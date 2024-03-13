#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H
#include <QString>
#include "singleclass.h"

class ImageModel
{
public:
    static ImageModel* getInstance();

    int insertByImage(QString name,QString path,QString time);

    int selectByImageData(int count,int pageNum,char **&qres,int &row,int &col);

    int selectByBideoCol(int &row);
private:
    ImageModel();
    static ImageModel* instance;
};

#endif // IMAGEMODEL_H
