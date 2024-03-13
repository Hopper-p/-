#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H
#include <QString>
#include "data/tbl_image.h"
#include <QList>
class ImageController
{
public:
    static ImageController* getInstance();
    //写入截图信息
    int doImage(QString name,QString path,QString time);
    //查询9条图片信息
    QList<Tbl_image*> doImageData(int count,int pageNum);
    //查询数据库内的图片数量
    int doImageNum();
private:
    ImageController();
    static ImageController* instance;
};

#endif // IMAGECONTROLLER_H
