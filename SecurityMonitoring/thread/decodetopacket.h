#ifndef DECODETOPACKET_H
#define DECODETOPACKET_H
#include <QImage>
#include <QThread>
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"//输入输出设备库:读取摄像头的
#include "libavfilter/avfilter.h"//音视频滤镜库:进行音视频处理与编辑
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libswresample/swresample.h"
#include "libswscale/swscale.h"
}
#include "encodethh264.h"
#include "controller/settingcontroller.h"
#include <QList>
class DecodeToPacket:public QThread
{
    Q_OBJECT
public:
    DecodeToPacket(QString cameraName);
    void setMulriple(int value);
    void writeFrame();//调用进程写尾帧
private:
    AVFormatContext *pFormatContext;
    int res;
    int vedio_index;
    //编解码器上下文结构体
    AVCodecContext *pCodecContext;
    //编解码器
    AVCodec *decoder;
    //存储一帧压缩的码流数据
    AVPacket *packet;
    int size;
    //携带无用像素数据  剔除后的纯净像素数据
    AVFrame *picture,*pictureRGB,*pictureYUV;
    uint8_t* buffer,*bufferYUV;
    //转置规则
    SwsContext *swsContextRGB,*swsContextYUV;
    QImage img;
    //编码子针
    EncodeThH264 *toH264;

    QList<Setting*> settingList;
protected:
    void run();
signals:
    void sendImg(QImage img);
};

#endif // DECODETOPACKET_H
