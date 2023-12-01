/****************************************************************************
** Meta object code from reading C++ file 'proccomm.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../proccomm.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'proccomm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSProcCommENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSProcCommENDCLASS = QtMocHelpers::stringData(
    "ProcComm",
    "readyRead",
    "",
    "action",
    "data"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSProcCommENDCLASS_t {
    uint offsetsAndSizes[10];
    char stringdata0[9];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[5];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSProcCommENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSProcCommENDCLASS_t qt_meta_stringdata_CLASSProcCommENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "ProcComm"
        QT_MOC_LITERAL(9, 9),  // "readyRead"
        QT_MOC_LITERAL(19, 0),  // ""
        QT_MOC_LITERAL(20, 6),  // "action"
        QT_MOC_LITERAL(27, 4)   // "data"
    },
    "ProcComm",
    "readyRead",
    "",
    "action",
    "data"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSProcCommENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x0a,    1 /* Public */,
       3,    1,   27,    2, 0x0a,    2 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,

       0        // eod
};

Q_CONSTINIT const QMetaObject ProcComm::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSProcCommENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSProcCommENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSProcCommENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ProcComm, std::true_type>,
        // method 'readyRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'action'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>
    >,
    nullptr
} };

void ProcComm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProcComm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->readyRead(); break;
        case 1: _t->action((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *ProcComm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProcComm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSProcCommENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ProcComm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
