#include "playbackwidget.h"
#include <QFile>
#include <QDebug>
#include "controller/videocontroller.h"
#include "controller/usercontroller.h"
#include "controller/logcontroller.h"
#include "data/video.h"
#include <QIcon>
#include <QMessageBox>
PlayBackWidget::PlayBackWidget(QWidget *parent) : QWidget(parent)
{
    this->loadQss();        //加载qss
    this->initControl();    //加载控件
    this->initConnect();    //加载链接
}

void PlayBackWidget::loadQss()
{
    QFile qss(":/qss/PlayBack.qss");
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

void PlayBackWidget::initControl()
{
    this->queryIo = false;
    this->pageNum = VideoController::getInstance()->doVideoNum();//总视频数量
    this->currentPage = 0;//当前页的查询下标
    this->pageCount = 1;//当前页
    //-------------------左----------start-------------------
    this->leftView = new QWidget(this);
    this->leftView->setObjectName("leftView");
        //声明布局
    this->leftLayout = new QVBoxLayout(this);
        //声明控件
    this->titleListWidget = new QListWidget;
    this->titleListWidget->addItem("视频回放");
    this->titleListWidget->addItem("照片列表");
    this->titleListWidget->setStyleSheet("height:40px;");
        //控件添加到布局
    this->leftLayout->addWidget(this->titleListWidget);
    this->leftLayout->addStretch(1);//弹簧
        //布局添加到窗口
    this->leftView->setLayout(this->leftLayout);
    //-------------------左-----------end--------------------
    //-------------------中----------start-------------------
    this->playVideoLab = new QLabel(this);
    this->playVideoLab->setMinimumSize(720,480);
    //-------------------中-----------end--------------------
    //-------------------右----------start-------------------
    this->rightView = new QWidget(this);
        //声明布局
    this->rightLayout = new QVBoxLayout(this);
        //声明控件
        //-------------------右上----------start-------------------
        this->rightUpView = new QWidget(this);
        this->rightUpLayout = new QHBoxLayout(this);
        //声明控件
        this->calendar = new QCalendarWidget;
        this->searchEdit = new QDateTimeEdit;
        this->searchEdit->setCalendarPopup(true);
        this->searchEdit->setCalendarWidget(this->calendar);
        this->searchEdit->setDisplayFormat("yyyy-MM-dd");
        this->searchEdit->setDateTime(QDateTime::currentDateTime());
        this->videoListBtn = new QPushButton("查询");
        this->clearTimeBtn = new QPushButton("取消");
        //控件添加到布局
        this->rightUpLayout->addWidget(this->searchEdit);
        this->rightUpLayout->addWidget(this->videoListBtn);
        this->rightUpLayout->addWidget(this->clearTimeBtn);
        this->rightUpView->setLayout(this->rightUpLayout);
        //-------------------右上-----------end--------------------
    this->videoListWidget = new QListWidget;
    this->videoListWidget->setLayoutDirection(Qt::LeftToRight);
    this->videoListWidget->setIconSize(QSize(140, 70));       // 图标大小
    this->videoListWidget->setResizeMode(QListView::Adjust);
    this->videoListWidget->setFocusPolicy(Qt::NoFocus);
    this->videoListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->videoListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->videoListWidget->setCursor(Qt::PointingHandCursor);
    //this->videoListWidget->setFixedSize(260,420);
    this->videoListWidget->setSpacing(0);
    QList<Video*> videoImgName = VideoController::getInstance()->doVideoName(6,0);
    //qDebug()<<"视频数量："<<videoImgName.size();
    for(int i=0;i<videoImgName.size();i++)
    {
        QListWidgetItem *imageItem = new QListWidgetItem(QIcon(videoImgName.at(i)->getVidemCoverPath()),
                                                         videoImgName.at(i)->getVideoName());
        this->videoListWidget->addItem(imageItem);
    }
        //-------------------右下----------start-------------------
        this->rightDownView = new QWidget(this);
        this->rightDownLayout = new QHBoxLayout(this);
        //声明控件
        this->pageEdit = new QLineEdit(this);
        this->GoBtn = new QPushButton("Go",this);
        this->GoBtn->setFixedSize(40,30);
        this->leftPageBtn = new QPushButton("<",this);
        this->leftPageBtn->setFixedSize(30,30);
        this->rightPageBtn = new QPushButton(">",this);
        this->rightPageBtn->setFixedSize(30,30);
        QString pageLabNum = "1/"+QString::number((this->pageNum/6)+1,10);
        this->PageLab = new QLabel(pageLabNum,this);
        this->topBtn = new QPushButton("<<",this);
        this->topBtn->setFixedSize(40,30);
        this->DownBtn = new QPushButton(">>",this);
        this->DownBtn->setFixedSize(40,30);
        //控件添加到布局
        this->rightDownLayout->addWidget(this->pageEdit);
        this->rightDownLayout->addWidget(this->GoBtn);
        this->rightDownLayout->addWidget(this->topBtn);
        this->rightDownLayout->addWidget(this->leftPageBtn);
        this->rightDownLayout->addWidget(this->PageLab);
        this->rightDownLayout->addWidget(this->rightPageBtn);
        this->rightDownLayout->addWidget(this->DownBtn);
        this->rightDownView->setLayout(this->rightDownLayout);
        //-------------------右下-----------end--------------------
        //控件添加到布局
    this->rightLayout->addWidget(this->rightUpView);
    this->rightLayout->addWidget(this->videoListWidget);
    this->rightLayout->addWidget(this->rightDownView);
        //布局添加到窗口
    this->rightView->setLayout(this->rightLayout);
    //-------------------右-----------end--------------------
    this->videoLayout = new QHBoxLayout(this);
    this->videoLayout->addWidget(this->playVideoLab,5);
    this->videoLayout->addWidget(this->rightView,2);
    this->videoLayout->setMargin(0);
    this->videoLayout->setSpacing(0);
    this->videoView = new QWidget(this);
    this->videoView->setLayout(this->videoLayout);
        //初始化图片列表页面
    this->imgWin = new ImgListWidget;
    this->playWin = new QStackedWidget(this);
        //将页面添加进去
    this->playWin->addWidget(this->videoView);
    this->playWin->addWidget(this->imgWin);

    this->totalLayout = new QHBoxLayout(this);
    this->totalLayout->addWidget(this->leftView,1);
    this->totalLayout->addWidget(this->playWin,7);

    this->videoThread = nullptr;
}

void PlayBackWidget::initConnect()
{
    connect(this->rightPageBtn,SIGNAL(clicked()),this,SLOT(rightPage()));
    connect(this->leftPageBtn,SIGNAL(clicked()),this,SLOT(leftPage()));
    connect(this->topBtn,SIGNAL(clicked()),this,SLOT(topPage()));
    connect(this->DownBtn,SIGNAL(clicked()),this,SLOT(DownPage()));
    connect(this->GoBtn,SIGNAL(clicked()),this,SLOT(GoPage()));
    connect(this->videoListBtn,SIGNAL(clicked()),this,SLOT(videoList()));
    connect(this->titleListWidget,SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(toWin(QListWidgetItem*)));
    connect(this->videoListWidget,SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(toPlayer(QListWidgetItem*)));
    connect(this->clearTimeBtn,SIGNAL(clicked()),this,SLOT(clearTime()));
}

void PlayBackWidget::setUserId(const QString &value)
{
    userId = value;
}

void PlayBackWidget::videoBack()
{
    if(this->videoThread != nullptr)
    {
        this->videoThread->setStop(true);
        this->videoThread->wait();
        this->videoThread->quit();
        this->videoThread->deleteLater();
    }
    //初始化回放线程
    QString videoName = VideoController::getInstance()->doVideoPath();
    qDebug()<<"回放线程videoName"<<videoName;
    if(videoName != "")
    {
        this->videoThread = new DecodeVideoThread();
        this->videoThread->setFilePath(videoName);
        this->videoThread->start();
        connect(this->videoThread,SIGNAL(sendImg(QImage)),this,SLOT(showImg(QImage)));
    }
}

void PlayBackWidget::clearTime()
{

    //修改状态为未查询
    this->queryIo = false;
    //添加全部视频信息
    QList<Video*> videoImgName = VideoController::getInstance()->doVideoName(6,0);
    //qDebug()<<"视频数量："<<videoImgName.size();
    this->pageNum = videoImgName.size();
    this->videoListWidget->clear();
    for(int i=0;i<videoImgName.size();i++)
    {
        QListWidgetItem *imageItem = new QListWidgetItem(QIcon(videoImgName.at(i)->getVidemCoverPath()),
                                                         videoImgName.at(i)->getVideoName());
        this->videoListWidget->addItem(imageItem);
    }
    this->pageCount = 1;
    this->pageNum = VideoController::getInstance()->doVideoNum();//总视频数量
    QString pageLabNum = QString::number(this->pageCount,10)+"/"+QString::number((this->pageNum/6)+1,10);
    this->PageLab->setText(pageLabNum);
}

void PlayBackWidget::updateImg()
{
    this->imgWin->updateImg();//刷新照片列表
}

void PlayBackWidget::videoLast()
{
    //qDebug()<<"当前选择的行号"<<this->videoListWidget->currentRow();
    if(this->videoListWidget->currentRow() == 0)
    {
        if(this->pageCount > 1)
        {
            this->leftPage();//翻到上一页
            this->videoListWidget->setCurrentRow(5);
        }else{
            QMessageBox::warning(this,"提示","已经是第一个视频了");
            return;
        }
    }else{
        this->videoListWidget->setCurrentRow(this->videoListWidget->currentRow()-1);
    }
    this->toPlayer(this->videoListWidget->currentItem());
}

void PlayBackWidget::videoNext()
{
    qDebug()<<((this->pageNum/6)+1);
    if(this->pageCount == ((this->pageNum/6)+1))
    {
        int count = this->videoListWidget->count();
        if(this->videoListWidget->currentRow() == (count-1))
        {
            QMessageBox::warning(this,"提示","已经是最后一个视频了");
            return;
        }
    }
    if(this->videoListWidget->currentRow() == 5)
    {
        if(this->pageCount < ((this->pageNum/6)+1))
        {
            this->rightPage();//翻到下一页
            this->videoListWidget->setCurrentRow(0);
        }
    }else{
        this->videoListWidget->setCurrentRow(this->videoListWidget->currentRow()+1);
    }
    this->toPlayer(this->videoListWidget->currentItem());
}

void PlayBackWidget::toPlayer(QListWidgetItem *imageItem)
{
    QString videoUrl = VideoController::getInstance()->doVideoNameAndPath(imageItem->text());
    //初始化播放界面
    if(nullptr == this->VideoWin)
    {
        this->VideoWin = new PlayVideoWidget;
        this->VideoWin->setUserId(this->userId);
        //根据视频名称查找视频路径
        this->VideoWin->setVideoName(imageItem->text());//传入视频名
        this->VideoWin->playStart(videoUrl);
        this->VideoWin->show();
    }else {
        this->VideoWin->setUserId(this->userId);
        this->VideoWin->setVideoName(imageItem->text());//传入视频名
        this->VideoWin->playStart(videoUrl);
        disconnect(this->VideoWin,SIGNAL(videoLast()),this,SLOT(videoLast()));
        disconnect(this->VideoWin,SIGNAL(videoNext()),this,SLOT(videoNext()));
        disconnect(this->VideoWin,SIGNAL(updateImg()),this,SLOT(updateImg()));
        this->VideoWin->show();
    }
    connect(this->VideoWin,SIGNAL(videoLast()),this,SLOT(videoLast()));
    connect(this->VideoWin,SIGNAL(videoNext()),this,SLOT(videoNext()));
    connect(this->VideoWin,SIGNAL(updateImg()),this,SLOT(updateImg()));
    //点播操作写入数据库
    QDateTime time = QDateTime::currentDateTime();
    QString timer = time.toString("yyyyMMddhhmmss");
    int user_id = UserController::getInstance()->doUserId(this->userId.toInt());
    QString operation = "播放"+imageItem->text();
    int res = LogController::getInstance()->doLog(user_id,operation,timer);
}

void PlayBackWidget::showImg(QImage image)
{
    this->image = image;
    if(!image.isNull())
    {
        QImage img(image);
        QImage simg = img.scaledToWidth(this->playVideoLab->height(), Qt::SmoothTransformation);
        this->playVideoLab->setPixmap(QPixmap::fromImage(simg));
        this->playVideoLab->setScaledContents(true);
    }
}

void PlayBackWidget::toWin(QListWidgetItem *usbItem)
{
    if(this->titleListWidget->currentRow() == 0)
    {
        this->playWin->setCurrentIndex(0);
    }else if(this->titleListWidget->currentRow() == 1){
        this->playWin->setCurrentIndex(1);
    }
}
//下一页
void PlayBackWidget::rightPage()
{
    //判断是否到达尾页
    if(this->pageCount < (this->pageNum/6)+1)
    {
        this->currentPage+=6;
        this->pageCount++;
        QList<Video*> videoImgName;
        if(this->queryIo)
        {
            videoImgName = VideoController::getInstance()->doVideoTime(this->dataTime,6,this->currentPage);
        }else{
            videoImgName = VideoController::getInstance()->doVideoName(6,this->currentPage);
        }
        //清空videoListWidget原有Item
        this->videoListWidget->clear();
        for(int i=0;i<videoImgName.size();i++)
        {
            QListWidgetItem *imageItem = new QListWidgetItem(QIcon(videoImgName.at(i)->getVidemCoverPath()),
                                                             videoImgName.at(i)->getVideoName());
            this->videoListWidget->addItem(imageItem);
        }
        QString pageLabNum = QString::number(this->pageCount,10)+"/"+QString::number((this->pageNum/6)+1,10);
        this->PageLab->setText(pageLabNum);
    }
}
//上一页
void PlayBackWidget::leftPage()
{
    if(this->pageCount > 1)
    {
        this->currentPage-=6;
        this->pageCount--;
        QList<Video*> videoImgName;
        if(this->queryIo)
        {
            videoImgName = VideoController::getInstance()->doVideoTime(this->dataTime,6,this->currentPage);
        }else{
            videoImgName = VideoController::getInstance()->doVideoName(6,this->currentPage);
        }
        //清空videoListWidget原有Item
        this->videoListWidget->clear();
        for(int i=0;i<videoImgName.size();i++)
        {
            QListWidgetItem *imageItem = new QListWidgetItem(QIcon(videoImgName.at(i)->getVidemCoverPath()),
                                                             videoImgName.at(i)->getVideoName());
            this->videoListWidget->addItem(imageItem);
        }
        QString pageLabNum = QString::number(this->pageCount,10)+"/"+QString::number((this->pageNum/6)+1,10);
        this->PageLab->setText(pageLabNum);
    }
}
//第一页
void PlayBackWidget::topPage()
{
    this->currentPage=0;
    this->pageCount=1;
    QList<Video*> videoImgName;
    if(this->queryIo)
    {
        videoImgName = VideoController::getInstance()->doVideoTime(this->dataTime,6,this->currentPage);
    }else{
        videoImgName = VideoController::getInstance()->doVideoName(6,this->currentPage);
    }
    //清空videoListWidget原有Item
    this->videoListWidget->clear();
    for(int i=0;i<videoImgName.size();i++)
    {
        QListWidgetItem *imageItem = new QListWidgetItem(QIcon(videoImgName.at(i)->getVidemCoverPath()),
                                                         videoImgName.at(i)->getVideoName());
        this->videoListWidget->addItem(imageItem);
    }
    QString pageLabNum = QString::number(this->pageCount,10)+"/"+QString::number((this->pageNum/6)+1,10);
    this->PageLab->setText(pageLabNum);
}
//最后一页
void PlayBackWidget::DownPage()
{
    this->pageCount=(this->pageNum/6)+1;
    this->currentPage = (this->pageCount-1)*6;
    QList<Video*> videoImgName;
    if(this->queryIo)
    {
        videoImgName = VideoController::getInstance()->doVideoTime(this->dataTime,6,this->currentPage);
    }else{
        videoImgName = VideoController::getInstance()->doVideoName(6,this->currentPage);
    }
    //清空videoListWidget原有Item
    this->videoListWidget->clear();
    for(int i=0;i<videoImgName.size();i++)
    {
        QListWidgetItem *imageItem = new QListWidgetItem(QIcon(videoImgName.at(i)->getVidemCoverPath()),
                                                         videoImgName.at(i)->getVideoName());
        this->videoListWidget->addItem(imageItem);
    }
    QString pageLabNum = QString::number(this->pageCount,10)+"/"+QString::number((this->pageNum/6)+1,10);
    this->PageLab->setText(pageLabNum);
}
//跳转指定页
void PlayBackWidget::GoPage()
{
    int GoNum = this->pageEdit->text().toInt();
    if(GoNum>0 && GoNum <= ((this->pageNum/6)+1))
    {
        this->pageCount = GoNum;
        this->currentPage = (this->pageCount-1)*6;
        QList<Video*> videoImgName;
        if(this->queryIo)
        {
            videoImgName = VideoController::getInstance()->doVideoTime(this->dataTime,6,this->currentPage);
        }else{
            videoImgName = VideoController::getInstance()->doVideoName(6,this->currentPage);
        }
        //清空videoListWidget原有Item
        this->videoListWidget->clear();
        for(int i=0;i<videoImgName.size();i++)
        {
            QListWidgetItem *imageItem = new QListWidgetItem(QIcon(videoImgName.at(i)->getVidemCoverPath()),
                                                             videoImgName.at(i)->getVideoName());
            this->videoListWidget->addItem(imageItem);
        }
        QString pageLabNum = QString::number(this->pageCount,10)+"/"+QString::number((this->pageNum/6)+1,10);
        this->PageLab->setText(pageLabNum);
    }
}
//根据日期筛选视频
void PlayBackWidget::videoList()
{
    //更改状态为正在查询
    this->queryIo = true;
    this->dataTime = this->searchEdit->text();
    dataTime.remove("-");
    qDebug()<<dataTime;
    QList<Video*> videoImgName = VideoController::getInstance()->doVideoTime(this->dataTime);
    qDebug()<<videoImgName.size();
    if(videoImgName.size() > 0)
    {
        //更改总页和当前页
        this->pageCount=1;
        this->pageNum = videoImgName.size();
        QString pageLabNum = QString::number(this->pageCount,10)+"/"+QString::number((this->pageNum/6)+1,10);
        this->PageLab->setText(pageLabNum);
        this->videoListWidget->clear();
        //查询分页信息
        QList<Video*> videoImgNamePage = VideoController::getInstance()->doVideoTime(this->dataTime,6,0);
        for(int i=0;i<videoImgNamePage.size();i++)
        {
            QListWidgetItem *imageItem = new QListWidgetItem(QIcon(videoImgNamePage.at(i)->getVidemCoverPath()),
                                                             videoImgNamePage.at(i)->getVideoName());
            this->videoListWidget->addItem(imageItem);
        }
    }else {
        QMessageBox::warning(this,"提示","当前日期无视频信息");
    }
}
