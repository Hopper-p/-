#include "transcodetonormalthread.h"
#include <QDebug>
TransCodeToNormalThread::TransCodeToNormalThread()
{

}

TransCodeToNormalThread::~TransCodeToNormalThread()
{
    qDebug() << "释放转码线程锁";
}

void TransCodeToNormalThread::prepareWork()
{
    if(this->oriPath.isEmpty() || this->savePath.isEmpty())
    {
        return;
    }
    //1.注册组件
    av_register_all();
    //2.打开视频流--h264
    this->pkt = (AVPacket*)malloc(sizeof(AVPacket));
    this->video_index = -1;
    this->frameCount = 0;
    this->pFormatContext = avformat_alloc_context();
    int res = avformat_open_input(&this->pFormatContext,this->oriPath.toUtf8(),nullptr,nullptr);
    if(res !=0 )
    {
        qDebug()<<"avformat_open_input fail";
        return;
    }
    qDebug()<<"avformat_open_input sucess";
    //3.打开视频流
    res = avformat_find_stream_info(this->pFormatContext,nullptr);
    if(res !=0 )
    {
        qDebug()<<"avformat_find_stream_info fail";
        return;
    }
    qDebug()<<"avformat_find_stream_info sucess";
    //查找视频流

    for(int i=0;i<this->pFormatContext->nb_streams;i++)
    {
        if(this->pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            this->video_index = i;
            break;
        }
    }
    if(video_index == -1)
    {
        qDebug()<<"error";
    }
    //4.猜测封装格式

    this->outputFormat = av_guess_format(nullptr,this->savePath.toUtf8(),nullptr);
    if(this->outputFormat == nullptr)
    {
        qDebug()<<"av_guess_format fail";
        return;
    }
    qDebug()<<"av_guess_format sucess";
    //5.打开文件流--创建出封装格式的封装格式上下文结构体
    this->outFormatContext = avformat_alloc_context();
    this->outFormatContext->oformat = this->outputFormat;
    res = avio_open(&this->outFormatContext->pb,this->savePath.toUtf8(),AVIO_FLAG_WRITE);
    if(res < 0)
    {
        qDebug()<<"avio_open fail";
        return;
    }
    qDebug()<<"avio_open sucess";
    //6.新建视频流
    this->newStream = avformat_new_stream(this->outFormatContext,nullptr);
    if(newStream == nullptr)
    {
        qDebug()<<"avformat_new_stream fail";
        return;
    }
    qDebug()<<"avformat_new_stream sucess";
    //参数设置
    //1.目标视频流的编码信息
    //2.源视频的编码器信息参数结构体
    res = avcodec_parameters_copy(this->newStream->codecpar,
                            this->pFormatContext->streams[video_index]->codecpar);
    if(res < 0)
    {
        qDebug()<<"avcodec_parameters_copy fail";
        return;
    }
    qDebug()<<"avcodec_parameters_copy sucess";
    this->newStream->codecpar->codec_tag = 0;
    this->newStream->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    //8.写入头部信息
    res = avformat_write_header(this->outFormatContext,nullptr);
    if(res < 0)
    {
        qDebug()<<"avformat_write_header fail";
        return;
    }
    qDebug()<<"avformat_write_header sucess";
}

void TransCodeToNormalThread::tranceCode()
{
    //读取一帧码流数据
    while(av_read_frame(this->pFormatContext,this->pkt) == 0)
    {
        //判定是否有视频流
        if(this->pkt->stream_index == this->video_index)
        {
            this->frameCount++;
            qDebug() << frameCount;
            //转码    时间基的转化与设置
            //如果没有时间基  时间基的转换流程
            if(this->pkt->pts == AV_NOPTS_VALUE)
            {
                AVRational time_base1 = this->pFormatContext->streams[this->video_index]->time_base;
                //计算两帧之间的长度
                int64_t duration = (double)AV_TIME_BASE/av_q2d(this->pFormatContext->streams[this->video_index]->r_frame_rate);
                //计算显示时间基：总帧数*2帧之间的长度/输入时间基*AV_TIME_BASE
                this->pkt->pts = (double)(this->frameCount*duration) /(double)(av_q2d(time_base1)*AV_TIME_BASE);
                //没有B帧  解码时间基 = 显示时间基
                this->pkt->dts = this->pkt->pts;
                this->pkt->duration = duration/(double)(av_q2d(time_base1)*AV_TIME_BASE);
            }
            else if(this->pkt->pts < this->pkt->dts)
                continue;
            //时间基的转换：参数 1：要换算的值；参数 2：原来的时间基，参数 3：现在的时间基
            //参数 4：换算的规则
            //显示时间基的转化
            pkt->pts=av_rescale_q_rnd(pkt->pts, this->pFormatContext->streams[video_index]->time_base,
                                      this->newStream->time_base, (AVRounding)(AV_ROUND_INF|AV_ROUND_PASS_MINMAX));
            //解码时间基的转换FFMPEG 技术
            pkt->dts=av_rescale_q_rnd(pkt->dts, this->pFormatContext->streams[video_index]->time_base,
                                      this->newStream->time_base, (AVRounding)(AV_ROUND_INF|AV_ROUND_PASS_MINMAX));

            pkt->duration=av_rescale_q(pkt->duration, this->pFormatContext->streams[video_index]->time_base,
                                       this->newStream->time_base);
            pkt->pos=-1;
            pkt->flags|=AV_PKT_FLAG_KEY;
            pkt->stream_index=0;
            //写入数据到输出视频信息结构体汇总
            av_interleaved_write_frame(this->outFormatContext,pkt);

            av_packet_unref(pkt);

        }
        av_packet_unref(this->pkt);
    }
    //写入尾
    av_write_trailer(this->outFormatContext);
    //关闭编码器
    avcodec_close(this->outFormatContext->streams[this->video_index]->codec);
    av_freep(&this->outFormatContext->streams[this->video_index]->codec);
    //关闭输出流
    avio_close(this->outFormatContext->pb);
    av_free(this->outFormatContext);
    avformat_close_input(&this->pFormatContext);
    av_free(this->pFormatContext);
}

