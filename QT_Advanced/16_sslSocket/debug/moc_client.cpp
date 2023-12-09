/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../client.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSClientENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSClientENDCLASS = QtMocHelpers::stringData(
    "Client",
    "connectToHost",
    "",
    "host",
    "port",
    "disconnect",
    "connected",
    "disconnected",
    "error",
    "QAbstractSocket::SocketError",
    "socketError",
    "stateChanged",
    "QAbstractSocket::SocketState",
    "socketState",
    "readRead",
    "encrypted",
    "encryptedBytesWritten",
    "written",
    "modeChanged",
    "QSslSocket::SslMode",
    "mode",
    "peerVerifyError",
    "QSslError",
    "preSharedKeyAutenticationRequired",
    "QSslPreSharedKeyAuthenticator*",
    "autenticator",
    "sslErrors",
    "QList<QSslError>",
    "errors"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSClientENDCLASS_t {
    uint offsetsAndSizes[58];
    char stringdata0[7];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[5];
    char stringdata5[11];
    char stringdata6[10];
    char stringdata7[13];
    char stringdata8[6];
    char stringdata9[29];
    char stringdata10[12];
    char stringdata11[13];
    char stringdata12[29];
    char stringdata13[12];
    char stringdata14[9];
    char stringdata15[10];
    char stringdata16[22];
    char stringdata17[8];
    char stringdata18[12];
    char stringdata19[20];
    char stringdata20[5];
    char stringdata21[16];
    char stringdata22[10];
    char stringdata23[34];
    char stringdata24[31];
    char stringdata25[13];
    char stringdata26[10];
    char stringdata27[17];
    char stringdata28[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSClientENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSClientENDCLASS_t qt_meta_stringdata_CLASSClientENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "Client"
        QT_MOC_LITERAL(7, 13),  // "connectToHost"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 4),  // "host"
        QT_MOC_LITERAL(27, 4),  // "port"
        QT_MOC_LITERAL(32, 10),  // "disconnect"
        QT_MOC_LITERAL(43, 9),  // "connected"
        QT_MOC_LITERAL(53, 12),  // "disconnected"
        QT_MOC_LITERAL(66, 5),  // "error"
        QT_MOC_LITERAL(72, 28),  // "QAbstractSocket::SocketError"
        QT_MOC_LITERAL(101, 11),  // "socketError"
        QT_MOC_LITERAL(113, 12),  // "stateChanged"
        QT_MOC_LITERAL(126, 28),  // "QAbstractSocket::SocketState"
        QT_MOC_LITERAL(155, 11),  // "socketState"
        QT_MOC_LITERAL(167, 8),  // "readRead"
        QT_MOC_LITERAL(176, 9),  // "encrypted"
        QT_MOC_LITERAL(186, 21),  // "encryptedBytesWritten"
        QT_MOC_LITERAL(208, 7),  // "written"
        QT_MOC_LITERAL(216, 11),  // "modeChanged"
        QT_MOC_LITERAL(228, 19),  // "QSslSocket::SslMode"
        QT_MOC_LITERAL(248, 4),  // "mode"
        QT_MOC_LITERAL(253, 15),  // "peerVerifyError"
        QT_MOC_LITERAL(269, 9),  // "QSslError"
        QT_MOC_LITERAL(279, 33),  // "preSharedKeyAutenticationRequ..."
        QT_MOC_LITERAL(313, 30),  // "QSslPreSharedKeyAuthenticator*"
        QT_MOC_LITERAL(344, 12),  // "autenticator"
        QT_MOC_LITERAL(357, 9),  // "sslErrors"
        QT_MOC_LITERAL(367, 16),  // "QList<QSslError>"
        QT_MOC_LITERAL(384, 6)   // "errors"
    },
    "Client",
    "connectToHost",
    "",
    "host",
    "port",
    "disconnect",
    "connected",
    "disconnected",
    "error",
    "QAbstractSocket::SocketError",
    "socketError",
    "stateChanged",
    "QAbstractSocket::SocketState",
    "socketState",
    "readRead",
    "encrypted",
    "encryptedBytesWritten",
    "written",
    "modeChanged",
    "QSslSocket::SslMode",
    "mode",
    "peerVerifyError",
    "QSslError",
    "preSharedKeyAutenticationRequired",
    "QSslPreSharedKeyAuthenticator*",
    "autenticator",
    "sslErrors",
    "QList<QSslError>",
    "errors"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSClientENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   92,    2, 0x0a,    1 /* Public */,
       5,    0,   97,    2, 0x0a,    4 /* Public */,
       6,    0,   98,    2, 0x08,    5 /* Private */,
       7,    0,   99,    2, 0x08,    6 /* Private */,
       8,    1,  100,    2, 0x08,    7 /* Private */,
      11,    1,  103,    2, 0x08,    9 /* Private */,
      14,    0,  106,    2, 0x08,   11 /* Private */,
      15,    0,  107,    2, 0x08,   12 /* Private */,
      16,    1,  108,    2, 0x08,   13 /* Private */,
      18,    1,  111,    2, 0x08,   15 /* Private */,
      21,    1,  114,    2, 0x08,   17 /* Private */,
      23,    1,  117,    2, 0x08,   19 /* Private */,
      26,    1,  120,    2, 0x08,   21 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   17,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, 0x80000000 | 22,    8,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void, 0x80000000 | 27,   28,

       0        // eod
};

Q_CONSTINIT const QMetaObject Client::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSClientENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSClientENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSClientENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Client, std::true_type>,
        // method 'connectToHost'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint16, std::false_type>,
        // method 'disconnect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'error'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>,
        // method 'stateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketState, std::false_type>,
        // method 'readRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'encrypted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'encryptedBytesWritten'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'modeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSslSocket::SslMode, std::false_type>,
        // method 'peerVerifyError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QSslError &, std::false_type>,
        // method 'preSharedKeyAutenticationRequired'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSslPreSharedKeyAuthenticator *, std::false_type>,
        // method 'sslErrors'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QSslError> &, std::false_type>
    >,
    nullptr
} };

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Client *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connectToHost((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint16>>(_a[2]))); break;
        case 1: _t->disconnect(); break;
        case 2: _t->connected(); break;
        case 3: _t->disconnected(); break;
        case 4: _t->error((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 5: _t->stateChanged((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketState>>(_a[1]))); break;
        case 6: _t->readRead(); break;
        case 7: _t->encrypted(); break;
        case 8: _t->encryptedBytesWritten((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 9: _t->modeChanged((*reinterpret_cast< std::add_pointer_t<QSslSocket::SslMode>>(_a[1]))); break;
        case 10: _t->peerVerifyError((*reinterpret_cast< std::add_pointer_t<QSslError>>(_a[1]))); break;
        case 11: _t->preSharedKeyAutenticationRequired((*reinterpret_cast< std::add_pointer_t<QSslPreSharedKeyAuthenticator*>>(_a[1]))); break;
        case 12: _t->sslErrors((*reinterpret_cast< std::add_pointer_t<QList<QSslError>>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketState >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QSslPreSharedKeyAuthenticator* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QSslError> >(); break;
            }
            break;
        }
    }
}

const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSClientENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
