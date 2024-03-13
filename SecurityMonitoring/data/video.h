#ifndef VIDEO_H
#define VIDEO_H
#include <QString>

class Video
{
public:
    Video(int videoId,QString videoName,QString videmPath,
          QString videmCoverPath,QString videoCreateTime,int videoFrameNum);
    int getVideoId() const;
    void setVideoId(int value);

    QString getVideoName() const;
    void setVideoName(const QString &value);

    QString getVidemPath() const;
    void setVidemPath(const QString &value);

    QString getVidemCoverPath() const;
    void setVidemCoverPath(const QString &value);

    QString getVideoCreateTime() const;
    void setVideoCreateTime(const QString &value);

    int getVideoFrameNum() const;
    void setVideoFrameNum(int value);

private:
    int videoId;
    QString videoName;
    QString videmPath;
    QString videmCoverPath;
    QString videoCreateTime;
    int videoFrameNum;
};

#endif // VIDEO_H
