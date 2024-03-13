#include "settingwidget.h"
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QCameraInfo>
#include <QMessageBox>
#include <QDir>
#include "controller/settingcontroller.h"
SettingWidget::SettingWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowIcon(QIcon(":/image/icon/SettingsIcon.png"));//设置图标
    this->setWindowTitle("设置");  //设置标题
    this->setFixedSize(500,400);   //控制大小
    this->loadQss();               //加载qss
    this->initControl();           //加载控件
    this->initConnect();           //加载链接
}
void SettingWidget::loadQss()
{
    QFile qss(":/qss/SettingWidget.qss");
    if( qss.open(QFile::ReadOnly))
    {
        qDebug()<<endl<<"SettingWidget::loadQss:open success";
        QString style = QLatin1String(qss.readAll());
        this->setStyleSheet(style);
        qss.close();
    }else{
        qDebug()<<endl<<"SettingWidget::loadQss:Open failed";
    }
}

void SettingWidget::initControl()
{
    //声明QLabel控件
    this->vStorageLab = new QLabel("视频存储位置：",this);
    this->vStorageLab->move(80,50);
    this->iStorageLab = new QLabel("图片存储位置：",this);
    this->iStorageLab->move(80,120);
    this->acquisitionLab = new QLabel("采集时间间隔：",this);
    this->acquisitionLab->move(80,190);
    this->menuCameraLab = new QLabel("摄像头配置：",this);
    this->menuCameraLab->move(80,260);
    //声明QLineEdit控件
    this->vStorageEdit = new QLineEdit(this);
    this->vStorageEdit->move(190,40);
    this->vStorageEdit->setReadOnly(true);
    this->iStorageEdit = new QLineEdit(this);
    this->iStorageEdit->move(190,110);
    this->iStorageEdit->setReadOnly(true);
    //声明QComboBox控件
    this->acquisitionCbx = new QComboBox(this);
    this->acquisitionCbx->move(190,180);
    this->acquisitionCbx->addItem("1分钟");
    this->acquisitionCbx->addItem("2分钟");
    this->acquisitionCbx->addItem("3分钟");
    this->menuCameraCbx = new QComboBox(this);

    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

    for(int i=0;i<cameras.size();i++)
    {
        this->menuCameraCbx->addItem(cameras[i].description());
    }
    this->menuCameraCbx->move(190,250);
    //声明QPushButton控件
    this->vStorageBtn = new QPushButton("...",this);
    this->vStorageBtn->move(375,40);
    this->vStorageBtn->setObjectName("vStorageBtn"); // 设置按钮的名称
    this->vStorageBtn->setStyleSheet("width:35;height:35;");
    this->iStorageBtn = new QPushButton("...",this);
    this->iStorageBtn->move(375,110);
    this->iStorageBtn->setObjectName("iStorageBtn"); // 设置按钮的名称
    this->iStorageBtn->setStyleSheet("width:35;height:35;");
    this->okBtn = new QPushButton("确定",this);
    this->okBtn->move(100,320);
    this->outBtn = new QPushButton("取消",this);
    this->outBtn->move(300,320);

    settingList = SettingController::getInstance()->initSettingData();
    //qDebug()<<"settingList size"<<settingList.size();
    if(settingList.size() == 1)
    {

        this->vStorageEdit->setText(settingList.at(0)->getVideoPath());
        this->iStorageEdit->setText(settingList.at(0)->getImagePath());
        if(settingList.at(0)->getIntervalTime() == 1500)
        {
            this->acquisitionCbx->setCurrentIndex(0);
        }else if (settingList.at(0)->getIntervalTime() == 3000) {
            this->acquisitionCbx->setCurrentIndex(1);
        }else if (settingList.at(0)->getIntervalTime() == 4500) {
            this->acquisitionCbx->setCurrentIndex(2);
        }
        //检查本机是否有当前目录信息
        QDir vStorageDir(settingList.at(0)->getVideoPath());
        if(!vStorageDir.exists())
        {
            this->vStorageEdit->setText("");
        }
        QDir iStorageDir(settingList.at(0)->getImagePath());
        if(!iStorageDir.exists())
        {
            this->iStorageEdit->setText("");
        }
    }
}

void SettingWidget::initConnect()
{
    connect(this->vStorageBtn, &QPushButton::clicked, this, &SettingWidget::showDialog);
    connect(this->iStorageBtn, &QPushButton::clicked, this, &SettingWidget::showDialog);
    connect(this->okBtn,SIGNAL(clicked()),this,SLOT(doWrite()));
    connect(this->outBtn,SIGNAL(clicked()),this,SLOT(closeThis()));
}

void SettingWidget::showDialog()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender()); // 获取发出信号的QPushButton对象
    QString btnName = button->objectName(); // 获取按钮的名称
    qDebug() << btnName;

    QString dir = QFileDialog::getExistingDirectory(this, "Open folder", "/home");
    if (!dir.isEmpty())
    {
        if (btnName == "vStorageBtn")
        {
            this->vStorageEdit->setText(dir);
        }
        else if (btnName == "iStorageBtn")
        {
            this->iStorageEdit->setText(dir);
        }
    }
}

void SettingWidget::doWrite()
{
    QString videoPath = this->vStorageEdit->text();
    QString imagePath = this->iStorageEdit->text();
    int time;
    switch (this->acquisitionCbx->currentIndex()) {
    case 0:
        time = 1500;
        break;
    case 1:
        time = 3000;
        break;
    case 2:
        time = 4500;
        break;
    }
    QString cameraName = this->menuCameraCbx->currentText();
    if(videoPath == "")
    {
        QMessageBox::warning(this,"错误","视频存储路径未选择");
        return;
    }else if(imagePath == ""){
        QMessageBox::warning(this,"错误","图片存储路径未选择");
        return;
    }
    int res = SettingController::getInstance()->doSetting(videoPath,imagePath,time,cameraName);
    if(res == 0)
    {
        QMessageBox::about(this,"成功","设置完毕，即将跳转至主页");
        emit backToMainWidget();
    }
}

void SettingWidget::closeThis()
{
    this->close();
}
