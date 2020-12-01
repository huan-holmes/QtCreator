/****************************************************************************
** Meta object code from reading C++ file 'ustarservice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../UStarService/ustarservice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ustarservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UStarService_t {
    QByteArrayData data[16];
    char stringdata0[207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UStarService_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UStarService_t qt_meta_stringdata_UStarService = {
    {
QT_MOC_LITERAL(0, 0, 12), // "UStarService"
QT_MOC_LITERAL(1, 13, 11), // "onUpClicked"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "onDownClicked"
QT_MOC_LITERAL(4, 40, 14), // "onResetClicked"
QT_MOC_LITERAL(5, 55, 13), // "OnLiftClicked"
QT_MOC_LITERAL(6, 69, 14), // "OnRightClicked"
QT_MOC_LITERAL(7, 84, 15), // "onLittleClicked"
QT_MOC_LITERAL(8, 100, 12), // "onBigClicked"
QT_MOC_LITERAL(9, 113, 14), // "onClearClicked"
QT_MOC_LITERAL(10, 128, 13), // "onLineClicked"
QT_MOC_LITERAL(11, 142, 20), // "onVirtualWallClicked"
QT_MOC_LITERAL(12, 163, 13), // "onOpenClicked"
QT_MOC_LITERAL(13, 177, 10), // "paintEvent"
QT_MOC_LITERAL(14, 188, 12), // "QPaintEvent*"
QT_MOC_LITERAL(15, 201, 5) // "event"

    },
    "UStarService\0onUpClicked\0\0onDownClicked\0"
    "onResetClicked\0OnLiftClicked\0"
    "OnRightClicked\0onLittleClicked\0"
    "onBigClicked\0onClearClicked\0onLineClicked\0"
    "onVirtualWallClicked\0onOpenClicked\0"
    "paintEvent\0QPaintEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UStarService[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    1,   85,    2, 0x08 /* Private */,

 // slots: parameters
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
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

void UStarService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UStarService *_t = static_cast<UStarService *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onUpClicked(); break;
        case 1: _t->onDownClicked(); break;
        case 2: _t->onResetClicked(); break;
        case 3: _t->OnLiftClicked(); break;
        case 4: _t->OnRightClicked(); break;
        case 5: _t->onLittleClicked(); break;
        case 6: _t->onBigClicked(); break;
        case 7: _t->onClearClicked(); break;
        case 8: _t->onLineClicked(); break;
        case 9: _t->onVirtualWallClicked(); break;
        case 10: _t->onOpenClicked(); break;
        case 11: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject UStarService::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UStarService.data,
      qt_meta_data_UStarService,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UStarService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UStarService::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UStarService.stringdata0))
        return static_cast<void*>(const_cast< UStarService*>(this));
    return QWidget::qt_metacast(_clname);
}

int UStarService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
