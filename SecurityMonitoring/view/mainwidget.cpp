#include "mainwidget.h"
#include <QFile>
#include <QDebug>
#include <QList>
#include "data/setting.h"
#include "controller/usercontroller.h"
#include "controller/logcontroller.h"
#include <QMessageBox>
MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    this->loginStaus = false;
    this->loadQss();        //加载qss
    this->initControl();    //加载控件
    this->initConnect();    //加载链接
}


//加载qss
void MainWidget::loadQss()
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
//加载qss
void MainWidget::initControl()
{
    //创建整个窗口样式
    this->resize(1200,700);
    this->setWindowTitle("XXX安防系统");
    //创建窗口布局
    //-------------------上边----------start-------------------
    this->topView = new QWidget(this);
    this->topView->setObjectName("topview");
        //创建水平布局
    this->topLayout = new QHBoxLayout(this);
        //创建控件
    this->imgLogoLab = new QLabel(this);
    this->imgLogoLab->setStyleSheet("border-image:url(:/image/logoImg.png);");
    this->imgLogoLab->setMinimumSize(60,60);//设置最小尺寸
    this->titleLab = new QLabel("XXX安防系统",this);
    this->titleLab->setStyleSheet("font-size:40px");
    this->monitorToggleBtn = new QPushButton("监控模式",this);
    this->monitorToggleBtn->setStyleSheet("background-color:#fb7299");
    this->playBackToggleBtn = new QPushButton("回放模式",this);
    this->logQueryBtn = new QPushButton("日志查询",this);
    this->settingsBtn = new QPushButton("系统设置",this);
    this->loginBtn = new QPushButton("登录",this);
    this->timer = new QTimer(this);
    this->timer->start(1000);
    this->timeLab = new QLabel(this->getNowTime());//系统时间
        //控件添加到布局中
    this->topLayout->addWidget(this->imgLogoLab);
    this->topLayout->addWidget(this->titleLab);
    this->topLayout->addStretch(1);//弹簧
    this->topLayout->addWidget(this->monitorToggleBtn);//监控模式
    this->topLayout->addWidget(this->playBackToggleBtn);//回放模式
    this->topLayout->addWidget(this->logQueryBtn);//日志查询
    this->topLayout->addWidget(this->settingsBtn);//系统设置
    this->topLayout->addWidget(this->loginBtn);//登录
    this->topLayout->addWidget(this->timeLab);//系统时间
        //添加完控件的布局添加到View内
    this->topView->setLayout(this->topLayout);
    //-------------------上边-----------end--------------------
    //初始化要切换的页面
    this->monitorWin = new MonitorWidget;
    this->playBackWin = new PlayBackWidget;
    this->logWin = new LogWidget;
    //-------------------下边----------start-------------------
    this->mainView = new QWidget(this);
    this->mainLayout = new QHBoxLayout(this);
    this->mainWin = new QStackedWidget(this);
        //将页面添加进去
    this->mainWin->addWidget(this->monitorWin);
    this->mainWin->addWidget(this->playBackWin);
    this->mainWin->addWidget(this->logWin);
    this->mainLayout->addWidget(this->mainWin);
    this->mainView->setLayout(this->mainLayout);
    //-------------------下边-----------end--------------------
    //将上下View添加到垂直布局中
    this->totalLayout = new QVBoxLayout(this);
    this->totalLayout->addWidget(this->topView,1);
    this->totalLayout->addWidget(this->mainView,7);
    this->totalLayout->setMargin(0);
    this->totalLayout->setSpacing(0);
    //初始化子界面
    this->settingWin = new SettingWidget;
    this->loginWin = new LoginWidget;
}
//加载链接
void MainWidget::initConnect()
{
    //显示系统时间
    connect(this->timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    //显示设置界面
    connect(this->settingsBtn,SIGNAL(clicked()),this,SLOT(showSetting()));
    //设置界面确认后返回主界面
    connect(this->settingWin,SIGNAL(backToMainWidget()),this,SLOT(showMain()));
    //登录界面返回主界面
    connect(this->loginWin,SIGNAL(backToMain(QString)),this,SLOT(showMain(QString)));
    //跳转登录页面
    connect(this->loginBtn,SIGNAL(clicked()),this,SLOT(showLoginWin()));
    //切换到监控界面
    connect(this->monitorToggleBtn,SIGNAL(clicked()),this,SLOT(showMonitor()));
    //切换到回放界面
    connect(this->playBackToggleBtn,SIGNAL(clicked()),this,SLOT(showPlayBack()));
    //拍照后刷新照片列表
    connect(this->monitorWin,SIGNAL(updateImg()),this,SLOT(updateImg()));
    //切换到日志界面
    connect(this->logQueryBtn,SIGNAL(clicked()),this,SLOT(showLog()));
}

QString MainWidget::getNowTime()
{
    QDateTime time = QDateTime::currentDateTime();
    return time.toString("yyyy-MM-dd\n hh:mm:ss");
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    //将当前登录的用户状态改为未登录
    int res = UserController::getInstance()->doNotLogin(this->userId);
    //调用写尾帧操作
    this->monitorWin->writeFrame();
    QThread::msleep(1000);
}

void MainWidget::updateImg()
{
    this->playBackWin->updateImg();
}
void MainWidget::timerUpdate()
{
    this->timeLab->setText(this->getNowTime());
}

void MainWidget::showMain()
{
    this->settingWin->close();
    //记录修改设置的用户
    QDateTime time = QDateTime::currentDateTime();
    QString timer = time.toString("yyyyMMddhhmmss");
    int user_id = UserController::getInstance()->doUserId(this->userId.toInt());
    int res = LogController::getInstance()->doLog(user_id,"修改设置",timer);
}
void MainWidget::showMain(QString userId)
{
    this->loginStaus = true;
    this->userId = userId;
    //将当前用户ID传入MonitorWidget
    this->monitorWin->setUserId(userId);
    this->playBackWin->setUserId(userId);
    this->loginWin->close();
    QString userName = UserController::getInstance()->doUserName(userId);
    this->loginBtn->setText(userName);
    //qDebug()<<"MainWidget::showMain 用户名："<<userName;
    //this->userNameLab->setText("你好，"+userName);//将用户名添加到界面中
    //this->loginBtn->setVisible(false);//隐藏登录按钮
}
void MainWidget::showSetting()
{
    this->settingWin->show();
}

void MainWidget::showLoginWin()
{

    if(this->loginBtn->text() != "登录")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,tr("退出登录"),tr("你是否要退出登录"),QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        if(reply == QMessageBox::Ok)
        {
            int res = UserController::getInstance()->doNotLogin(this->userId);
            if(res == 0)
            {
                this->loginBtn->setText("登录");
            }
        }
    }else {
        this->loginWin->show();
    }
}

