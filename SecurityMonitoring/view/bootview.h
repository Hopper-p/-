#ifndef BOOTVIEW_H
#define BOOTVIEW_H
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "bootitem.h"
#include "view/mainwidget.h"
#include "view/settingwidget.h"
class BootView:public QGraphicsView
{
    Q_OBJECT
public:
    BootView();
private:
    QGraphicsScene *mySence;    //场景
    BootItem *item1,*item2,*item3,*item4;       //图元
    QTimer *timer;              //定时器
    int state;
    SettingWidget *setWin;
public slots:
    void stopMove();
    void showMainWidget();
    void showMain();
};

#endif // BOOTVIEW_H
