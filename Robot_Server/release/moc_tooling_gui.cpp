/****************************************************************************
** Meta object code from reading C++ file 'tooling_gui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Tooling/tooling_gui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tooling_gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Tooling_GUI_t {
    QByteArrayData data[11];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tooling_GUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tooling_GUI_t qt_meta_stringdata_Tooling_GUI = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Tooling_GUI"
QT_MOC_LITERAL(1, 12, 9), // "updateGUI"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 14), // "Tooling::State"
QT_MOC_LITERAL(4, 38, 6), // "_state"
QT_MOC_LITERAL(5, 45, 18), // "update_GUI_Message"
QT_MOC_LITERAL(6, 64, 4), // "_str"
QT_MOC_LITERAL(7, 69, 18), // "flashYellowTimeout"
QT_MOC_LITERAL(8, 88, 17), // "flashGreenTimeout"
QT_MOC_LITERAL(9, 106, 15), // "flashRedTimeout"
QT_MOC_LITERAL(10, 122, 15) // "clockTimeUpdate"

    },
    "Tooling_GUI\0updateGUI\0\0Tooling::State\0"
    "_state\0update_GUI_Message\0_str\0"
    "flashYellowTimeout\0flashGreenTimeout\0"
    "flashRedTimeout\0clockTimeUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tooling_GUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       5,    1,   47,    2, 0x08 /* Private */,
       7,    0,   50,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,
       9,    0,   52,    2, 0x08 /* Private */,
      10,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Tooling_GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Tooling_GUI *_t = static_cast<Tooling_GUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateGUI((*reinterpret_cast< Tooling::State(*)>(_a[1]))); break;
        case 1: _t->update_GUI_Message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->flashYellowTimeout(); break;
        case 3: _t->flashGreenTimeout(); break;
        case 4: _t->flashRedTimeout(); break;
        case 5: _t->clockTimeUpdate(); break;
        default: ;
        }
    }
}

const QMetaObject Tooling_GUI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Tooling_GUI.data,
      qt_meta_data_Tooling_GUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Tooling_GUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tooling_GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Tooling_GUI.stringdata0))
        return static_cast<void*>(const_cast< Tooling_GUI*>(this));
    return QObject::qt_metacast(_clname);
}

int Tooling_GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
