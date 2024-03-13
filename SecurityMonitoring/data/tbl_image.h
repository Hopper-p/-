#ifndef TBL_IMAGE_H
#define TBL_IMAGE_H

#include <QString>



class Tbl_image
{
public:
    Tbl_image(int image_id,QString image_name,QString image_path,QString video_create_time);
    int getImage_id() const;
    void setImage_id(int value);

    QString getImage_name() const;
    void setImage_name(const QString &value);

    QString getImage_path() const;
    void setImage_path(const QString &value);

    QString getVideo_create_time() const;
    void setVideo_create_time(const QString &value);

private:
    int image_id;
    QString image_name;
    QString image_path;
    QString video_create_time;
};

#endif // TBL_IMAGE_H
