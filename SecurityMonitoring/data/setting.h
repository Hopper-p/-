#ifndef SETTING_H
#define SETTING_H
#include <QString>

class Setting
{
public:
    Setting(QString videoPath,QString imagePath,int intervalTime,QString cameraName);

    QString getVideoPath() const;
    void setVideoPath(const QString &value);

    QString getImagePath() const;
    void setImagePath(const QString &value);

    int getIntervalTime() const;
    void setIntervalTime(int value);

    QString getCameraName() const;
    void setCameraName(const QString &value);

private:
    QString videoPath;
    QString imagePath;
    int intervalTime;
    QString cameraName;
};

#endif // SETTING_H
