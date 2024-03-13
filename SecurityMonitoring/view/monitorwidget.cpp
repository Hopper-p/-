#include "monitorwidget.h"
#include <QFile>
#include <QDebug>
#include "controller/usercontroller.h"
#include "controller/imagecontroller.h"
#include "controller/logcontroller.h"
#include <QMessageBox>
MonitorWidget::MonitorWidget(QWidget *parent) : QWidget(parent)
{
    this->switchView = true;
    this->loadQss();        //加载qss
    this->initControl();    //加载控件
    this->initConnect();    //加载链接
}

void MonitorWidget::loadQss()
{
    QFile qss(":/qss/main.qss");
    if( qss.open(QFile::ReadOnly))
    {
        qDebug()<<endl<<"open success";
        QString style = QLatin1String(qss.readAll());
        this->setStyleSheet(style);
        qss.close();
    }else{
        qDebug()<<endl<<"Open failed";
    }
}

void MonitorWidget::initControl()
{
    //-------------------下左----------start-------------------
    this->leftView = new QWidget(this);
    this->leftView->setObjectName("leftView");
        //创建垂直布局
    this->leftLayout = new QVBoxLayout(this);
        //创建控件
    this->usbCamera = new QListWidget;
    this->usbCamera->addItem("视频1");
    this->usbCamera->addItem("视频2");
        //控件添加到布局中
    this->leftLayout->addWidget(this->usbCamera);
    this->leftLayout->addStretch(1);//弹簧
        //添加完控件的布局添加到View内
    this->leftView->setLayout(this->leftLayout);
    //-------------------下左-----------end--------------------
    //-------------------下右----------start-------------------
    this->rightView = new QWidget(this);
    this->rightLayout = new QVBoxLayout(this);
        //-------------------下右上----------start-------------------
        this->rightUpView = new QWidget(this);
        this->rightUpView->setObjectName("rightUpView");
        this->rightUpView->setMinimumSize(720,480);
            //创建网格控件
        this->rightUpLayout = new QGridLayout(this);
            //创建控件
        this->videoLabs[0] = new QLabel("视频1", this);
        this->videoLabs[1] = new QLabel("视频2", this);
        this->videoLabs[2] = new QLabel("视频3", this);
        this->videoLabs[3] = new QLabel("视频4", this);
            //控件添加到布局
        this->rightUpLayout->setSpacing(2);//设置间距
        this->rightUpLayout->addWidget(this->videoLabs[0],0,0);//往网格的不同坐标添加不同的组件
        this->rightUpLayout->addWidget(this->videoLabs[1],0,1);
        this->rightUpLayout->addWidget(this->videoLabs[2],1,0);
        this->rightUpLayout->addWidget(this->videoLabs[3],1,1);
            //添加完控件的布局添加到View内
        this->rightUpView->setLayout(this->rightUpLayout);
        //-------------------下右上-----------end--------------------
        //-------------------下右下----------start-------------------
        this->rightDownView = new QWidget(this);
            //创建水平布局
        this->rightDownLayout = new QHBoxLayout(this);
            //创建控件
        this->SingleViewBtn = new QPushButton(this);
        this->SingleViewBtn->setStyleSheet("border-image:url(:/image/icon/通用类_一画面.png);width:40px;height:40px;");
        this->MultipleViewBtn = new QPushButton(this);
        this->MultipleViewBtn->setStyleSheet("border-image:url(:/image/icon/通用类_四画面.png);width:40px;height:40px;");
        this->pictureBtn = new QPushButton("拍照",this);
        this->pictureBtn->setStyleSheet("font-size:19px;");
            //控件添加到布局中
        this->rightDownLayout->addWidget(this->SingleViewBtn);
        this->rightDownLayout->addWidget(this->MultipleViewBtn);
        this->rightDownLayout->addWidget(this->pictureBtn);
        this->rightDownLayout->addStretch(1);//弹簧
            //布局添加到View内
        this->rightDownView->setLayout(this->rightDownLayout);
        //-------------------下右下-----------end--------------------
    this->rightLayout->addWidget(this->rightUpView,9);
    this->rightLayout->addWidget(this->rightDownView,1);
    this->rightLayout->setMargin(0);
    this->rightLayout->setSpacing(0);
        //布局添加到View内
    this->rightView->setLayout(this->rightLayout);
    //-------------------下右-----------end--------------------
    this->downLayout = new QHBoxLayout(this);
    this->downLayout->addWidget(this->leftView,1);
    this->downLayout->addWidget(this->rightView,7);
    this->downLayout->setMargin(0);
    this->downLayout->setSpacing(0);

    //读取摄像头信息
    this->settingList = SettingController::getInstance()->initSettingData();
    this->usbCamera->item(0)->setText(settingList.at(0)->getCameraName());
    //初始化播放线程
    this->playThread = new DecodeToPacket(settingList.at(0)->getCameraName());
    this->playThread->start();
}

