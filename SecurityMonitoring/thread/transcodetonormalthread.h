#ifndef TRANSCODETONORMALTHREAD_H
#define TRANSCODETONORMALTHREAD_H

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

#include <QThread>

class TransCodeToNormalThread: public QThread
{
    Q_OBJECT
public:
    TransCodeToNormalThread();
    ~TransCodeToNormalThread();
    void prepareWork();
    void tranceCode();

    QString getOriPath() const;
    void setOriPath(const QString &value);

    QString getSavePath() const;
    void setSavePath(const QString &value);

private:
    // 封装格式上下文结构体（解码+编码）
    AVFormatContext *pFormatContext, *outFormatContext;
    AVOutputFormat *outputFormat;
    AVStream *newStream;
    int video_index;
    AVPacket *pkt;                  // 压缩一帧码流数据
    int frameCount;                 // 记录总帧数

    QString oriPath;
    QString savePath;

protected:
    void run();

signals:
    void transCodeSuccess();
};

#endif // TRANSCODETONORMALTHREAD_H
