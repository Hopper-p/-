#include "loginwidget.h"
#include <QFile>
#include <QDebug>
#include <QRegExpValidator>
#include <QMessageBox>
#include "controller/usercontroller.h"
#include "controller/logcontroller.h"
#include <QDateTime>
LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent)
{
    this->handMod = false;
    this->setWindowTitle("登录");
    this->setFixedSize(600,400);
    this->loadQss();    //加载qss
    this->initControl();//加载控件
    this->initConnect();//加载链接
}
void LoginWidget::loadQss()
{
    QFile qss(":/qss/Login.qss");
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
void LoginWidget::initControl()
{
    //正则表达式声明
    QRegExp letExp("[A-Za-z]*");
    QRegExp numExp("[A-Za-z0-9]*");
    QRegExp codeExp("[0-9]*");
    //用户名输入框
    this->nameEdit = new QLineEdit(this);
    this->nameEdit->move(240,70);
    this->nameEdit->setPlaceholderText("账号");
    this->nameEdit->setMaxLength(10);
    this->nameEdit->setValidator(new QRegExpValidator(numExp,this));
    //密码输入框
    this->pwdEdit = new QLineEdit(this);
    this->pwdEdit->move(240,140);
    this->pwdEdit->setPlaceholderText("密码");
    this->pwdEdit->setEchoMode(QLineEdit::Password);
    this->pwdEdit->setMaxLength(10);
    this->pwdEdit->setValidator(new QRegExpValidator(numExp,this));
    //验证码输入框
    this->codeEdit = new QLineEdit(this);
    this->codeEdit->move(240,210);
    this->codeEdit->setPlaceholderText("验证码");
    this->codeEdit->setFixedWidth(90);
    this->codeEdit->setFont(QFont("Arial",10));
    this->codeEdit->setValidator(new QRegExpValidator(numExp,this));
    //验证码按钮
    this->captchaBtn = new Verification(this);
    this->captchaBtn->setStyleSheet("height: 30px; font-size: 14pt;");
    this->captchaBtn->move(335,213);
    //qDebug()<<"验证码："<<this->captchaBtn->m_captcha;

    //Label控件
    this->nameLab = new QLabel("账  号：",this);
    this->nameLab->move(150,80);
    this->pwdLab = new QLabel("密  码：",this);
    this->pwdLab->move(150,150);
    this->codeLab = new QLabel("验证码：",this);
    this->codeLab->move(150,220);
    //按钮控件
    this->logBtn = new QPushButton("登录",this);
    this->logBtn->move(120,300);
    this->regBtn = new QPushButton("注册",this);
    this->regBtn->move(380,300);
    this->eyesBtn = new QPushButton(this);
    this->eyesBtn->move(380,140);
    this->eyesBtn->setIcon(QIcon(":/image/icon/closesEyes.png"));
    this->eyesBtn->setStyleSheet("width:35px;height:35px;background-color:#fefcf0");
    //初始化注册窗口
    this->regWin = new RegWidget;
}

void LoginWidget::initConnect()
{
    //登录按钮业务逻辑
    connect(this->logBtn, SIGNAL(clicked()),this,SLOT(doLogin()));
    //明密文显示切换
    connect(this->eyesBtn,SIGNAL(clicked()),this,SLOT(handText()));
    //跳转注册窗口
    connect(this->regBtn, SIGNAL(clicked()),this,SLOT(toReg()));
    //注册界面回到登录界面
    connect(this->regWin,SIGNAL(backToLogin()),this,SLOT(showSelf()));
    //注册界面回到登录界面（带账号信息）
    connect(this->regWin,SIGNAL(backToLogin(QString)),this,SLOT(showSelf(QString)));
}
void LoginWidget::doLogin()
{
    //获取表单信息  用户名  密码  验证码
    //QString codestr = this->codeEdit->text();
    bool Logif = true;
    //刷新验证码
    this->captchaBtn->TimeoutSlot();
    if(this->nameEdit->text() == "" || this->pwdEdit->text() == "")
    {
        QMessageBox::warning(this,"提示","用户名/密码不能为空");
        return;
    }else if(this->nameEdit->text().length()<6 ||this->pwdEdit->text().length()<6){
        QMessageBox::warning(this,"提示","用户名/密码最小长度6位");
        return;
    }
    //检测验证码是否填写正确
    if(this->codeEdit->text().compare(this->captchaBtn->m_captcha,Qt::CaseInsensitive) == 0)
    {
        //格式检验完毕，准备校验账号密码
        int res = UserController::getInstance()->doLogin(this->nameEdit->text(),this->pwdEdit->text());
        if(res == 0)
        {
            QMessageBox::warning(this,"提示","登录成功，即将返回主页");
            //将登录写入日志
            QDateTime time = QDateTime::currentDateTime();
            QString timer = time.toString("yyyyMMddhhmmss");
            int userId = UserController::getInstance()->doUserId(this->nameEdit->text().toInt());
            res = LogController::getInstance()->doLog(userId,"登录",timer);
            emit backToMain(this->nameEdit->text());
        }else {
            QMessageBox::warning(this,"提示","账号或密码不正确");
        }
    }else {
        QMessageBox::warning(this,"提示","验证码错误，请重新输入");
        this->captchaBtn->genCaptcha();
    }
}

void LoginWidget::handText()
{
    this->handMod = !this->handMod;
    if(this->handMod)
    {
        this->pwdEdit->setEchoMode(QLineEdit::Normal);
        this->eyesBtn->setIcon(QIcon(":/image/icon/openEyes.png"));
    }else{
        this->pwdEdit->setEchoMode(QLineEdit::Password);
        this->eyesBtn->setIcon(QIcon(":/image/icon/closesEyes.png"));
    }
}
void LoginWidget::toReg()
{
    this->hide();//隐藏当前窗口
    this->regWin->show();//显示注册窗口
}
void LoginWidget::showSelf()
{
    this->regWin->close();//注册关闭
    this->show();//本体显示
}

void LoginWidget::showSelf(QString name)
{
    this->regWin->close();//注册关闭
    this->nameEdit->setText(name);
    this->show();//本体显示
}
