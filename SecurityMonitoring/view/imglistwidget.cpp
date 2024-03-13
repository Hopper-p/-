#include "imglistwidget.h"
#include <QFile>
#include <QDebug>
#include "controller/imagecontroller.h"
#include <QFileInfo>
#include <QObject>
ImgListWidget::ImgListWidget(QWidget *parent) : QWidget(parent)
{
    this->page_num = 0;     //当前页数
    this->isShowSingle = false;
    this->imageNum = ImageController::getInstance()->doImageNum();//图片数量
    if(this->imageNum%9 == 0)
    {
        this->total_page_num = (this->imageNum/9)-1;//总页数
    }else {
        this->total_page_num = this->imageNum/9;
    }
    this->loadQss();        //加载qss
    this->initControl();    //加载控件
    this->initConnect();    //加载链接
    this->updateImg();      //加载图片列表
}

void ImgListWidget::loadQss()
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

void ImgListWidget::initControl()
{
    //-------------------左----------start-------------------
    this->leftView = new QWidget(this);
    this->leftLayout = new QVBoxLayout(this);
        //-------------------左上----------start-------------------
        this->leftUpView = new QWidget(this);
        this->leftUpView->setObjectName("rightUpView");
        this->leftUpLayout = new QGridLayout(this);
            //声明控件
        for (int j=0;j<9;j++)
        {
            this->imgLabs[j] = new QLabel(this);
            this->imgLabs[j]->installEventFilter(this);
        }
        this->leftUpLayout->setSpacing(1);
        this->leftUpLayout->addWidget(this->imgLabs[0],0,0);
        this->leftUpLayout->addWidget(this->imgLabs[1],0,1);
        this->leftUpLayout->addWidget(this->imgLabs[2],0,2);
        this->leftUpLayout->addWidget(this->imgLabs[3],1,0);
        this->leftUpLayout->addWidget(this->imgLabs[4],1,1);
        this->leftUpLayout->addWidget(this->imgLabs[5],1,2);
        this->leftUpLayout->addWidget(this->imgLabs[6],2,0);
        this->leftUpLayout->addWidget(this->imgLabs[7],2,1);
        this->leftUpLayout->addWidget(this->imgLabs[8],2,2);
        this->leftUpView->setLayout(this->leftUpLayout);
        //-------------------左上-----------end--------------------
    this->leftLayout->addWidget(this->leftUpView);
    this->leftLayout->setMargin(0);
    this->leftLayout->setSpacing(0);
    this->leftView->setLayout(this->leftLayout);
    //-------------------左-----------end--------------------
    //-------------------右----------start-------------------
    this->rightView = new QWidget(this);
    this->rightLayout = new QVBoxLayout(this);
        //声明控件
    //声明控件
    this->queryView = new QWidget(this);
    this->queryLayout = new QHBoxLayout(this);
    this->calendar = new QCalendarWidget;
    this->searchEdit = new QDateTimeEdit;
    this->searchEdit->setCalendarPopup(true);
    this->searchEdit->setCalendarWidget(this->calendar);
    this->searchEdit->setDisplayFormat("yyyy-MM-dd");
    this->searchEdit->setDateTime(QDateTime::currentDateTime());
    this->queryLayout->addWidget(this->searchEdit);
    this->queryView->setLayout(this->queryLayout);

    this->queryBtnView = new QWidget(this);
    this->queryBtnLayout = new QHBoxLayout(this);
    this->videoListBtn = new QPushButton("查询");
    this->clearTimeBtn = new QPushButton("取消查询");
    this->queryBtnLayout->addWidget(this->videoListBtn);
    this->queryBtnLayout->addWidget(this->clearTimeBtn);
    this->queryBtnLayout->setMargin(0);
    this->queryBtnLayout->setSpacing(0);
    this->queryBtnView->setLayout(this->queryBtnLayout);


    this->imgNameLab = new QLabel("图片名称",this);
    this->imgNameLabel = new QLabel(this);
    this->imgSizeLab = new QLabel("图片大小",this);
    this->imgSizeLabel = new QLabel(this);
    this->imgDimLab = new QLabel("图片尺寸",this);
    this->imgDimLabel = new QLabel(this);
    this->rightLayout->addWidget(this->queryView);
    this->rightLayout->addWidget(this->queryBtnView);
    this->rightLayout->addWidget(this->imgNameLab);
    this->rightLayout->addWidget(this->imgNameLabel);
    this->rightLayout->addWidget(this->imgSizeLab);
    this->rightLayout->addWidget(this->imgSizeLabel);
    this->rightLayout->addWidget(this->imgDimLab);
    this->rightLayout->addWidget(this->imgDimLabel);
    this->rightLayout->setMargin(0);
    this->rightLayout->setSpacing(0);
    this->rightLayout->addStretch(1);//弹簧
    this->rightView->setLayout(this->rightLayout);
    //-------------------右-----------end--------------------
    this->totalLayout = new QHBoxLayout(this);
    this->totalLayout->addWidget(this->leftView,8);
    this->totalLayout->addWidget(this->rightView,1);
    this->totalLayout->setMargin(0);
    this->totalLayout->setSpacing(0);
}

void ImgListWidget::initConnect()
{

}

