/****************************************************************************
** Meta object code from reading C++ file 'tooling.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Tooling/tooling.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tooling.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Tooling_t {
    QByteArrayData data[6];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tooling_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tooling_t qt_meta_stringdata_Tooling = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Tooling"
QT_MOC_LITERAL(1, 8, 9), // "updateGUI"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 14), // "Tooling::State"
QT_MOC_LITERAL(4, 34, 21), // "updateConnectionState"
QT_MOC_LITERAL(5, 56, 28) // "Tooling_Communication::State"

    },
    "Tooling\0updateGUI\0\0Tooling::State\0"
    "updateConnectionState\0"
    "Tooling_Communication::State"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tooling[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,

       0        // eod
};

void Tooling::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Tooling *_t = static_cast<Tooling *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateGUI((*reinterpret_cast< Tooling::State(*)>(_a[1]))); break;
        case 1: _t->updateConnectionState((*reinterpret_cast< Tooling_Communication::State(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Tooling::*_t)(Tooling::State );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Tooling::updateGUI)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Tooling::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Tooling.data,
      qt_meta_data_Tooling,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Tooling::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tooling::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Tooling.stringdata0))
        return static_cast<void*>(const_cast< Tooling*>(this));
    return QObject::qt_metacast(_clname);
}

int Tooling::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Tooling::updateGUI(Tooling::State _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
