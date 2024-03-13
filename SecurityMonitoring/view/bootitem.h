#ifndef BOOTITEM_H
#define BOOTITEM_H
#include <QGraphicsItem>
#include <QObject>
#include <QString>
#include <QPixmap>
#include <QWidget>
#include <QPainter>

class BootItem:public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    BootItem(int status,QString path);

    QRectF boundingRect() const;

    void paint(QPainter *paiter, const QStyleOptionGraphicsItem *option,QWidget *widget = Q_NULLPTR);

    void advance(int phase);
private:
    int status;     //状态
    QPixmap img;    //图片
signals:
    void stopMove();
};

#endif // BOOTITEM_H