QString TransCodeToNormalThread::getOriPath() const
{
    return oriPath;
}

void TransCodeToNormalThread::setOriPath(const QString &value)
{
    oriPath = value;
}

QString TransCodeToNormalThread::getSavePath() const
{
    return savePath;
}

void TransCodeToNormalThread::setSavePath(const QString &value)
{
    savePath = value;
}

void TransCodeToNormalThread::run()
{
    //读取一帧码流数据
    while(av_read_frame(this->pFormatContext,this->pkt) == 0)
    {
        //判定是否有视频流
        if(this->pkt->stream_index == this->video_index)
        {
            this->frameCount++;
            qDebug() << frameCount;
            //转码    时间基的转化与设置
            //如果没有时间基  时间基的转换流程
            if(this->pkt->pts == AV_NOPTS_VALUE)
            {
                AVRational time_base1 = this->pFormatContext->streams[this->video_index]->time_base;
                //计算两帧之间的长度
                int64_t duration = (double)AV_TIME_BASE/av_q2d(this->pFormatContext->streams[this->video_index]->r_frame_rate);
                //计算显示时间基：总帧数*2帧之间的长度/输入时间基*AV_TIME_BASE
                this->pkt->pts = (double)(this->frameCount*duration) /(double)(av_q2d(time_base1)*AV_TIME_BASE);
                //没有B帧  解码时间基 = 显示时间基
                this->pkt->dts = this->pkt->pts;
                this->pkt->duration = duration/(double)(av_q2d(time_base1)*AV_TIME_BASE);
            }
            else if(this->pkt->pts < this->pkt->dts)
                continue;
            //时间基的转换：参数 1：要换算的值；参数 2：原来的时间基，参数 3：现在的时间基
            //参数 4：换算的规则
            //显示时间基的转化
            pkt->pts=av_rescale_q_rnd(pkt->pts, this->pFormatContext->streams[video_index]->time_base,
                                      this->newStream->time_base, (AVRounding)(AV_ROUND_INF|AV_ROUND_PASS_MINMAX));
            //解码时间基的转换FFMPEG 技术
            pkt->dts=av_rescale_q_rnd(pkt->dts, this->pFormatContext->streams[video_index]->time_base,
                                      this->newStream->time_base, (AVRounding)(AV_ROUND_INF|AV_ROUND_PASS_MINMAX));

            pkt->duration=av_rescale_q(pkt->duration, this->pFormatContext->streams[video_index]->time_base,
                                       this->newStream->time_base);
            pkt->pos=-1;
            pkt->flags|=AV_PKT_FLAG_KEY;
            pkt->stream_index=0;
            //写入数据到输出视频信息结构体汇总
            av_interleaved_write_frame(this->outFormatContext,pkt);

        }
        av_packet_unref(this->pkt);

    }
    //写入尾
    av_write_trailer(this->outFormatContext);
    //关闭编码器
    avcodec_close(this->outFormatContext->streams[this->video_index]->codec);
    av_freep(&this->outFormatContext->streams[this->video_index]->codec);
    //关闭输出流
    avio_close(this->outFormatContext->pb);
    av_free(this->outFormatContext);
    avformat_close_input(&this->pFormatContext);
    av_free(this->pFormatContext);
    emit transCodeSuccess();
}
