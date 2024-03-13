/****************************************************************************
** Meta object code from reading C++ file 'monitorwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/monitorwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'monitorwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MonitorWidget_t {
    QByteArrayData data[11];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MonitorWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MonitorWidget_t qt_meta_stringdata_MonitorWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MonitorWidget"
QT_MOC_LITERAL(1, 14, 9), // "updateImg"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "showImg"
QT_MOC_LITERAL(4, 33, 5), // "image"
QT_MOC_LITERAL(5, 39, 8), // "toPlayer"
QT_MOC_LITERAL(6, 48, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 65, 7), // "usbItem"
QT_MOC_LITERAL(8, 73, 12), // "switchSingle"
QT_MOC_LITERAL(9, 86, 14), // "switchMultiple"
QT_MOC_LITERAL(10, 101, 7) // "picture"

    },
    "MonitorWidget\0updateImg\0\0showImg\0image\0"
    "toPlayer\0QListWidgetItem*\0usbItem\0"
    "switchSingle\0switchMultiple\0picture"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MonitorWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   45,    2, 0x0a /* Public */,
       5,    1,   48,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,
       9,    0,   52,    2, 0x0a /* Public */,
      10,    0,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MonitorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MonitorWidget *_t = static_cast<MonitorWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateImg(); break;
        case 1: _t->showImg((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->toPlayer((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->switchSingle(); break;
        case 4: _t->switchMultiple(); break;
        case 5: _t->picture(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MonitorWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MonitorWidget::updateImg)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MonitorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MonitorWidget.data,
      qt_meta_data_MonitorWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MonitorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MonitorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MonitorWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MonitorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MonitorWidget::updateImg()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
