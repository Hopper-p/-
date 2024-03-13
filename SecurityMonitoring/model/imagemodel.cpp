#include "imagemodel.h"
ImageModel *ImageModel::instance = nullptr;
ImageModel *ImageModel::getInstance()
{
    if(nullptr == ImageModel::instance)
        ImageModel::instance;
    return ImageModel::instance;
}

int ImageModel::insertByImage(QString name, QString path, QString time)
{
    QString insertQsq = QString("INSERT INTO tbl_image (image_name,image_path,video_create_time)VALUES('%1','%2','%3');")
            .arg(name).arg(path).arg(time);
    SingleClass *dbinstance = SingleClass::getInstance();
    int res = dbinstance->insertDeleteUpdate(insertQsq);
    if(SQLITE_OK == res)
    {
        return 0;      //执行成功
    }else {
        return -1;     //执行失败
    }
}

int ImageModel::selectByImageData(int count, int pageNum, char **&qres, int &row, int &col)
{
    QString selectSql = QString("SELECT *FROM tbl_image ORDER BY video_create_time DESC LIMIT %1 OFFSET %2;")
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
    }else{
        return -1;      //执行失败
    }
}

int ImageModel::selectByBideoCol(int &row)
{
    char **qres = nullptr;
    int col = 0;
    QString selectSql = QString("SELECT * FROM tbl_image;");
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

ImageModel::ImageModel()
{

}
