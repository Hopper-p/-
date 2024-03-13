/****************************************************************************
** Meta object code from reading C++ file 'playvideowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/playvideowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playvideowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlayVideoWidget_t {
    QByteArrayData data[13];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayVideoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayVideoWidget_t qt_meta_stringdata_PlayVideoWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PlayVideoWidget"
QT_MOC_LITERAL(1, 16, 9), // "videoLast"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 9), // "videoNext"
QT_MOC_LITERAL(4, 37, 9), // "updateImg"
QT_MOC_LITERAL(5, 47, 8), // "showDown"
QT_MOC_LITERAL(6, 56, 7), // "showImg"
QT_MOC_LITERAL(7, 64, 5), // "image"
QT_MOC_LITERAL(8, 70, 12), // "playHandover"
QT_MOC_LITERAL(9, 83, 7), // "Changes"
QT_MOC_LITERAL(10, 91, 8), // "mulriple"
QT_MOC_LITERAL(11, 100, 10), // "toDownload"
QT_MOC_LITERAL(12, 111, 7) // "picture"

    },
    "PlayVideoWidget\0videoLast\0\0videoNext\0"
    "updateImg\0showDown\0showImg\0image\0"
    "playHandover\0Changes\0mulriple\0toDownload\0"
    "picture"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayVideoWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    0,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   62,    2, 0x0a /* Public */,
       6,    1,   63,    2, 0x0a /* Public */,
       8,    0,   66,    2, 0x0a /* Public */,
       9,    1,   67,    2, 0x0a /* Public */,
      11,    0,   70,    2, 0x0a /* Public */,
      12,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlayVideoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayVideoWidget *_t = static_cast<PlayVideoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->videoLast(); break;
        case 1: _t->videoNext(); break;
        case 2: _t->updateImg(); break;
        case 3: _t->showDown(); break;
        case 4: _t->showImg((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 5: _t->playHandover(); break;
        case 6: _t->Changes((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->toDownload(); break;
        case 8: _t->picture(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PlayVideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayVideoWidget::videoLast)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PlayVideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayVideoWidget::videoNext)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PlayVideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayVideoWidget::updateImg)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject PlayVideoWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayVideoWidget.data,
      qt_meta_data_PlayVideoWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PlayVideoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayVideoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayVideoWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlayVideoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void PlayVideoWidget::videoLast()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PlayVideoWidget::videoNext()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PlayVideoWidget::updateImg()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
