#-------------------------------------------------
#
# Project created by QtCreator 2023-07-26T15:54:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SecurityMonitoring
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    model/singleclass.cpp \
    view/bootview.cpp \
    view/bootitem.cpp \
    view/settingwidget.cpp \
    view/mainwidget.cpp \
    controller/settingcontroller.cpp \
    model/settingmodel.cpp \
    data/setting.cpp \
    view/loginwidget.cpp \
    tools/verification.cpp \
    controller/usercontroller.cpp \
    model/usermodel.cpp \
    view/regwidget.cpp \
    thread/decodetopacket.cpp \
    view/monitorwidget.cpp \
    view/playbackwidget.cpp \
    thread/encodethh264.cpp \
    controller/videocontroller.cpp \
    data/video.cpp \
    model/videomodel.cpp \
    data/user.cpp \
    view/imglistwidget.cpp \
    thread/decodevideothread.cpp \
    view/playvideowidget.cpp \
    controller/imagecontroller.cpp \
    model/imagemodel.cpp \
    thread/transcodetonormalthread.cpp \
    view/downwidget.cpp \
    data/tbl_image.cpp \
    view/logwidget.cpp \
    controller/logcontroller.cpp \
    model/logmodel.cpp \
    data/log.cpp

HEADERS += \
    model/singleclass.h \
    view/bootview.h \
    view/bootitem.h \
    view/settingwidget.h \
    view/mainwidget.h \
    controller/settingcontroller.h \
    model/settingmodel.h \
    data/setting.h \
    view/loginwidget.h \
    tools/verification.h \
    controller/usercontroller.h \
    model/usermodel.h \
    view/regwidget.h \
    thread/decodetopacket.h \
    view/monitorwidget.h \
    view/playbackwidget.h \
    thread/encodethh264.h \
    controller/videocontroller.h \
    data/video.h \
    model/videomodel.h \
    data/user.h \
    view/imglistwidget.h \
    thread/decodevideothread.h \
    view/playvideowidget.h \
    controller/imagecontroller.h \
    model/imagemodel.h \
    thread/transcodetonormalthread.h \
    view/downwidget.h \
    data/tbl_image.h \
    view/logwidget.h \
    controller/logcontroller.h \
    model/logmodel.h \
    data/log.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DESTDIR += bin

LIBS += $$PWD/lib/sqlite3.lib

INCLUDEPATH += ./ffmpeglib/include
LIBS += $$PWD/ffmpeglib/lib/avcodec.lib  \
        $$PWD/ffmpeglib/lib/avdevice.lib  \
        $$PWD/ffmpeglib/lib/avfilter.lib  \
        $$PWD/ffmpeglib/lib/avformat.lib  \
        $$PWD/ffmpeglib/lib/avutil.lib  \
        $$PWD/ffmpeglib/lib/swresample.lib  \
        $$PWD/ffmpeglib/lib/swscale.lib

RESOURCES += \
    resources.qrc

DISTFILES += \
    qss/SettingWidget.qss \
    qss/main.qss

QT       += core gui multimedia multimediawidgets

