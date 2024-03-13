#include "encodethh264.h"
#include <QDebug>
#include <QDateTime>
#include "controller/settingcontroller.h"
#include "controller/videocontroller.h"
EncodeThH264::EncodeThH264()
{
    this->pkt_index = 0;
    this->count = 0;
    this->queue = new QQueue<AVFrame*>;
}

void EncodeThH264::prepareEncode()  //初始化编码相关数据
{
    this->pkt = av_packet_alloc();
    this->pFormatContext = avformat_alloc_context();
    //1.注册组件
    av_register_all();
    //2.猜测封装格式
    //获取当前时间
    QDateTime time = QDateTime::currentDateTime();
    this->timer = time.toString("yyyyMMddhhmmss");
    qDebug()<<"QDateTime time"<<timer;
    //获取视频路径信息
    settingList = SettingController::getInstance()->initSettingData();
    //qDebug()<<settingList.at(0)->getVideoPath()+"/"+timer.toUtf8()+".h264";
    videoName = timer+".h264";
    this->filename = settingList.at(0)->getVideoPath()+"/"+timer.toUtf8()+".h264";
    AVOutputFormat *outputFormat = av_guess_format(nullptr,this->filename.toUtf8(),nullptr);
    if(nullptr == outputFormat)
    {
        qDebug()<<"av_guess_format error";
    }
    qDebug()<<"av_guess_format success";
    pFormatContext->oformat = outputFormat;
    //打开文件流
    int res = avio_open(&pFormatContext->pb,filename.toUtf8(),AVIO_FLAG_WRITE);
    if(res<0)
    {
        qDebug()<<"avio_open error";
        return;
    }
    qDebug()<<"avio_open success";
    //4.新建视频流
    AVStream* newStream =  avformat_new_stream(pFormatContext,nullptr);
    if(nullptr == newStream)
    {
        qDebug()<<"newStream error";
        return;
    }
    qDebug()<<"newStream success";
    //5.查找编码器
    this->pCodecContext = newStream->codec;
    //参数设置
    pCodecContext->width = this->width;         //属性--可以在解码线程中设置
    pCodecContext->height = this->height;        //属性--可以在解码线程中设置
    pCodecContext->time_base = {1,25};  //时间基 1秒播放的帧数
    pCodecContext->bit_rate = 400000;   //码率
    pCodecContext->framerate = {25,1};  //帧率
    pCodecContext->gop_size = 10;       //每10帧为1单位
    //影响清晰度
    pCodecContext->qmax = 51;
    pCodecContext->qmin = 10;
    pCodecContext->max_b_frames = 0;    //没有B帧
    pCodecContext->pix_fmt = AV_PIX_FMT_YUV420P;//编码器设置
    pCodecContext->codec_type = AVMEDIA_TYPE_VIDEO;//设置为视频流
    pCodecContext->codec_id = outputFormat->video_codec;//编码器ID
    //查找编码器
    this->encoder = avcodec_find_encoder(pCodecContext->codec_id);
    if(nullptr == encoder)
    {
        qDebug()<<"avcodec_find_encoder error";
        return;
    }
    qDebug()<<"avcodec_find_encoder success";
    //6.打开编码器
    res = avcodec_open2(pCodecContext,encoder,nullptr);
    if(res!=0)
    {
        qDebug()<<"avcodec_open2 error";
    }
    qDebug()<<"avcodec_open2 success";
    //7.写入头部信息
    res = avformat_write_header(pFormatContext,nullptr);
    if(res<0)
    {
        qDebug()<<"avformat_write_header error";
        return;
    }
    qDebug()<<"avformat_write_header success";
}

void EncodeThH264::encodeFrame(AVFrame *pictureYUV)
{
    //把AVFrame发给pCodecContext
    int res = avcodec_send_frame(this->pCodecContext,pictureYUV);
    if(res<0)
    {
        qDebug()<<"avcedec_send_frame error";
        return;
    }
    //一帧YUV420P压缩可能压缩成2个AVPacket
    while (res >= 0)
    {
        pictureYUV->pts = pkt_index++;
        //把一帧AVFrame压缩成AVPacket
        res = avcodec_receive_packet(this->pCodecContext,this->pkt);
        if(res == AVERROR_EOF || res == AVERROR(EACCES))
        {
            break;
        }
        //AVFrame写入文件
        av_interleaved_write_frame(this->pFormatContext,this->pkt);
        //qDebug()<<"write_frame success："<<pkt_index;
    }
}

void EncodeThH264::writeailer()
{
    //视频信息写入数据库
    //qDebug()<<videoName<<settingList.at(0)->getVideoPath()<<settingList.at(0)->getVideoPath()<<this->timer<<this->count;
    int res = VideoController::getInstance()->doVideo(videoName,settingList.at(0)->getVideoPath()+"/"+this->timer+".h264",
                                                      settingList.at(0)->getVideoPath()+"/"+this->timer+".jpg",
                                                      this->timer,this->count);
    //qDebug()<<"insertDeleteUpdate res = "<<res;
    //写尾帧
    av_write_trailer(pFormatContext);
    //关闭输入流
    avio_close(this->pFormatContext->pb);
    //释放视频信息
    avformat_free_context(pFormatContext);
}

int EncodeThH264::getWidth() const
{
    return width;
}

void EncodeThH264::setWidth(int value)
{
    width = value;
}

int EncodeThH264::getHeight() const
{
    return height;
}

void EncodeThH264::setHeight(int value)
{
    height = value;
}

QString EncodeThH264::getFilename() const
{
    return filename;
}

void EncodeThH264::setFilename(const QString &value)
{
    filename = value;
}

void EncodeThH264::writeFrame()
{
    this->writeailer();
}

void EncodeThH264::run()
{
    this->prepareEncode();
    while(1)
        {
        //延时10毫秒，防止代码运行过快，不写尾帧
        msleep(10);
        if(!this->queue->isEmpty())
        {
            this->encodeFrame(this->queue->dequeue());
            this->count++;
            //qDebug()<<"EncodeThH264 count:"<<this->count;

            if(this->count == this->settingList.at(0)->getIntervalTime())
            {
                this->writeailer();
                this->count = 0;
                this->prepareEncode();
            }
        }
    }
}
