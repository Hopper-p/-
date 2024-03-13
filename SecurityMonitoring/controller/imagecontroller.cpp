#include "imagecontroller.h"
#include <QDebug>
#include "model/imagemodel.h"
ImageController *ImageController::instance = nullptr;
ImageController *ImageController::getInstance()
{
    if(nullptr == ImageController::instance)
        ImageController::instance = new ImageController;
    return ImageController::instance;
}

int ImageController::doImage(QString name, QString path, QString time)
{
    int res = ImageModel::getInstance()->insertByImage(name,path,time);
    return res;
}

QList<Tbl_image *> ImageController::doImageData(int count, int pageNum)
{
    QList<Tbl_image *> imgList;
    char **qres = nullptr;
    int row = 0,col = 0;
    pageNum *=9;
    int res = ImageModel::getInstance()->selectByImageData(count,pageNum,qres,row,col);
    if(SQLITE_OK == res)
    {
        if(row>0)
        {
            for(int i=1;i<row+1;i++)
            {
                imgList.push_back(new Tbl_image(atoi(qres[i*col]),qres[i*col+1]
                                        ,qres[i*col+2],qres[i*col+3]));
            }
            return imgList;
        }
    }
}

int ImageController::doImageNum()
{
    int row = 0;
    int res = ImageModel::getInstance()->selectByBideoCol(row);
    qDebug()<<"VideoController::doVideoNum col:"<<row;
    if(SQLITE_OK == res)
    {
        return row;
    }else {
        return 0;
    }
}

ImageController::ImageController()
{

}
