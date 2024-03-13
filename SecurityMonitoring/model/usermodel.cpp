#include "usermodel.h"
#include <QDateTime>
UserModel *UserModel::instance = nullptr;
UserModel *UserModel::getInstance()
{
    if(nullptr == UserModel::instance)
        UserModel::instance = new UserModel;
    return UserModel::instance;
}

int UserModel::selectByUserIdAndPwd(QString Id,QString pwd)
{
    QString selectSql = QString("SELECT * FROM tbl_user WHERE user_account='%1' AND user_pwd='%2';")
            .arg(Id).arg(pwd);
    char **qres = nullptr;
    int row = 0,col = 0;
    char *errmsg = nullptr;
    //创建出数据库单例
    SingleClass *dbinstance = SingleClass::getInstance();
    int res = dbinstance->getData(selectSql.toUtf8(),qres,row,col);
    if(SQLITE_OK == res)
    {
        if(row>0)   //用户密码存在
        {
            return 0;   //登录成功

        }else {
            return 1;   //登录失败
        }
    }else {
        return -1;      //执行失败
    }
}

int UserModel::updateUserStatus(QString Id, int status)
{
    QString upSql = QString("UPDATE tbl_user SET user_status=%1 WHERE user_account='%2';")
            .arg(status).arg(Id);
    SingleClass *dbinstance = SingleClass::getInstance();
    int res = dbinstance->insertDeleteUpdate(upSql);
    if(SQLITE_OK == res)
    {
        return 0;      //执行成功
    }else {
        return -1;     //执行失败
    }
}

int UserModel::selectByUserName(QString userId,char **&qres)
{
    QString selectSql = QString("SELECT user_name FROM tbl_user WHERE user_account='%1';")
            .arg(userId);
    SingleClass *dbinstance = SingleClass::getInstance();
    int row = 0,col = 0;
    int res = dbinstance->getData(selectSql.toUtf8(),qres,row,col);
    if(SQLITE_OK == res)
    {
        if(row>0)   //查询到内容
        {
            return 0;   //查询成功
        }else {
            return 1;   //查询失败
        }
    }else {
        return -1;      //执行失败
    }
}

int UserModel::insertByUser(QString account,QString name, QString pwd)
{

    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
    QString str = dateTime .toString("yyyy-MM-dd hh:mm:ss");//格式化时间
    QString insertSql = QString("INSERT INTO tbl_user (user_account,user_name,user_pwd,user_reg_time) VALUES ('%1','%2','%3','%4');")
            .arg(account).arg(name).arg(pwd).arg(str);
    SingleClass *dbinstance = SingleClass::getInstance();
    int res = dbinstance->insertDeleteUpdate(insertSql);
    if(SQLITE_OK == res)
    {
        return 0;      //执行成功
    }else {
        return -1;     //执行失败
    }
}

int UserModel::selectByUserStatus(QString userId, char **&qres)
{
    QString selectSql = QString("SELECT user_status FROM tbl_user WHERE user_account = '%1';")
            .arg(userId);
    SingleClass *dbinstance = SingleClass::getInstance();
    int row = 0,col = 0;
    int res = dbinstance->getData(selectSql.toUtf8(),qres,row,col);
    if(SQLITE_OK == res)
    {
        if(row>0)   //查询到内容
        {
            return 0;   //查询成功
        }else {
            return 1;   //查询失败
        }
    }else {
        return -1;      //执行失败
    }
}

int UserModel::selectByUserId(int userId, char **&qres)
{
    QString selectSql = QString("SELECT user_id FROM tbl_user WHERE user_account=%1;").arg(userId);
    SingleClass *dbinstance = SingleClass::getInstance();
    int row = 0,col = 0;
    int res = dbinstance->getData(selectSql.toUtf8(),qres,row,col);
    if(SQLITE_OK == res)
    {
        if(row>0)   //查询到内容
        {
            return 0;   //查询成功
        }else {
            return 1;   //查询失败
        }
    }else {
        return -1;      //执行失败
    }
}

UserModel::UserModel()
{

}
