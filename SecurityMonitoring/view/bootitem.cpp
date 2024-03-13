#include "bootitem.h"
#include <QDebug>
BootItem::BootItem(int status, QString path)
{
    this->status = status;
    this->img.load(path);
}

QRectF BootItem::boundingRect() const
{
    return QRectF(-this->img.width()/2,-this->img.height()/2,img.width(),img.height());
}

void BootItem::paint(QPainter *paiter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    paiter->drawPixmap(-this->img.width()/2,-this->img.height()/2,img.width(),img.height(),this->img);
}

void BootItem::advance(int phase)
{
    if(this->status == 1)
    {
        //图元的碰撞
        if(collidingItems().count()>0)
        {
            //qDebug()<<"boom";
            //this->status = 0;
            emit stopMove();
            return;
        }
        this->setPos(mapToScene(2,0));
    }
    if(this->status == 2)
    {
        this->moveBy(-2, 0);
    }
}
