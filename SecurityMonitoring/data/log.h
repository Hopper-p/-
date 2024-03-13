#ifndef LOG_H
#define LOG_H
#include <QString>

class Log
{
public:
    Log(int logId,int userId,QString logContent,QString logCreateTime);
    int getLogId() const;
    void setLogId(int value);

    int getUserId() const;
    void setUserId(int value);

    QString getLogContent() const;
    void setLogContent(const QString &value);

    QString getLogCreateTime() const;
    void setLogCreateTime(const QString &value);

private:
    int logId;
    int userId;
    QString logContent;
    QString logCreateTime;
};

#endif // LOG_H
