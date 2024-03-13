#include "logmodel.h"
LogModel *LogModel::instance = nullptr;
LogModel *LogModel::getInstance()
{
    if(nullptr == LogModel::instance)
        LogModel::instance;
    return LogModel::instance;
}

int LogModel::insertByLog(int userId, QString logContent, QString logCreateTime)
{
    QString insertQsq = QString("INSERT INTO tbl_log (user_id,log_content,log_create_time)VALUES(%1,'%2','%3');")
            .arg(userId).arg(logContent).arg(logCreateTime);
    SingleClass *dbinstance = SingleClass::getInstance();
    int res = dbinstance->insertDeleteUpdate(insertQsq);
    if(SQLITE_OK == res)
    {
        return 0;      //执行成功
    }else {
        return -1;     //执行失败
    }
}

int LogModel::selectByLog(int count, int pageNum, char **&qres, int &row, int &col)
{
    QString selectSql = QString("SELECT * FROM tbl_log DESC LIMIT %1 OFFSET %2;")
            .arg(count).arg(pageNum);
    SingleClass *dbinstance = SingleClass::getInstance();
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

int LogModel::selectByLogNum(int &row)
{
    char **qres = nullptr;
    int col = 0;
    QString selectSql = QString("SELECT * FROM tbl_log;");
    SingleClass *dbinstance = SingleClass::getInstance();
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

LogModel::LogModel()
{

}
