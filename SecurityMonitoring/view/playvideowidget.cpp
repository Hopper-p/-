#include "playvideowidget.h"
#include <QDebug>
#include <QFile>
#include <QIcon>
#include <QStyledItemDelegate>
#include <QMessageBox>
#include <QDateTime>
#include "controller/usercontroller.h"
#include "controller/imagecontroller.h"
#include "controller/logcontroller.h"
PlayVideoWidget::PlayVideoWidget(QWidget *parent) : QWidget(parent)
{
    this->isPlay = true;
    this->loadQss();    //加载qss
    this->initControl();
    this->initConnect();
}

void PlayVideoWidget::loadQss()
{
    QFile qss(":/qss/Player.qss");
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

void PlayVideoWidget::initControl()
{
    //创建整个窗口样式
    this->resize(900,600);
    this->setWindowTitle("播放器");
    this->setWindowIcon(QIcon(":/image/player/播放器-主页.png"));
    //定义上中下view
    //-------------------上----------start-------------------
    this->topview = new QWidget(this);
    this->topview->setFixedHeight(45);
    this->topview->setStyleSheet("background-color:black");
        //创建布局
    this->topLayout = new QHBoxLayout(this);
        //创建控件
    this->topLab1 = new QLabel(this);
    this->topLab1->setMinimumSize(30,30);
    this->topLab1->setMaximumSize(30,30);
    this->topLab1->setStyleSheet("border-image:url(:/image/player/播放器-主页.png);");
    this->topLab2 = new QLabel("主界面",this);
    this->topLab3 = new QLabel("视频标题",this);
        //控件添加到布局中
    this->topLayout->addWidget(this->topLab1);
    this->topLayout->addWidget(this->topLab2);
    this->topLayout->addStretch(1);
    this->topLayout->addWidget(this->topLab3);
        //布局添加到view中
    this->topview->setLayout(this->topLayout);
    //-------------------上-----------end--------------------
    //-------------------中----------start-------------------
    this->middleView = new QWidget(this);
    //this->middleView->setStyleSheet("background-color:white");

    this->playLayout = new QVBoxLayout(this);

    this->playLab = new QLabel(this);
    this->playLab->setScaledContents(true);
    this->playLab->setMinimumSize(800, 368);
    this->playLab->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred); // 设置大小策略为首选大小

    this->playLayout->addWidget(this->playLab);
    this->playLayout->setMargin(0);
    this->playLayout->setSpacing(0);

    this->middleView->setLayout(this->playLayout);
    //-------------------中-----------end--------------------
    //-------------------下----------start-------------------
        //-------------------下进度条----------start-------------------
            //创建布局
    this->timLayout = new QHBoxLayout(this);
            //创建控件
    this->playBar = new QProgressBar(this);
    // 设置进度范围（0-100）
    this->playBar->setMinimum(0);
    this->playBar->setMaximum(30);
    this->proLabel = new QLabel("0 / " + QString::number(this->playBar->maximum()));
    this->playBar->setValue(0);
            //控件添加到布局中
    this->timLayout->addWidget(this->proLabel);
    this->timLayout->addWidget(this->playBar);
            //布局添加到view中
    this->bottomViews = new QWidget(this);
    this->bottomViews->setStyleSheet("background-color:black");
    this->bottomViews->setLayout(this->timLayout);
        //-------------------下进度条----------end-------------------
        //-------------------下控件----------start-------------------
            //创建布局
    this->botLayout1 = new QHBoxLayout(this);
            //创建控件
    this->playBtn = new QPushButton(this);
    this->playBtn->setIcon(QIcon(":/image/player/播放器-暂停_44.png"));
    this->lastEpisodeBtn = new QPushButton(this);
    this->lastEpisodeBtn->setIcon(QIcon(":/image/player/播放器-上一集.png"));
    this->nextEpisodeBtn = new QPushButton(this);
    this->nextEpisodeBtn->setIcon(QIcon(":/image/player/播放器-下一集_44.png"));
    this->plyBtn5 = new QPushButton("导出",this);
    this->comBx2 = new QComboBox(this);
    this->comBx2->addItem("0.5X");
    this->comBx2->addItem("1.0X");
    this->comBx2->addItem("2.0X");
    this->comBx2->addItem("3.0X");
    this->comBx2->setCurrentIndex(1);
    this->comBx2->setItemDelegate(new QStyledItemDelegate());
    this->plyBtn2 = new QPushButton("截屏",this);
            //控件添加到布局中
    this->botLayout1->addWidget(this->playBtn);
    this->botLayout1->addWidget(this->lastEpisodeBtn);
    this->botLayout1->addWidget(this->nextEpisodeBtn);
    this->botLayout1->addStretch(1);
    this->botLayout1->addWidget(this->plyBtn5);
    this->botLayout1->addWidget(this->comBx2);
    this->botLayout1->addWidget(this->plyBtn2);
            //布局添加到view中
    this->bottomView = new QWidget(this);
    this->bottomView->setFixedHeight(45);
    this->bottomView->setStyleSheet("background-color:black");
    this->bottomView->setLayout(this->botLayout1);
        //-------------------下控件----------end-------------------
    //-------------------下-----------end--------------------
    //将上中下view添加到垂直布局中
    this->totalLayout = new QVBoxLayout(this);
    this->totalLayout->addWidget(this->topview,1);
    this->totalLayout->addWidget(this->middleView,10);
    this->totalLayout->addWidget(this->bottomViews,1);
    this->totalLayout->addWidget(this->bottomView,1);
    this->totalLayout->setMargin(0);
    this->totalLayout->setSpacing(0);
    //初始化播放线程
    this->videoThread = new DecodeVideoThread();
    //初始化导出页面
    this->DownWin = new DownWidget;
    this->DownWin->setVideoName(this->videoName);

    //读取设置信息
    this->settingList = SettingController::getInstance()->initSettingData();
}