void MonitorWidget::initConnect()
{
    //切换到单视图显示模式
    connect(this->SingleViewBtn,SIGNAL(clicked()),this,SLOT(switchSingle()));
    //切换到四宫格显示模式
    connect(this->MultipleViewBtn,SIGNAL(clicked()),this,SLOT(switchMultiple()));
    //获取解码的图片并添加到界面上
    connect(this->playThread, SIGNAL(sendImg(QImage)), this, SLOT(showImg(QImage)));
    //获取用户点击摄像头信息
    connect(this->usbCamera,SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(toPlayer(QListWidgetItem*)));
    //点击拍照
    connect(this->pictureBtn,SIGNAL(clicked()),this,SLOT(picture()));
}

QString MonitorWidget::getNowTime()
{

}

void MonitorWidget::setUserId(const QString &value)
{
    userId = value;
}

void MonitorWidget::writeFrame()
{
    this->playThread->writeFrame();
}
void MonitorWidget::showImg(QImage image)
{
    this->image = image;
    if(!image.isNull())
    {
        QImage img(image);
        QImage simg = img.scaledToWidth(this->videoLabs[0]->height(), Qt::SmoothTransformation);
        this->videoLabs[0]->setPixmap(QPixmap::fromImage(simg));
        this->videoLabs[0]->setScaledContents(true);
    }
}

void MonitorWidget::toPlayer(QListWidgetItem *usbItem)
{
    if(this->usbCamera->currentRow() == 0)
    {
        this->videoLabs[0]->setVisible(true);
        this->videoLabs[1]->setVisible(false);
        this->videoLabs[2]->setVisible(false);
        this->videoLabs[3]->setVisible(false);
    }
    else if (this->usbCamera->currentRow() == 1)
    {
        this->videoLabs[0]->setVisible(false);
        this->videoLabs[1]->setVisible(true);
        this->videoLabs[2]->setVisible(false);
        this->videoLabs[3]->setVisible(false);
    }
}
void MonitorWidget::switchSingle()
{
    this->switchView = false;
    int Row = this->usbCamera->currentRow();
    if(Row == -1)
    {
        Row = 0;
    }
    for (int i=0;i<4;i++)
    {
        if(Row == i)
        {
            this->videoLabs[i]->setVisible(true);
        }else {
            this->videoLabs[i]->setVisible(false);
        }
    }
}

void MonitorWidget::switchMultiple()
{
    this->switchView = true;
    for (int i=0;i<4;i++)
    {
        this->videoLabs[i]->setVisible(true);
    }
}

void MonitorWidget::picture()
{
    if(this->switchView)
    {
        QMessageBox::warning(this,"提示","未切换为单通道，无法拍照");
    }else if(UserController::getInstance()->doUserIdStatus(this->userId) == 1){
        QDateTime time = QDateTime::currentDateTime();
        QString timer = time.toString("yyyyMMddhhmmss");
        this->image.save(settingList.at(0)->getImagePath()+"/"+timer.toUtf8()+".jpg", "JPG", 100);
        //写入数据库
        int res = ImageController::getInstance()->doImage(timer+".jpg",
                          settingList.at(0)->getImagePath()+"/"+timer.toUtf8()+".jpg",timer);
        QMessageBox::information(this,"成功","已成功拍照",QMessageBox::Yes,QMessageBox::Yes);
        //将登录写入日志
        int user_id = UserController::getInstance()->doUserId(this->userId.toInt());
        res = LogController::getInstance()->doLog(user_id,"截屏",timer);
        emit updateImg();//刷新照片列表信号
    }else{
        QMessageBox::warning(this,"提示","当前还未登录，无法拍照");
    }
}
