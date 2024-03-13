#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H
#include <QString>
#include "data/video.h"
class VideoController
{
public:
    static VideoController* getInstance();
    //写入视频信息
    int doVideo(QString videoName,QString videoPath,QString videoCoverPath,QString createTime,int frameNum);
    //获取分页后的封面路径和视频名称
    QList<Video*> doVideoName(int count,int pageNum);
    //查询当前存储的视频条数
    int doVideoNum();
    //查询最新的视频存储路径
    QString doVideoPath();
    //根据视频名称查找视频路径
    QString doVideoNameAndPath(QString videoName);
    //根据日期筛选视频列表
    QList<Video*> doVideoTime(QString videoTime);
    //根据日期筛选视频列表分页显示
    QList<Video*> doVideoTime(QString videoTime,int count,int pageNum);
private:
    VideoController();
    static VideoController* instance;
};

#endif // VIDEOCONTROLLER_H
