#include "user.h"

User::User(int userId,QString userAccount,QString userName,QString userPwd,bool userStatus,QString userRegTime)
{
    this->userId = userId;
    this->userAccount = userAccount;
    this->userName = userName;
    this->userPwd = userPwd;
    this->userStatus = userStatus;
    this->userRegTime = userRegTime;
}

int User::getUserId() const
{
    return userId;
}

void User::setUserId(int value)
{
    userId = value;
}

QString User::getUserAccount() const
{
    return userAccount;
}

void User::setUserAccount(const QString &value)
{
    userAccount = value;
}

QString User::getUserName() const
{
    return userName;
}

void User::setUserName(const QString &value)
{
    userName = value;
}

QString User::getUserPwd() const
{
    return userPwd;
}

void User::setUserPwd(const QString &value)
{
    userPwd = value;
}

bool User::getUserStatus() const
{
    return userStatus;
}

void User::setUserStatus(bool value)
{
    userStatus = value;
}

QString User::getUserRegTime() const
{
    return userRegTime;
}

void User::setUserRegTime(const QString &value)
{
    userRegTime = value;
}
