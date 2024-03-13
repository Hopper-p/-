#include "setting.h"

Setting::Setting(QString videoPath,QString imagePath,int intervalTime,QString cameraName)
{
    this->videoPath = videoPath;
    this->imagePath = imagePath;
    this->intervalTime = intervalTime;
    this->cameraName = cameraName;
}

QString Setting::getVideoPath() const
{
    return videoPath;
}

void Setting::setVideoPath(const QString &value)
{
    videoPath = value;
}

QString Setting::getImagePath() const
{
    return imagePath;
}

void Setting::setImagePath(const QString &value)
{
    imagePath = value;
}

int Setting::getIntervalTime() const
{
    return intervalTime;
}

void Setting::setIntervalTime(int value)
{
    intervalTime = value;
}

QString Setting::getCameraName() const
{
    return cameraName;
}

void Setting::setCameraName(const QString &value)
{
    cameraName = value;
}
