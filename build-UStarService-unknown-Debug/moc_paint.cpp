/****************************************************************************
** Meta object code from reading C++ file 'paint.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../UStarService/paint.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paint.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Paint_t {
    QByteArrayData data[15];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Paint_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Paint_t qt_meta_stringdata_Paint = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Paint"
QT_MOC_LITERAL(1, 6, 10), // "paintEvent"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 12), // "QPaintEvent*"
QT_MOC_LITERAL(4, 31, 5), // "event"
QT_MOC_LITERAL(5, 37, 11), // "onUpClicked"
QT_MOC_LITERAL(6, 49, 13), // "onDownClicked"
QT_MOC_LITERAL(7, 63, 14), // "onResetClicked"
QT_MOC_LITERAL(8, 78, 13), // "OnLeftClicked"
QT_MOC_LITERAL(9, 92, 14), // "OnRightClicked"
QT_MOC_LITERAL(10, 107, 15), // "onLittleClicked"
QT_MOC_LITERAL(11, 123, 12), // "onBigClicked"
QT_MOC_LITERAL(12, 136, 14), // "onClearClicked"
QT_MOC_LITERAL(13, 151, 13), // "onLineClicked"
QT_MOC_LITERAL(14, 165, 20) // "onVirtualWallClicked"

    },
    "Paint\0paintEvent\0\0QPaintEvent*\0event\0"
    "onUpClicked\0onDownClicked\0onResetClicked\0"
    "OnLeftClicked\0OnRightClicked\0"
    "onLittleClicked\0onBigClicked\0"
    "onClearClicked\0onLineClicked\0"
    "onVirtualWallClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Paint[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,
      13,    0,   80,    2, 0x08 /* Private */,
      14,    0,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Paint::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Paint *_t = static_cast<Paint *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        case 1: _t->onUpClicked(); break;
        case 2: _t->onDownClicked(); break;
        case 3: _t->onResetClicked(); break;
        case 4: _t->OnLeftClicked(); break;
        case 5: _t->OnRightClicked(); break;
        case 6: _t->onLittleClicked(); break;
        case 7: _t->onBigClicked(); break;
        case 8: _t->onClearClicked(); break;
        case 9: _t->onLineClicked(); break;
        case 10: _t->onVirtualWallClicked(); break;
        default: ;
        }
    }
}

const QMetaObject Paint::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Paint.data,
      qt_meta_data_Paint,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Paint::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Paint::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Paint.stringdata0))
        return static_cast<void*>(const_cast< Paint*>(this));
    return QWidget::qt_metacast(_clname);
}

int Paint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
