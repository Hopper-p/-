#include "log.h"

Log::Log(int logId,int userId,QString logContent,QString logCreateTime)
{
    this->logId = logId;
    this->userId = userId;
    this->logContent = logContent;
    this->logCreateTime = logCreateTime;
}

int Log::getLogId() const
{
    return logId;
}

void Log::setLogId(int value)
{
    logId = value;
}

int Log::getUserId() const
{
    return userId;
}

void Log::setUserId(int value)
{
    userId = value;
}

QString Log::getLogContent() const
{
    return logContent;
}

void Log::setLogContent(const QString &value)
{
    logContent = value;
}

QString Log::getLogCreateTime() const
{
    return logCreateTime;
}

void Log::setLogCreateTime(const QString &value)
{
    logCreateTime = value;
}
