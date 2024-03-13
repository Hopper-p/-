#include "bootview.h"
#include <QThread>
#include <QDebug>
#include <QList>
#include "controller/settingcontroller.h"
#include "data/setting.h"
#include <QMessageBox>
#include <QDir>
BootView::BootView()
{
    //设置大小，背景
    this->setFixedSize(600,350);
    this->setWindowTitle("开机动画");
    this->setBackgroundBrush(QBrush(QPixmap(":/image/BootImg/BackgroundImg.png")));
    //创建场景
    this->mySence = new QGraphicsScene;
    this->setScene(this->mySence);
    this->setSceneRect(0,0,this->width()-2,this->height()-2);
    //创建图元
    this->item1 = new BootItem(1,":/image/BootImg/leiftImg.png");
    //设置图元位置
    this->item1->setPos(20,this->height()/2);
    //场景添加图元
    this->mySence->addItem(this->item1);
    //创建图元
    this->item2 = new BootItem(2,":/image/BootImg/rightImg.png");
    //设置图元位置
    this->item2->setPos(580,this->height()/2);
    this->mySence->addItem(this->item2);
    //创建定时器
    this->timer = new QTimer();
    this->timer->start(20);
    connect(this->timer,SIGNAL(timeout()),this->mySence,SLOT(advance()));
    connect(this->item1,SIGNAL(stopMove()),this,SLOT(stopMove()));
    this->setWin = new SettingWidget;
    connect(this->setWin,SIGNAL(backToMainWidget()),this,SLOT(showMain()));
    this->item3 = new BootItem(3,":/image/BootImg/LoveImg.png");    
}

void BootView::stopMove()
{
    //停止定时器
    this->timer->stop();
    //显示爆炸图片
    this->item3->setPos(this->width()/2,240);
    this->mySence->addItem(this->item3);
    this->state = 3;
    this->timer->stop();
    //跳转主界面窗口
    QTimer::singleShot(1000, this, &BootView::showMainWidget);
}

void BootView::showMainWidget()
{
    QThread::sleep(1);
    QList<Setting*> settingList = SettingController::getInstance()->initSettingData();
    if(settingList.size() == 1)
    {
        QDir vStorageDir(settingList.at(0)->getVideoPath());
        QDir iStorageDir(settingList.at(0)->getImagePath());
        if(vStorageDir.exists() || iStorageDir.exists())
        {
            this->showMain();
        }else{
            this->hide();
            setWin->show();
        }
    }else {
        this->hide();
        setWin->show();
    }
}

void BootView::showMain()
{
    delete this->setWin;
    this->close();
    MainWidget *mainWin = new MainWidget;
    mainWin->show();
}
