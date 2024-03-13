#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User(int userId,QString userAccount,QString userName,QString userPwd,bool userStatus,QString userRegTime);

    int getUserId() const;
    void setUserId(int value);

    QString getUserAccount() const;
    void setUserAccount(const QString &value);

    QString getUserName() const;
    void setUserName(const QString &value);

    QString getUserPwd() const;
    void setUserPwd(const QString &value);

    bool getUserStatus() const;
    void setUserStatus(bool value);

    QString getUserRegTime() const;
    void setUserRegTime(const QString &value);

private:
    int userId;
    QString userAccount;
    QString userName;
    QString userPwd;
    bool userStatus;
    QString userRegTime;
};

#endif // USER_H
