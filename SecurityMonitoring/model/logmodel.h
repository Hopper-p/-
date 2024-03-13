#ifndef LOGMODEL_H
#define LOGMODEL_H
#include <QString>
#include "singleclass.h"
class LogModel
{
public:
    static LogModel* getInstance();

    int insertByLog(int userId,QString logContent,QString logCreateTime);

    int selectByLog(int count, int pageNum,char **&qres,int &row,int &col);

    int selectByLogNum(int &row);
private:
    LogModel();
    static LogModel* instance;
};

#endif // LOGMODEL_H
