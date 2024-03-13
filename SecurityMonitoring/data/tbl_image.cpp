#include "tbl_image.h"

Tbl_image::Tbl_image(int image_id,QString image_name,QString image_path,QString video_create_time)
{
    this->image_id = image_id;
    this->image_name = image_name;
    this->image_path = image_path;
    this->video_create_time = video_create_time;

}

int Tbl_image::getImage_id() const
{
    return image_id;
}

void Tbl_image::setImage_id(int value)
{
    image_id = value;
}

QString Tbl_image::getImage_name() const
{
    return image_name;
}

void Tbl_image::setImage_name(const QString &value)
{
    image_name = value;
}

QString Tbl_image::getImage_path() const
{
    return image_path;
}

void Tbl_image::setImage_path(const QString &value)
{
    image_path = value;
}

QString Tbl_image::getVideo_create_time() const
{
    return video_create_time;
}

void Tbl_image::setVideo_create_time(const QString &value)
{
    video_create_time = value;
}
