#include "regwidget.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include "controller/usercontroller.h"
RegWidget::RegWidget(QWidget *parent) : QWidget(parent)
{
    this->handMod = false;
    this->handMod1 = false;
    //设置标题
    this->setWindowTitle("注册界面");
    //控制大小
    this->setFixedSize(600,400);
    this->loadQss();    //加载qss
    this->initControl();//加载控件
    this->initConnect();//加载链接
}

void RegWidget::loadQss()
{
    QFile qss(":/qss/Login.qss");
    if( qss.open(QFile::ReadOnly))
    {
        qDebug()<<endl<<"RegWidget::loadQss open success";
        QString style = QLatin1String(qss.readAll());
        this->setStyleSheet(style);
        qss.close();
    }else{
        qDebug()<<endl<<"RegWidget::loadQss Open failed";
    }
}

void RegWidget::initControl()
{
    //正则限制
    QRegExpValidator *valid1 = new QRegExpValidator(QRegExp("^[a-zA-Z0-9\u4e00-\u9fa5]{6,10}$"), this);
    QRegExpValidator *valid2 = new QRegExpValidator(QRegExp("^[a-zA-Z0-9]{6,10}$"), this);
    //加载QLabel控件
    this->accountLab = new QLabel("账    号：",this);
    this->accountLab->move(150,40);
    this->nickNameLab = new QLabel("昵    称：",this);
    this->nickNameLab->move(150,100);
    this->pwdLab = new QLabel("密    码：",this);
    this->pwdLab->move(150,160);
    this->conPwdLab = new QLabel("确认密码：",this);
    this->conPwdLab->move(150,220);
    //加载QEdit控件
    this->accountEdit = new QLineEdit(this);
    this->accountEdit->move(250,30);
    this->accountEdit->setPlaceholderText("账号");
    this->accountEdit->setValidator(valid2);

    this->nickNameEdit = new QLineEdit(this);
    this->nickNameEdit->move(250,90);
    this->nickNameEdit->setPlaceholderText("昵称");
    this->nickNameEdit->setValidator(valid1);

    this->pwdEdit = new QLineEdit(this);
    this->pwdEdit->move(250,150);
    this->pwdEdit->setPlaceholderText("密码");
    this->pwdEdit->setEchoMode(QLineEdit::Password);
    this->pwdEdit->setValidator(valid2);

    this->conPwdEdit = new QLineEdit(this);
    this->conPwdEdit->move(250,210);
    this->conPwdEdit->setPlaceholderText("确认密码");
    this->conPwdEdit->setEchoMode(QLineEdit::Password);
    this->pwdEdit->setValidator(valid2);

    //加载QPushButton控件
    this->logBtn = new QPushButton("注册",this);
    this->logBtn->move(140,300);
    this->exitBtn = new QPushButton("取消",this);
    this->exitBtn->move(340,300);
    this->eyesPwdBtn = new QPushButton(this);
    this->eyesPwdBtn->move(395,150);
    this->eyesPwdBtn->setIcon(QIcon(":/image/icon/closesEyes.png"));
    this->eyesPwdBtn->setStyleSheet("width:35px;height:35px;background-color:#fefcf0");
    this->eyesConPwdBtn = new QPushButton(this);
    this->eyesConPwdBtn->move(395,210);
    this->eyesConPwdBtn->setIcon(QIcon(":/image/icon/closesEyes.png"));
    this->eyesConPwdBtn->setStyleSheet("width:35px;height:35px;background-color:#fefcf0");
}

void RegWidget::initConnect()
{
    //注册业务
    connect(this->logBtn,SIGNAL(clicked()),this,SLOT(doReg()));
    //明密文显示切换
    connect(this->eyesPwdBtn,SIGNAL(clicked()),this,SLOT(handPwdText()));
    connect(this->eyesConPwdBtn,SIGNAL(clicked()),this,SLOT(handConPwdText()));
    //点击取消返回登录页面
    connect(this->exitBtn, SIGNAL(clicked()),this,SIGNAL(backToLogin()));
}
void RegWidget::doReg()
{
    if(this->accountEdit->text() == "" || this->pwdEdit->text() == "" || this->conPwdEdit->text() == "")
    {
        QMessageBox::warning(this,"提示","账号/密码/确认密码不能为空");
        return;
    }else if(this->pwdEdit->text().length() < 6 || this->accountEdit->text().length() < 6){
        QMessageBox::warning(this,"提示","用户名/密码最小长度6位");
        return;
    }else if(this->conPwdEdit->text() != this->pwdEdit->text()){
        QMessageBox::warning(this,"提示","两次输入密码不一致");
        return;
    }else{
        int res = UserController::getInstance()->doRegistration(this->accountEdit->text(),
                  this->nickNameEdit->text(),this->pwdEdit->text());
        if(res == 0)
        {
            QMessageBox::about(this,"成功","注册成功");
            this->accountEdit->setText("");
            this->nickNameEdit->setText("");
            this->pwdEdit->setText("");
            this->conPwdEdit->setText("");
            //手动触发backToLogin自定义信号
            emit backToLogin(this->accountEdit->text());
        }else if(res == 2){
            QMessageBox::warning(this,"提示","该账户已被占用，请重试");
        }
    }
}

void RegWidget::handPwdText()
{
    this->handMod = !this->handMod;
    if(this->handMod)
    {
        this->pwdEdit->setEchoMode(QLineEdit::Normal);
        this->eyesPwdBtn->setIcon(QIcon(":/image/icon/openEyes.png"));
    }else{
        this->pwdEdit->setEchoMode(QLineEdit::Password);
        this->eyesPwdBtn->setIcon(QIcon(":/image/icon/closesEyes.png"));
    }
}

void RegWidget::handConPwdText()
{
    this->handMod1 = !this->handMod1;
    if(this->handMod1)
    {
        this->conPwdEdit->setEchoMode(QLineEdit::Normal);
        this->eyesConPwdBtn->setIcon(QIcon(":/image/icon/openEyes.png"));
    }else{
        this->conPwdEdit->setEchoMode(QLineEdit::Password);
        this->eyesConPwdBtn->setIcon(QIcon(":/image/icon/closesEyes.png"));
    }
}
