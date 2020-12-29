/****************************************************************************
** Meta object code from reading C++ file 'mappingwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../UStarService/mappingwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mappingwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MappingWidget_t {
    QByteArrayData data[13];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MappingWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MappingWidget_t qt_meta_stringdata_MappingWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MappingWidget"
QT_MOC_LITERAL(1, 14, 16), // "onMappingClicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 15), // "onMapBagClicked"
QT_MOC_LITERAL(4, 48, 12), // "onPOIClicked"
QT_MOC_LITERAL(5, 61, 21), // "onOperationLogClicked"
QT_MOC_LITERAL(6, 83, 20), // "onLocalImportClicked"
QT_MOC_LITERAL(7, 104, 18), // "onRoomPointClicked"
QT_MOC_LITERAL(8, 123, 18), // "onGoalPointClicked"
QT_MOC_LITERAL(9, 142, 24), // "onDeceleratePointClicked"
QT_MOC_LITERAL(10, 167, 20), // "onChargePointClicked"
QT_MOC_LITERAL(11, 188, 18), // "onLiftPointClicked"
QT_MOC_LITERAL(12, 207, 19) // "onOtherPointClicked"

    },
    "MappingWidget\0onMappingClicked\0\0"
    "onMapBagClicked\0onPOIClicked\0"
    "onOperationLogClicked\0onLocalImportClicked\0"
    "onRoomPointClicked\0onGoalPointClicked\0"
    "onDeceleratePointClicked\0onChargePointClicked\0"
    "onLiftPointClicked\0onOtherPointClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MappingWidget[] = {

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
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

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

       0        // eod
};

void MappingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MappingWidget *_t = static_cast<MappingWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onMappingClicked(); break;
        case 1: _t->onMapBagClicked(); break;
        case 2: _t->onPOIClicked(); break;
        case 3: _t->onOperationLogClicked(); break;
        case 4: _t->onLocalImportClicked(); break;
        case 5: _t->onRoomPointClicked(); break;
        case 6: _t->onGoalPointClicked(); break;
        case 7: _t->onDeceleratePointClicked(); break;
        case 8: _t->onChargePointClicked(); break;
        case 9: _t->onLiftPointClicked(); break;
        case 10: _t->onOtherPointClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MappingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MappingWidget.data,
      qt_meta_data_MappingWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MappingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MappingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MappingWidget.stringdata0))
        return static_cast<void*>(const_cast< MappingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MappingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
