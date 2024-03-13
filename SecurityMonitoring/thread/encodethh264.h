#ifndef ENCODETHH264_H
#define ENCODETHH264_H
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
#include <QQueue>
#include "data/setting.h"
#include <QList>
class EncodeThH264:public QThread
{
    Q_OBJECT
public:
    EncodeThH264();
    void prepareEncode();
    /** 把YUV420P压缩成
     * @brief encodeFrame
     * @param pictureYUV
     */
    void encodeFrame(AVFrame *pictureYUV);
    //写尾帧
    void writeailer();

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    QString getFilename() const;
    void setFilename(const QString &value);

    QQueue<AVFrame*> *queue;
    void writeFrame();//调用进程写尾帧
private:
    AVCodecContext * pCodecContext;
    AVCodec * encoder;
    AVPacket *pkt;
    AVFormatContext *pFormatContext;
    int pkt_index;      //记录多少帧
    int width,height;
    QString filename;

    QString videoName;
    QString timer;

    int count;
    QList<Setting*> settingList;

protected:
    void run();
};

#endif // ENCODETHH264_H
