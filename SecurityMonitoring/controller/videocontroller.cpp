#include "videocontroller.h"
#include "model/videomodel.h"
#include <QDebug>
#include <QIcon>
VideoController *VideoController::instance = nullptr;

VideoController *VideoController::getInstance()
{
    if(nullptr == VideoController::instance)
        VideoController::instance = new VideoController;
    return VideoController::instance;
}

int VideoController::doVideo(QString videoName, QString videoPath, QString videoCoverPath, QString createTime, int frameNum)
{
    int res = VideoModel::getInstance()->insertByVideo(videoName,videoPath,videoCoverPath,createTime,frameNum);
    if(res == 0)
    {
        qDebug()<<"视频数据写入成功";
        return res;
    }else {
        qDebug()<<"视频数据写入失败";
        return res;
    }
}

QList<Video*> VideoController::doVideoName(int count,int pageNum)
{
    QList<Video*> videoList;
    char **qres = nullptr;
    int row = 0,col = 0;
    int res = VideoModel::getInstance()->selectByVideoName(count,pageNum,qres,row,col);
    if(SQLITE_OK == res)
    {
        if(row>0)
        {
            for(int i=1;i<row+1;i++)
            {
                videoList.push_back(new Video(atoi(qres[i*col]),(qres[i*col+1]),(qres[i*col+2]),
                        (qres[i*col+3]),(qres[i*col+4]),atoi(qres[i*col+5])));
            }
            return videoList;
        }
    }
}

int VideoController::doVideoNum()
{
    int row = 0;
    int res = VideoModel::getInstance()->selectByBideoCol(row);
    //qDebug()<<"VideoController::doVideoNum col:"<<row;
    if(SQLITE_OK == res)
    {
        return row;
    }else {
        return 0;
    }
}

QString VideoController::doVideoPath()
{
    char **qres = nullptr;
    int row = 0,col = 0;
    int res = VideoModel::getInstance()->selectByVideoName(1,0,qres,row,col);
    qDebug()<<"doVideoPath"<<res;
    if(SQLITE_OK == res)
    {
        return qres[col+2];
    }
    return "";
}

QString VideoController::doVideoNameAndPath(QString videoName)
{
    char **qres = nullptr;
    int res = VideoModel::getInstance()->selectByVideoPath(videoName,qres);
    qDebug()<<"doVideoNameAndPath:"<<qres[1];
    if(SQLITE_OK == res)
    {
        return qres[1];
    }
}
//根据日期筛选视频列表
QList<Video *> VideoController::doVideoTime(QString videoTime)
{
    QList<Video*> videoList;
    char **qres = nullptr;
    int row = 0,col = 0;
    int res = VideoModel::getInstance()->selectByVideoTime(videoTime,qres,row,col);
    if(SQLITE_OK == res)
    {
        if(row>0)
        {
            for(int i=1;i<row+1;i++)
            {
                videoList.push_back(new Video(atoi(qres[i*col]),(qres[i*col+1]),(qres[i*col+2]),
                        (qres[i*col+3]),(qres[i*col+4]),atoi(qres[i*col+5])));
            }
            return videoList;
        }
    }
}

QList<Video *> VideoController::doVideoTime(QString videoTime, int count, int pageNum)
{
    QList<Video*> videoList;
    char **qres = nullptr;
    int row = 0,col = 0;
    int res = VideoModel::getInstance()->selectByVideoTime(videoTime,count,pageNum,qres,row,col);
    if(SQLITE_OK == res)
    {
        if(row>0)
        {
            for(int i=1;i<row+1;i++)
            {
                videoList.push_back(new Video(atoi(qres[i*col]),(qres[i*col+1]),(qres[i*col+2]),
                        (qres[i*col+3]),(qres[i*col+4]),atoi(qres[i*col+5])));
            }
            return videoList;
        }
    }
}

VideoController::VideoController()
{

}
