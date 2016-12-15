/****************************************************************************
** Meta object code from reading C++ file 'summary.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../summary.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'summary.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Summary_t {
    QByteArrayData data[13];
    char stringdata[260];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Summary_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Summary_t qt_meta_stringdata_Summary = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Summary"
QT_MOC_LITERAL(1, 8, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(4, 55, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(5, 79, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(6, 103, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(7, 127, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(8, 155, 5), // "index"
QT_MOC_LITERAL(9, 161, 20), // "on_nameBox_activated"
QT_MOC_LITERAL(10, 182, 24), // "on_graphChoice_activated"
QT_MOC_LITERAL(11, 207, 26), // "on_graphSelector_activated"
QT_MOC_LITERAL(12, 234, 25) // "on_dateSelector_activated"

    },
    "Summary\0on_pushButton_clicked\0\0"
    "on_pushButton_3_clicked\0on_pushButton_4_clicked\0"
    "on_pushButton_5_clicked\0on_pushButton_6_clicked\0"
    "on_tabWidget_currentChanged\0index\0"
    "on_nameBox_activated\0on_graphChoice_activated\0"
    "on_graphSelector_activated\0"
    "on_dateSelector_activated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Summary[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    1,   69,    2, 0x08 /* Private */,
       9,    1,   72,    2, 0x08 /* Private */,
      10,    1,   75,    2, 0x08 /* Private */,
      11,    1,   78,    2, 0x08 /* Private */,
      12,    1,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void Summary::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Summary *_t = static_cast<Summary *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_3_clicked(); break;
        case 2: _t->on_pushButton_4_clicked(); break;
        case 3: _t->on_pushButton_5_clicked(); break;
        case 4: _t->on_pushButton_6_clicked(); break;
        case 5: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_nameBox_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_graphChoice_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_graphSelector_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_dateSelector_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Summary::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Summary.data,
      qt_meta_data_Summary,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Summary::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Summary::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Summary.stringdata))
        return static_cast<void*>(const_cast< Summary*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Summary::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
