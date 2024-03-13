#include "videomodel.h"
#include "QDebug"
VideoModel *VideoModel::instance = nullptr;
VideoModel *VideoModel::getInstance()
{
    if(nullptr == VideoModel::instance)
        VideoModel::instance;
    return VideoModel::instance;
}

int VideoModel::insertByVideo(QString videoName, QString videoPath, QString videoCoverPath, QString createTime, int frameNum)
{
    QString insertSql = QString("INSERT INTO tbl_video (video_id,video_name,video_path,video_cover_path,video_create_time,video_frame_num)VALUES (NULL,'%1','%2','%3','%4',%5);")
                                .arg(videoName).arg(videoPath).arg(videoCoverPath).arg(createTime).arg(frameNum);
    SingleClass *dbinstance = SingleClass::getInstance();
    int res = dbinstance->insertDeleteUpdate(insertSql);
    qDebug()<<"insertByVideo res="<<res;
    //qDebug() << sqlite3_errcode(db);
    if(SQLITE_OK == res)
    {
        return 0;      //执行成功
    }else {
        return -1;     //执行失败
    }
}

int VideoModel::selectByVideoName(int count, int pageNum, char **&qres, int &row, int &col)
{
    QString selectSql = QString("SELECT * FROM tbl_video ORDER BY video_create_time DESC LIMIT %1 OFFSET %2;")
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

int VideoModel::selectByBideoCol(int &row)
{
    char **qres = nullptr;
    int col = 0;
    QString selectSql = QString("SELECT * FROM tbl_video;");
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

int VideoModel::selectByVideoPath(QString videoName,char **&qres)
{
    int row=0,col=0;
    QString selectSql = QString("SELECT video_path FROM tbl_video WHERE video_name='%1';").arg(videoName);
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

int VideoModel::selectByVideoTime(QString videoTime, char **&qres,int &row,int &col)
{
    QString selectSql = QString("SELECT *FROM tbl_video WHERE video_create_time LIKE'%1%';")
            .arg(videoTime);
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

int VideoModel::selectByVideoTime(QString videoTime, int count, int pageNum, char **&qres, int &row, int &col)
{
    QString selectSql = QString("SELECT *FROM tbl_video WHERE video_create_time LIKE'%1%' ORDER BY video_create_time DESC LIMIT %2 OFFSET %3;")
            .arg(videoTime).arg(count).arg(pageNum);
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

VideoModel::VideoModel()
{

}
