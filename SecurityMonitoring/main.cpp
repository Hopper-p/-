#include <QApplication>
#include <QDebug>
#include "view/bootview.h"
#include "sqlite3.h"
#include "view/playvideowidget.h"
extern "C"
{
   #include"libavcodec/avcodec.h"
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //qDebug() << "SQLite3版本：" << sqlite3_libversion();
    //qDebug()<<avcodec_version();

    BootView w;
    w.show();
    //PlayVideoWidget w;
    //w.show();

    return a.exec();
}
