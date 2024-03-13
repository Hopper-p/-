/****************************************************************************
** Meta object code from reading C++ file 'playbackwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/playbackwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playbackwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlayBackWidget_t {
    QByteArrayData data[19];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayBackWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayBackWidget_t qt_meta_stringdata_PlayBackWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PlayBackWidget"
QT_MOC_LITERAL(1, 15, 9), // "clearTime"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 9), // "updateImg"
QT_MOC_LITERAL(4, 36, 9), // "videoLast"
QT_MOC_LITERAL(5, 46, 9), // "videoNext"
QT_MOC_LITERAL(6, 56, 8), // "toPlayer"
QT_MOC_LITERAL(7, 65, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 82, 9), // "imageItem"
QT_MOC_LITERAL(9, 92, 7), // "showImg"
QT_MOC_LITERAL(10, 100, 5), // "image"
QT_MOC_LITERAL(11, 106, 5), // "toWin"
QT_MOC_LITERAL(12, 112, 7), // "usbItem"
QT_MOC_LITERAL(13, 120, 9), // "rightPage"
QT_MOC_LITERAL(14, 130, 8), // "leftPage"
QT_MOC_LITERAL(15, 139, 7), // "topPage"
QT_MOC_LITERAL(16, 147, 8), // "DownPage"
QT_MOC_LITERAL(17, 156, 6), // "GoPage"
QT_MOC_LITERAL(18, 163, 9) // "videoList"

    },
    "PlayBackWidget\0clearTime\0\0updateImg\0"
    "videoLast\0videoNext\0toPlayer\0"
    "QListWidgetItem*\0imageItem\0showImg\0"
    "image\0toWin\0usbItem\0rightPage\0leftPage\0"
    "topPage\0DownPage\0GoPage\0videoList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayBackWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    1,   83,    2, 0x0a /* Public */,
       9,    1,   86,    2, 0x0a /* Public */,
      11,    1,   89,    2, 0x0a /* Public */,
      13,    0,   92,    2, 0x0a /* Public */,
      14,    0,   93,    2, 0x0a /* Public */,
      15,    0,   94,    2, 0x0a /* Public */,
      16,    0,   95,    2, 0x0a /* Public */,
      17,    0,   96,    2, 0x0a /* Public */,
      18,    0,   97,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QImage,   10,
    QMetaType::Void, 0x80000000 | 7,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlayBackWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayBackWidget *_t = static_cast<PlayBackWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clearTime(); break;
        case 1: _t->updateImg(); break;
        case 2: _t->videoLast(); break;
        case 3: _t->videoNext(); break;
        case 4: _t->toPlayer((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->showImg((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 6: _t->toWin((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->rightPage(); break;
        case 8: _t->leftPage(); break;
        case 9: _t->topPage(); break;
        case 10: _t->DownPage(); break;
        case 11: _t->GoPage(); break;
        case 12: _t->videoList(); break;
        default: ;
        }
    }
}

const QMetaObject PlayBackWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayBackWidget.data,
      qt_meta_data_PlayBackWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PlayBackWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayBackWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayBackWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlayBackWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
