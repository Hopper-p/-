#include "downwidget.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include "controller/usercontroller.h"
#include "controller/logcontroller.h"
#include <QDateTime>
DownWidget::DownWidget(QWidget *parent) : QWidget(parent)
{
    this->initControl();
}

void DownWidget::initControl()
{
    this->resize(400,200);
    //-------------------上----------start-------------------
    this->topview = new QWidget(this);
    this->topLayout = new QHBoxLayout(this);
        //创建控件
    this->pathLab = new QLabel("文件路径",this);
    this->pathEdit = new QLineEdit(this);
    this->urlBtn = new QPushButton("选择路径",this);
        //控件添加到布局
    this->topLayout->addWidget(this->pathLab);
    this->topLayout->addWidget(this->pathEdit);
    this->topLayout->addWidget(this->urlBtn);
        //布局添加到窗口中
    this->topview->setLayout(this->topLayout);
    //-------------------上-----------end--------------------
    //-------------------中----------start-------------------
    this->middleView = new QWidget(this);
    this->middLayout = new QHBoxLayout(this);
        //创建控件
    this->nameLab = new QLabel("文件名称",this);
    this->nameEdit = new QLineEdit(this);
    this->urlBox1 = new QComboBox(this);
    this->urlBox1->addItem(".mp4");
    this->urlBox1->addItem(".avi");
        //控件添加到布局
    this->middLayout->addWidget(this->nameLab);
    this->middLayout->addWidget(this->nameEdit);
    this->middLayout->addWidget(this->urlBox1);
        //布局添加到窗口中
    this->middleView->setLayout(this->middLayout);
    //-------------------中-----------end--------------------
    //-------------------下----------start-------------------
    this->bottomView = new QWidget(this);
    this->bottomLayout = new QHBoxLayout(this);
        //创建控件
    this->okBtn = new QPushButton("确定",this);
    this->outBtn = new QPushButton("取消",this);
        //控件添加到布局
    this->bottomLayout->addWidget(this->okBtn);
    this->bottomLayout->addWidget(this->outBtn);
        //布局添加到窗口中
    this->bottomView->setLayout(this->bottomLayout);
    //-------------------下-----------end--------------------
    this->totalLayout = new QVBoxLayout(this);
    this->totalLayout->addWidget(this->topview);
    this->totalLayout->addWidget(this->middleView);
    this->totalLayout->addWidget(this->bottomView);
    //初始化播放线程
    this->TransCode = new TransCodeToNormalThread;
    connect(this->urlBtn,SIGNAL(clicked()),this,SLOT(showDialog()));
    connect(this->okBtn,SIGNAL(clicked()),this,SLOT(downFile()));
}

void DownWidget::setVideoName(const QString &value)
{
    videoName = value;
}

void DownWidget::setVideoUrl(const QString &value)
{
    videoUrl = value;
}

void DownWidget::setUserId(const QString &value)
{
    userId = value;
}

void DownWidget::showDialog()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Open folder", "/home");
    if (!dir.isEmpty())
    {
        this->pathEdit->setText(dir);
    }
}

void DownWidget::downFile()
{
    QString url = this->pathEdit->text()+"/"+this->nameEdit->text()+this->urlBox1->currentText();

    this->TransCode->setSavePath(url);
    this->TransCode->setOriPath(this->videoUrl);
    this->TransCode->prepareWork();
    this->TransCode->start();
    QMessageBox::about(this,"成功","导出成功");
    //导出操作写入数据库
    QDateTime time = QDateTime::currentDateTime();
    QString timer = time.toString("yyyyMMddhhmmss");
    int user_id = UserController::getInstance()->doUserId(this->userId.toInt());
    QString operation = "导出"+this->nameEdit->text();
    int res = LogController::getInstance()->doLog(user_id,operation,timer);
    this->close();
}
