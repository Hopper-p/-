#include "logcontroller.h"
#include "model/logmodel.h"
LogController *LogController::instance = nullptr;
LogController *LogController::getInstance()
{
    if(nullptr == LogController::instance)
        LogController::instance = new LogController;
    return LogController::instance;
}

int LogController::doLog(int userId, QString logContent, QString logCreateTime)
{
    return LogModel::getInstance()->insertByLog(userId,logContent,logCreateTime);
}

QList<Log *> LogController::doLogData(int count, int pageNum)
{
    QList<Log *> logList;
    char **qres = nullptr;
    int row = 0,col = 0;
    int res = LogModel::getInstance()->selectByLog(count,pageNum,qres,row,col);
    if(SQLITE_OK == res)
    {
        if(row>0)
        {
            for(int i=1;i<row+1;i++)
            {
                logList.push_back(new Log(atoi(qres[i*col]),atoi(qres[i*col+1]),(qres[i*col+2]),
                        (qres[i*col+3])));
            }
            return logList;
        }
    }
}

int LogController::doLogNum()
{
    int row = 0;
    int res = LogModel::getInstance()->selectByLogNum(row);
    if(SQLITE_OK == res)
    {
        return row;
    }else {
        return 0;
    }
}

LogController::LogController()
{

}
