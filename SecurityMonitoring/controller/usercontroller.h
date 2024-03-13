#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H
#include <QString>

class UserController
{
public:
    static UserController* getInstance();
    //登录
    int doLogin(QString id,QString pwd);
    //查找用户昵称
    QString doUserName(QString userId);
    //写入用户注册的信息
    int doRegistration(QString account,QString name,QString pwd);
    //将当前用户登录状态改为未登录
    int doNotLogin(QString account);
    //根据用户账户查询该用户是否登录
    int doUserIdStatus(QString account);
    //查询用户原始ID
    int doUserId(int account);
private:
    UserController();
    static UserController* instance;
};

#endif // USERCONTROLLER_H
