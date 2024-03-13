#include "logwidget.h"
#include <QFile>
#include <QDebug>
#include <QHeaderView>
#include "controller/logcontroller.h"
LogWidget::LogWidget(QWidget *parent) : QWidget(parent)
{
    this->loadQss();        //加载qss
    this->initControl();    //加载控件
    this->updateTable();    //加载数据
    this->initConnect();    //加载链接
}

void LogWidget::loadQss()
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

void LogWidget::initControl()
{
    this->count =13;
    this->pageNum=0;
    this->logListWidget = new QListWidget(this);
    this->logListWidget->addItem("本地日志");
    this->rightView = new QWidget(this);
    this->rightLayout = new QVBoxLayout(this);
    this->logTable = new QTableWidget(13,4,this);
    this->logTable->setHorizontalHeaderLabels(QStringList() << "日志编号" << "用户ID" << "操作事件"<<"操作时间");
    //设置表格数据区内的所有单元格都不允许编辑
    this->logTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置表格为自适应布局
    this->logTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->logTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->logTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 隐藏垂直表头（行号）
    this->logTable->verticalHeader()->setVisible(false);
    this->rightDownView = new QWidget(this);
    this->rightDownLayout = new QHBoxLayout(this);
    this->leftBtn = new QPushButton("<",this);
    this->rightBtn = new QPushButton(">",this);
    this->rightDownLayout->addWidget(this->leftBtn);
    this->rightDownLayout->addWidget(this->rightBtn);
    this->rightDownView->setLayout(this->rightDownLayout);
    this->rightLayout->addWidget(this->logTable,9);
    this->rightLayout->addWidget(this->rightDownView,1);
    this->rightLayout->setMargin(0);
    this->rightLayout->setSpacing(0);
    this->rightView->setLayout(this->rightLayout);

    this->totaLayout = new QHBoxLayout(this);
    this->totaLayout->addWidget(this->logListWidget,1);
    this->totaLayout->addWidget(this->rightView,8);
    this->totaLayout->setMargin(0);
    this->totaLayout->setSpacing(0);
}

void LogWidget::initConnect()
{
    connect(this->leftBtn,SIGNAL(clicked()),this,SLOT(leftPage()));
    connect(this->rightBtn,SIGNAL(clicked()),this,SLOT(rightPage()));
}

void LogWidget::updateTable()
{
    //读取数据写入到表格
    QList<Log *> logList = LogController::getInstance()->doLogData(this->count,this->pageNum);
    for (int i=0;i<logList.size();i++)
    {
        this->tabitem = new QTableWidgetItem(QString::number(logList.at(i)->getLogId()));
        this->tabitem->setTextAlignment(Qt::AlignCenter);
        this->logTable->setItem(i,0,this->tabitem);
        this->tabitem = new QTableWidgetItem(QString::number(logList.at(i)->getUserId()));
        this->tabitem->setTextAlignment(Qt::AlignCenter);
        this->logTable->setItem(i,1,this->tabitem);
        this->tabitem = new QTableWidgetItem(logList.at(i)->getLogContent());
        this->tabitem->setTextAlignment(Qt::AlignCenter);
        this->logTable->setItem(i,2,this->tabitem);
        this->tabitem = new QTableWidgetItem(logList.at(i)->getLogCreateTime());
        this->tabitem->setTextAlignment(Qt::AlignCenter);
        this->logTable->setItem(i,3,this->tabitem);
    }
}

void LogWidget::leftPage()
{
    if(this->pageNum >=13)
    {
        this->pageNum-=13;
    }
    this->updateTable();
}

void LogWidget::rightPage()
{
    int dataNum = LogController::getInstance()->doLogNum();
    if(this->pageNum < dataNum)
    {
        this->pageNum+=13;
    }
    this->logTable->clearContents();
    this->updateTable();
}