void ImgListWidget::updateImg()
{
    //加载图片数据
    QList<Tbl_image *> imgList = ImageController::getInstance()->doImageData(9,this->page_num);
    qDebug()<<"图片数量"<<imgList.size();
    for (int i=0;i<imgList.size();i++)
    {
        // 设置图片
        QPixmap pixmap(imgList.at(i)->getImage_path());
        this->imgLabs[i]->setPixmap(pixmap.scaledToWidth(200, Qt::SmoothTransformation));
        this->imgLabs[i]->setScaledContents(true);
        this->imgLabs[i]->setProperty("img_name",imgList.at(i)->getImage_name());
        this->imgLabs[i]->setProperty("img_path",imgList.at(i)->getImage_path());
        this->imgLabs[i]->setProperty("img_create_time",imgList.at(i)->getVideo_create_time());
        this->imgLabs[i]->installEventFilter(this);
    }
}

bool ImgListWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonDblClick)
    {
        int label_index = -1;
        //找到被双击的QLabel的索引
        for(int i = 0; i < 9; i++)
        {
            if(watched == imgLabs[i])
            {
                label_index = i;
                break;
            }
        }
        if(label_index != -1)
        {
            //如果标志位为false，即当前状态不是最大状态，则将当前双击的QLabel放大
            if(!isShowSingle)
            {
                for (int i=0; i < this->leftUpLayout->count(); i++)
                {
                    this->leftUpLayout->removeWidget(this->imgLabs[i]);
                    this->imgLabs[i]->setVisible(false);
                }
                for (int i=0; i < 9; i++)
                {
                    if(i == label_index)
                    {
                        this->leftUpLayout->addWidget(this->imgLabs[i], 0, 0);
                        this->imgLabs[i]->setVisible(true);
                    }
                    else {
                        this->leftUpLayout->removeWidget(this->imgLabs[i]);
                        this->imgLabs[i]->setVisible(false);
                    }
                }
                this->leftUpLayout->setRowStretch(0, 1);
                this->leftUpLayout->setRowStretch(1, 0);
                this->leftUpLayout->setRowStretch(2, 0);
                this->leftUpLayout->setColumnStretch(0, 1);
                this->leftUpLayout->setColumnStretch(1, 0);
                this->leftUpLayout->setColumnStretch(2, 0);
                this->isShowSingle = true;
            }else{//恢复9宫格布局
                for (int i=0; i < this->leftUpLayout->count(); i++)
                {
                    this->leftUpLayout->removeWidget(this->imgLabs[i]);
                    this->imgLabs[i]->setVisible(false);
                }
                for (int i=0; i < 9; i++)
                {
                    this->leftUpLayout->addWidget(this->imgLabs[i], i / 3, i % 3);
                    this->imgLabs[i]->setVisible(true);
                }
                this->leftUpLayout->setRowStretch(0, 1);
                this->leftUpLayout->setRowStretch(1, 1);
                this->leftUpLayout->setRowStretch(2, 1);
                this->leftUpLayout->setColumnStretch(0, 1);
                this->leftUpLayout->setColumnStretch(1, 1);
                this->leftUpLayout->setColumnStretch(2, 1);
                this->isShowSingle = false;
            }
        }
    }
    if(event->type()==QEvent::MouseButtonPress)
    {
        int label_index = -1;
        //找到被单击的QLabel的索引
        for(int i = 0; i < 9; i++)
        {
            if(watched == imgLabs[i])
            {
                label_index = i;
                break;
            }
        }
        qDebug()<<label_index;
        QLabel *label = this->imgLabs[label_index];
        QFileInfo fileInfo(label->property("img_path").toString());
        // 获取图片大小（以KB为单位）
        qint64 fileSize = fileInfo.size() / 1024;
        // 获取图片的宽度和高度
        QImage image(label->property("img_path").toString());
        int width = image.width();
        int height = image.height();
        // 输出图片的大小和尺寸
        qDebug() << "图片大小: " << fileSize << "KB";
        qDebug() << "图片宽度: " << width;
        qDebug() << "图片高度: " << height;
        this->imgNameLabel->setText(label->property("img_name").toString());
        this->imgSizeLabel->setText(QString::number(fileInfo.size() / 1024) + "KB");
        this->imgDimLabel->setText(QString::number(image.width()) + "x" + QString::number(image.height()));
    }
    return QWidget::eventFilter(watched,event); //返回父类的事件过滤函数
}

void ImgListWidget::wheelEvent(QWheelEvent *event)
{
    // 根据滚轮的方向来切换图片
    if (event->angleDelta().y() > 0)
    {
        // 向上滚动
        this->page_num = (this->page_num-1 < 0) ? 0: this->page_num -= 1;
    }else{
        this->page_num = (this->page_num + 1 > this->total_page_num) ? this->total_page_num: this->page_num + 1;
    }
    //加载图片数据
    QList<Tbl_image *> imgList = ImageController::getInstance()->doImageData(9,this->page_num);
    qDebug()<<"图片数量"<<imgList.size();
    for (int i=0;i<9;i++) {
        this->imgLabs[i]->clear();
    }
    for (int i=0;i<imgList.size();i++)
    {
        QImage img;
        img.load(imgList.at(i)->getImage_path());
        QImage simg = img.scaledToWidth(240, Qt::SmoothTransformation);
        this->imgLabs[i]->setPixmap(QPixmap::fromImage(simg));
        this->imgLabs[i]->setScaledContents(true);
    }
}