void PlayVideoWidget::initConnect()
{
    connect(this->playBtn,SIGNAL(clicked()),this,SLOT(playHandover()));
    connect(this->videoThread,SIGNAL(sendImg(QImage)),this,SLOT(showImg(QImage)));
    connect(this->comBx2,SIGNAL(currentIndexChanged(QString)),this,SLOT(Changes(QString)));
    connect(this->plyBtn2,SIGNAL(clicked()),this,SLOT(picture()));
    connect(this->plyBtn5,SIGNAL(clicked()),this,SLOT(showDown()));
    connect(this->lastEpisodeBtn,SIGNAL(clicked()),this,SIGNAL(videoLast()));
    connect(this->nextEpisodeBtn,SIGNAL(clicked()),this,SIGNAL(videoNext()));
}

void PlayVideoWidget::setVideoName(const QString &value)
{
    videoName = value;
    this->topLab3->setText(videoName);
}

void PlayVideoWidget::playStart(QString videoUrl)
{

    if(this->videoThread->isRunning())
    {
        this->videoThread->setStop(true);
        this->videoThread->wait();
        this->videoThread->quit();
    }
    qDebug()<<this->videoThread->isRunning()<<this->videoThread->isFinished();
    this->videoUrl = videoUrl;
    this->DownWin->setVideoUrl(videoUrl);
    this->videoThread->setFilePath(this->videoUrl);
    this->videoThread->start();
}

void PlayVideoWidget::setUserId(const QString &value)
{
    userId = value;
}

void PlayVideoWidget::closeEvent(QCloseEvent *event)
{
    if(this->videoThread != nullptr)
    {
        this->videoThread->setStop(true);
        this->videoThread->wait();
        this->videoThread->quit();
    }
}

void PlayVideoWidget::showDown()
{
    this->DownWin->show();
    this->DownWin->setUserId(this->userId);
}

void PlayVideoWidget::showImg(QImage image)
{
    this->image = image;
    if(!image.isNull())
    {
        QImage img(image);
        QImage simg = img.scaledToWidth(this->playLab->height(), Qt::SmoothTransformation);
        this->playLab->setPixmap(QPixmap::fromImage(simg));
        this->playLab->setScaledContents(true);
    }
}

void PlayVideoWidget::playHandover()
{
    isPlay = !isPlay;
    if(isPlay)
    {
        this->videoThread->setNeedSeek(false);//播放
        this->playBtn->setIcon(QIcon(":/image/player/播放器-暂停_44.png"));
    }else{
        this->videoThread->setNeedSeek(true);//暂停
        this->playBtn->setIcon(QIcon(":/image/player/播放器-播放_44.png"));
    }
}

void PlayVideoWidget::Changes(QString mulriple)
{
    if(mulriple == "0.5X")
    {
        this->videoThread->setSpeed(80);
    }else if(mulriple == "1.0X"){
        this->videoThread->setSpeed(40);
    }else if(mulriple == "2.0X"){
        this->videoThread->setSpeed(20);
    }else if(mulriple == "3.0X"){
        this->videoThread->setSpeed(10);
    }
}

void PlayVideoWidget::toDownload()
{

}

void PlayVideoWidget::picture()
{
    if(UserController::getInstance()->doUserIdStatus(this->userId) == 1)
    {
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
        emit updateImg();
    }else{
        QMessageBox::warning(this,"提示","当前还未登录，无法拍照");
    }
}
