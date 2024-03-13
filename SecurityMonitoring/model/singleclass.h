#ifndef SINGLECLASS_H
#define SINGLECLASS_H
#include <sqlite3.h>
#include <QString>
class SingleClass
{
public:
    static SingleClass* getInstance();//提供一个公共接口获取唯一实例

    int insertDeleteUpdate(QString sql);

    int getData(QString sql,char**&result,int &row,int &col);
private:
    SingleClass();
    ~SingleClass();
    static SingleClass* instance;
    sqlite3 *dbconnect;

};

#endif // SINGLECLASS_H
