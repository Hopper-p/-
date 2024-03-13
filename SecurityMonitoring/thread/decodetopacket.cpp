#include "decodetopacket.h"
#include <QDateTime>
#include <QDebug>
#include <stdio.h>
DecodeToPacket::DecodeToPacket(QString cameraName)
{

    //注册组件
    av_register_all();
    //注册设备
    avdevice_register_all();
    // 封装格式上下文结构体
    this->pFormatContext = avformat_alloc_context();
    // 1. 打开一个视频
    QString camera = "video="+cameraName;
    qDebug() <<camera;
    AVInputFormat *fmt = av_find_input_format("dshow");
    this->res = avformat_open_input(&pFormatContext, camera.toUtf8(), fmt, nullptr);
    if(res != 0)
    {
        qDebug() << "DecodeToPacket::DecodeToPacket(): open_input fail...";
    }
    else
    {
        qDebug() << "DecodeToPacket::DecodeToPacket(): open_input success...";
    }

    // 2. 查找流媒体数据
    res = avformat_find_stream_info(pFormatContext, nullptr);
    if(res < 0)
    {
        qDebug() << "DecodeToPacket::DecodeToPacket(): find_stream_info fail...";
    }
    else
    {
        qDebug() << "DecodeToPacket::DecodeToPacket(): find_stream_info success...";
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
        qDebug() << "DecodeToPacket::DecodeToPacket(): find_video_stream_info fail...";
        return;
    }
    qDebug() << "DecodeToPacket::DecodeToPacket(): find_video_stream_info success...";



    // 4. 查找解码器
    this->pCodecContext = pFormatContext->streams[vedio_index]->codec;
    this->decoder = avcodec_find_decoder(pCodecContext->codec_id);
    if (!decoder) {
        qDebug() << "DecodeToPacket::DecodeToPacket(): find_decoder fail...";
        return;
    }
    qDebug() << "DecodeToPacket::DecodeToPacket(): find_decoder success...";

    // 5. 打开解码器
    if (avcodec_open2(pCodecContext, decoder, nullptr) != 0) {
        qDebug() << "DecodeToPacket::DecodeToPacket(): open_decoder fail...";
        return;
    }
    qDebug() << "DecodeToPacket::DecodeToPacket(): open_decoder success...";

    // 6. 数据准备
    packet = (AVPacket*)malloc(sizeof (AVPacket));      // 开空间
    this->size = pCodecContext->width*pCodecContext->height;
    res = av_new_packet(packet, size);
    if(res != 0)
    {
        qDebug()<<"av_new_packet fail";
        return;
    }
    qDebug()<<"av_new_packet success";
    this->picture = av_frame_alloc();
    this->pictureRGB = av_frame_alloc();
    this->pictureYUV = av_frame_alloc();
    picture->width = pCodecContext->width;
    picture->height = pCodecContext->height;
    picture->format = pCodecContext->pix_fmt;
    pictureRGB->width = pCodecContext->width;
    pictureRGB->height = pCodecContext->height;
    pictureRGB->format = pCodecContext->pix_fmt;

    this->pictureYUV->width = this->pCodecContext->width;
    this->pictureYUV->height = this->pCodecContext->height;
    this->pictureYUV->format = this->pCodecContext->pix_fmt;
    //压缩的一帧RGB32大小
    int numbyte = avpicture_get_size(AV_PIX_FMT_RGB32,pCodecContext->width,pCodecContext->height);
    //动态开空间
    this->buffer = (uint8_t*)av_malloc(numbyte*sizeof (uint8_t));
    //填充规则
    avpicture_fill((AVPicture *)pictureRGB,buffer,
                   AV_PIX_FMT_RGB32,pCodecContext->width,pCodecContext->height);
    this->swsContextRGB = sws_getContext(pCodecContext->width,pCodecContext->height,pCodecContext->pix_fmt,
                                               pCodecContext->width,pCodecContext->height,AV_PIX_FMT_RGB32,
                                               SWS_BICUBIC,nullptr,nullptr,nullptr);

    //压缩的一帧RGB32大小
    int numbyteYUV = avpicture_get_size(AV_PIX_FMT_YUV420P,pCodecContext->width,pCodecContext->height);
    //动态开空间
    this->bufferYUV = (uint8_t*)av_malloc(numbyteYUV*sizeof (uint8_t));
    //填充规则
    avpicture_fill((AVPicture *)pictureYUV,bufferYUV,
                   AV_PIX_FMT_YUV420P,pCodecContext->width,pCodecContext->height);
    this->swsContextYUV = sws_getContext(pCodecContext->width,pCodecContext->height,pCodecContext->pix_fmt,
                                               pCodecContext->width,pCodecContext->height,AV_PIX_FMT_YUV420P,
                                               SWS_BICUBIC,nullptr,nullptr,nullptr);

    //this->toH264->prepareEncode();
}

void DecodeToPacket::writeFrame()
{
    this->toH264->writeFrame();
}

void DecodeToPacket::run()
{
    settingList = SettingController::getInstance()->initSettingData();
    int frame_num = 0;
    //1.创建编码指针
    this->toH264 = new EncodeThH264;
    //this->toH264->setFilename(settingList.at(0)->getVideoPath()+"/"+timer.toUtf8()+".h264");

    this->toH264->setWidth(pCodecContext->width);
    this->toH264->setHeight(pCodecContext->height);
    //开启编码线程
    this->toH264->start();
    while (av_read_frame(pFormatContext, packet) == 0)
    {
        // 判断是否为视频流
        if (packet->stream_index == vedio_index)
        {
            //fwrite(packet->data, packet->size, 1, fp);
            int ptr = -1;
            avcodec_decode_video2(pCodecContext,picture,&ptr,packet);
            if(ptr != 0)
            {
                sws_scale(swsContextRGB,picture->data,picture->linesize,0,picture->height,
                          pictureRGB->data,pictureRGB->linesize);
                sws_scale(swsContextYUV,picture->data,picture->linesize,0,picture->height,
                          pictureYUV->data,pictureYUV->linesize);
                this->img = QImage((uchar*)buffer,pictureRGB->width,pictureRGB->height,QImage::Format_RGB32);

                emit sendImg(this->img);

                //编码动作
                this->toH264->queue->enqueue(pictureYUV);
                frame_num++;
                //截取第一帧为视频封面
                if(frame_num%settingList.at(0)->getIntervalTime() == 1)
                {
                    QDateTime time = QDateTime::currentDateTime();
                    QString timer = time.toString("yyyyMMddhhmmss");
                    img.save(settingList.at(0)->getVideoPath()+"/"+timer.toUtf8()+".jpg", "JPG", 100);
                    frame_num = 1;
                }
                //qDebug() <<"frame_num:"<<frame_num;
            }
        }
        // 释放AVPacket
        av_packet_unref(packet);
    }
    qDebug() << "Frames: " << frame_num;
    // 释放资源
    //fclose(fp);
    avcodec_close(pCodecContext);
    avformat_close_input(&pFormatContext);
    avformat_free_context(pFormatContext);
}
