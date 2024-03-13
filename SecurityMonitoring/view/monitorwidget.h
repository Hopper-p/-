#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QDateTime>
#include "thread/decodetopacket.h"
#include <QListWidget>
#include "controller/settingcontroller.h"
class MonitorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MonitorWidget(QWidget *parent = nullptr);

    void loadQss();

    void initControl();

    void initConnect();

    QString getNowTime();
    void setUserId(const QString &value);

    void writeFrame();//调用进程写尾帧
private:
    QVBoxLayout *leftLayout,*rightLayout;
    QHBoxLayout *totalLayout,*downLayout,*rightDownLayout;
    QWidget *leftView,*rightView,*rightUpView,*rightDownView;
    QGridLayout *rightUpLayout;
    //QLabel *videoLab1,*videoLab2,*videoLab3,*videoLab4;
    QLabel* videoLabs[4];
    QPushButton *SingleViewBtn,*MultipleViewBtn,*pictureBtn;
    DecodeToPacket *playThread; //播放线程
    QListWidget *usbCamera;
    QImage image;
    QList<Setting*> settingList;
    QString userId;
    bool switchView;
signals:
    void updateImg();
public slots:
    void showImg(QImage image);//将解码的图片传入界面中
    void toPlayer(QListWidgetItem *usbItem);
    void switchSingle();//切换单视图显示
    void switchMultiple();//切换四宫格显示
    void picture();
};

#endif // MONITORWIDGET_H
