#include "DecodeVideoThread.h"
#include <QDebug>

/**
 * 解封装： MP4、FLV -> AVPacket
 * @brief DecodeVideoThread::DecodeVideoThread
 */
DecodeVideoThread::DecodeVideoThread()
{
    this->speed = 40;
    this->needSeek = false;
    this->stop = false;
}

DecodeVideoThread::~DecodeVideoThread()
{
}

void DecodeVideoThread::prepareDecode()
{
    av_register_all();
    // 封装格式上下文结构体
    this->pFormatContext = avformat_alloc_context();
    // 1. 打开一个视频
    int res = avformat_open_input(&pFormatContext, this->filePath.toUtf8(), nullptr, nullptr);
    if(res != 0)
    {
        qDebug() << "DecodeVideoThread::DecodeVideoThread(): open_input fail...";
    }
    else
    {
        qDebug() << "DecodeVideoThread::DecodeVideoThread(): open_input success...";
    }

    // 2. 查找流媒体数据
    res = avformat_find_stream_info(pFormatContext, nullptr);
    if(res < 0)
    {
        qDebug() << "DecodeVideoThread::DecodeVideoThread(): find_stream_info fail...";
    }
    else
    {
        qDebug() << "DecodeVideoThread::DecodeVideoThread(): find_stream_info success...";
    }

    // 3. 找到视频流
    this->vedio_index = -1;       // 记录vedio
    for (int i=0; i<pFormatContext->nb_streams; i++)
    {
        if(pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            vedio_index = i;
            break;
        }
    }
    if(vedio_index == -1)
    {
        qDebug() << "DecodeVideoThread::DecodeVideoThread(): find_video_stream_info fail...";
        return;
    }
    qDebug() << "DecodeVideoThread::DecodeVideoThread(): find_video_stream_info success...";

    // 4. 查找解码器
    this->pCodecContext = pFormatContext->streams[vedio_index]->codec;
    this->decoder = avcodec_find_decoder(pCodecContext->codec_id);
    if (!decoder) {
        qDebug() << "DecodeVideoThread::DecodeVideoThread(): find_decoder fail...";
        return;
    }
    qDebug() << "DecodeVideoThread::DecodeVideoThread(): find_decoder success...";

    // 5. 打开解码器
    if (avcodec_open2(pCodecContext, decoder, nullptr) != 0) {
        qDebug() << "DecodeVideoThread::DecodeVideoThread(): open_decoder fail...";
        return;
    }
    qDebug() << "DecodeVideoThread::DecodeVideoThread(): open_decoder success...";

    // 6. 数据准备
    this->packet = (AVPacket*)malloc(sizeof (AVPacket));      // 开辟空间
    this->size = pCodecContext->width * pCodecContext->height;
    av_new_packet(packet, size);
    if(res != 0)
    {
         qDebug() << "DecodeVideoThread::DecodeVideoThread(): av_new_packet fail...";
         return;
    }
    qDebug() << "DecodeVideoThread::DecodeVideoThread(): av_new_packet success...";
    this->picture = av_frame_alloc();                 // 开辟空间 像素数据——嗲有无效数据
    this->pictureRGB = av_frame_alloc();             // 开辟空间 像素数据——纯净
    picture->width = pCodecContext->width;
    picture->height = pCodecContext->height;
    picture->format = pCodecContext->pix_fmt;
    pictureRGB->width = pCodecContext->width;
    pictureRGB->height = pCodecContext->height;
    pictureRGB->format = pCodecContext->pix_fmt;
    // 计算压缩的一帧RGB32的大小
    int numByte = avpicture_get_size(AV_PIX_FMT_RGB32,  pCodecContext->width,  pCodecContext->height);
    // 动态开空间
    this->buffer = (uint8_t*)av_malloc(numByte * sizeof(uint8_t));
    // 填充规则
    avpicture_fill((AVPicture *)pictureRGB, buffer,
                   AV_PIX_FMT_RGB32,  pCodecContext->width,  pCodecContext->height);
    // 转置规则
    this->swsContextRGB = sws_getContext(pCodecContext->width, pCodecContext->height, pCodecContext->pix_fmt,
                                               pCodecContext->width, pCodecContext->height, AV_PIX_FMT_RGB32,
                                         SWS_BICUBIC, nullptr, nullptr, nullptr);
}

int DecodeVideoThread::getSpeed() const
{
    return speed;
}

void DecodeVideoThread::setSpeed(int value)
{
    speed = value;
}

QString DecodeVideoThread::getFilePath() const
{
    return filePath;
}

void DecodeVideoThread::setFilePath(const QString &value)
{
    filePath = value;
}

bool DecodeVideoThread::getNeedSeek() const
{
    return needSeek;
}

void DecodeVideoThread::setNeedSeek(bool value)
{
    needSeek = value;
}

void DecodeVideoThread::setStop(bool value)
{
    stop = value;
}

void DecodeVideoThread::run()
{
    // 7. 读取码流数据
    int frame_num = 0;
    while(1)
    {
        prepareDecode();
        while (av_read_frame(pFormatContext, packet) == 0)
        {
            if(this->stop)
            {
                this->stop = false;
                return;
            }
            while (this->needSeek)
            {
                msleep(10);
            }
            // 判断是否为视频流
            if (packet->stream_index == vedio_index)
            {
                // 解码   AVPacket --> AVFrame
                int ptr = -1;
                avcodec_decode_video2(pCodecContext, picture, &ptr, packet);
                if(ptr != 0)
                {
                    // 非纯净的Fram ---转置规则---> 纯净的RGB32像素数据
                    // sws_scale(转置规则, 源数据, 源列数, 开始转置的列数， 需要转换的高度，目标数据，目标列数);
                    sws_scale(swsContextRGB, picture->data, picture->linesize, 0,
                              picture->height, pictureRGB->data, pictureRGB->linesize);
                    this->img = QImage((uchar*)buffer, pictureRGB->width, pictureRGB->height, QImage::Format_RGB32);
                    emit sendImg(this->img);
                    msleep(this->speed);
                    frame_num++;
                }
            }
            av_packet_unref(packet);        // 释放AVPacket
        }
        frame_num = 0;
    }
}
