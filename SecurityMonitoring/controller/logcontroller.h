#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H
#include <QString>
#include "data/log.h"
#include <QList>
class LogController
{
public:
    static LogController* getInstance();
    //写入日志信息
    int doLog(int userId,QString logContent,QString logCreateTime);
    //读取日志信息
    QList<Log*> doLogData(int count,int pageNum);
    //读取日志表条数
    int doLogNum();
private:
    LogController();
    static LogController* instance;
};

#endif // LOGCONTROLLER_H
