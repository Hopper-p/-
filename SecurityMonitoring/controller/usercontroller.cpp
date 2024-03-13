#include "usercontroller.h"
#include "model/usermodel.h"
#include <QCryptographicHash>
#include <QDebug>
UserController *UserController::instance = nullptr;
UserController *UserController::getInstance()
{
    if(nullptr == UserController::instance)
        UserController::instance = new UserController;
    return UserController::instance;
}
//登录
int UserController::doLogin(QString id, QString pwd)
{
    int res = -2;
    //将密码加密后传入数据库进行比对
    QString md5Pwd = QCryptographicHash::hash(pwd.toLatin1(),QCryptographicHash::Md5).toHex();
    if(UserModel::getInstance()->selectByUserIdAndPwd(id,md5Pwd) == 0)
    {
        res = UserModel::getInstance()->updateUserStatus(id,1);
    }
    return res;
}
//查找用户昵称
QString UserController::doUserName(QString userId)
{
    char **qres = nullptr;
    int res = UserModel::getInstance()->selectByUserName(userId,qres);
    if(SQLITE_OK == res)
    {
        return qres[1];
    }
}
//写入用户注册的信息
int UserController::doRegistration(QString account,QString name, QString pwd)
{
    //将密码进行MD5加密
    QString md5Pwd = QCryptographicHash::hash(pwd.toLatin1(),QCryptographicHash::Md5).toHex();
    //qDebug()<<"MD5加密后："<<md5Pwd;
    char **qres = nullptr;
    if(UserModel::getInstance()->selectByUserName(name,qres) != SQLITE_OK)
    {//查询不到用户，账号不存在
        int res = UserModel::getInstance()->insertByUser(account,name,md5Pwd);
        if(res == 0)
        {
            qDebug()<<"注册数据写入成功";
            return res;
        }else {
            qDebug()<<"注册数据写入失败";
            return res;
        }
    }else {
        return 2;//用户名相同
    }
}

int UserController::doNotLogin(QString account)
{
    //将当前用户登录状态改为未登录
    int res = UserModel::getInstance()->updateUserStatus(account,0);
    return res;
}

int UserController::doUserIdStatus(QString account)
{
    char **qres = nullptr;
    int res = UserModel::getInstance()->selectByUserStatus(account,qres);
    if(SQLITE_OK == res)
    {
        return atoi(qres[1]);
    }
    return false;
}

int UserController::doUserId(int account)
{
    char **qres = nullptr;
    int res = UserModel::getInstance()->selectByUserId(account,qres);
    if(SQLITE_OK == res)
    {
        return atoi(qres[1]);
    }
    return false;
}

UserController::UserController()
{

}
