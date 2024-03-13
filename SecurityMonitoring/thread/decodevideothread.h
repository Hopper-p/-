#ifndef DECODEVIDEOTHREAD_H
#define DECODEVIDEOTHREAD_H

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
#include <QImage>
#include <QThread>
#include <QString>

class DecodeVideoThread: public QThread
{
    Q_OBJECT
public:
    DecodeVideoThread();
    ~DecodeVideoThread();

    void prepareDecode();

    int getSpeed() const;
    void setSpeed(int value);

    QString getFilePath() const;
    void setFilePath(const QString &value);

    bool getNeedSeek() const;
    void setNeedSeek(bool value);

    void setStop(bool value);

private:
    AVFormatContext *pFormatContext;    // 封装格式上下文结构体
    int vedio_index;                    // 视频流下标
    AVCodecContext *pCodecContext;      // 编解码器上下文结构体
    AVCodec *decoder;                   // 编解码器
    AVPacket *packet;                   // 存储一帧压缩码流数据
    int size;
    AVFrame *picture;                   // 携带无用像素数据
    AVFrame *pictureRGB;                // 剔除后的纯净像素数据
    uint8_t *buffer;
    SwsContext *swsContextRGB;          // 转置规则
    QImage img;                         // 发送的图片
    QString filePath;                   // 文件路径
    int speed;                          // 播放速度
    bool needSeek;                      //暂停播放标志位
    bool stop;

protected:

    /** 持续不断解码AVFrame 纯净AVFrame  --> QImage  --> 界面发送
     * @brief run
     */
    void run();

signals:
    void sendImg(QImage img);
    void playFinished();

};


#endif // DECODEVIDEOTHREAD_H
