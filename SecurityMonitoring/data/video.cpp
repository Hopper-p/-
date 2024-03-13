#include "video.h"

Video::Video(int videoId,QString videoName,QString videmPath,
             QString videmCoverPath,QString videoCreateTime,int videoFrameNum)
{
    this->videoId = videoId;
    this->videoName = videoName;
    this->videmPath = videmPath;
    this->videmCoverPath = videmCoverPath;
    this->videoCreateTime = videoCreateTime;
    this->videoCreateTime = videoCreateTime;
}

int Video::getVideoId() const
{
    return videoId;
}

void Video::setVideoId(int value)
{
    videoId = value;
}

QString Video::getVideoName() const
{
    return videoName;
}

void Video::setVideoName(const QString &value)
{
    videoName = value;
}

QString Video::getVidemPath() const
{
    return videmPath;
}

void Video::setVidemPath(const QString &value)
{
    videmPath = value;
}

QString Video::getVidemCoverPath() const
{
    return videmCoverPath;
}

void Video::setVidemCoverPath(const QString &value)
{
    videmCoverPath = value;
}

QString Video::getVideoCreateTime() const
{
    return videoCreateTime;
}

void Video::setVideoCreateTime(const QString &value)
{
    videoCreateTime = value;
}

int Video::getVideoFrameNum() const
{
    return videoFrameNum;
}

void Video::setVideoFrameNum(int value)
{
    videoFrameNum = value;
}
