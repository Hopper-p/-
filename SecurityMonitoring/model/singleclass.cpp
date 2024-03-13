#include "SingleClass.h"
#include <QDebug>

SingleClass *SingleClass::instance = nullptr;
/** 获取单例
 * @brief SingleClass::getInstance
 * @return
 */
SingleClass *SingleClass::getInstance()
{
    if(nullptr == SingleClass::instance)
    {
        SingleClass::instance = new SingleClass;
        qDebug() << "create singleclass";
    }
    else
    {
        qDebug() << "create singleclass again";
    }
    return SingleClass::instance;
}
int SingleClass::insertDeleteUpdate(QString sql)
{
    char *errmsg = nullptr;
    int res = sqlite3_exec(this->dbconnect,sql.toUtf8(),nullptr,nullptr,&errmsg);
    if(SQLITE_OK == res)
    {
        return 0;//执行成功
    }else{
        qDebug()<<"insertDeleteUpdate"<<sqlite3_errmsg(dbconnect)<<"  ";
        qDebug()<<sqlite3_errcode(dbconnect)<<"  ";
        return res;
    }
}
int SingleClass::getData(QString sql, char **&result, int &row, int &col)
{
    char *errmsg = nullptr;
    int res = sqlite3_get_table(this->dbconnect,sql.toUtf8(),&result,&row,&col,&errmsg);
    if(SQLITE_OK == res)
    {
        return 0;//执行成功
    }else{
        qDebug()<<sqlite3_errmsg(dbconnect)<<"  ";
        qDebug()<<sqlite3_errcode(dbconnect)<<"  ";
        return res;
    }
}
SingleClass::SingleClass()
{
    int res = sqlite3_open("./player31.db",&this->dbconnect);
    if(SQLITE_OK == res)
    {
        qDebug()<<"MySingleClass--db  opensuccess--29";
    }else{
        qDebug()<<sqlite3_errmsg(dbconnect);
        qDebug()<<sqlite3_errcode(dbconnect);
    }
}
SingleClass::~SingleClass()
{
   sqlite3_close(this->dbconnect);
}