void MainWidget::showMonitor()
{
    this->playBackToggleBtn->setStyleSheet("background-color:#f6f7f8");
    this->logQueryBtn->setStyleSheet("background-color:#f6f7f8");
    this->monitorToggleBtn->setStyleSheet("background-color:#fb7299");
    this->mainWin->setCurrentIndex(0);
}

void MainWidget::showPlayBack()
{
    if(this->loginStaus)
    {
        this->playBackToggleBtn->setStyleSheet("background-color:#fb7299");
        this->logQueryBtn->setStyleSheet("background-color:#f6f7f8");
        this->monitorToggleBtn->setStyleSheet("background-color:#f6f7f8");
        this->mainWin->setCurrentIndex(1);
        //刷新回放页面的最新视频
        this->playBackWin->videoBack();
    }else {
        QMessageBox::warning(this,"提示","当前还未登录，无法查看回放");
    }

}

void MainWidget::showLog()
{
    if(this->loginStaus)
    {
        this->playBackToggleBtn->setStyleSheet("background-color:#f6f7f8");
        this->logQueryBtn->setStyleSheet("background-color:#fb7299");
        this->monitorToggleBtn->setStyleSheet("background-color:#f6f7f8");
        this->logWin->updateTable();//刷新日志表信息
        this->mainWin->setCurrentIndex(2);
    }else {
        QMessageBox::warning(this,"提示","当前还未登录，无法查看日志");
    }
}

