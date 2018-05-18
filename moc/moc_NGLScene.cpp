/****************************************************************************
** Meta object code from reading C++ file 'NGLScene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/NGLScene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NGLScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NGLScene_t {
    QByteArrayData data[27];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NGLScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NGLScene_t qt_meta_stringdata_NGLScene = {
    {
QT_MOC_LITERAL(0, 0, 8), // "NGLScene"
QT_MOC_LITERAL(1, 9, 15), // "numBoidsChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "setAddBoids"
QT_MOC_LITERAL(4, 38, 11), // "_numOfBoids"
QT_MOC_LITERAL(5, 50, 14), // "setRemoveBoids"
QT_MOC_LITERAL(6, 65, 8), // "addBoids"
QT_MOC_LITERAL(7, 74, 11), // "removeBoids"
QT_MOC_LITERAL(8, 86, 11), // "setCohesion"
QT_MOC_LITERAL(9, 98, 7), // "_weight"
QT_MOC_LITERAL(10, 106, 13), // "setSeparation"
QT_MOC_LITERAL(11, 120, 12), // "setAlignment"
QT_MOC_LITERAL(12, 133, 13), // "setSeekWeight"
QT_MOC_LITERAL(13, 147, 11), // "setMaxSpeed"
QT_MOC_LITERAL(14, 159, 9), // "_maxSpeed"
QT_MOC_LITERAL(15, 169, 11), // "setMaxForce"
QT_MOC_LITERAL(16, 181, 9), // "_maxForce"
QT_MOC_LITERAL(17, 191, 12), // "setAwareness"
QT_MOC_LITERAL(18, 204, 16), // "_awarenessRadius"
QT_MOC_LITERAL(19, 221, 14), // "activateTarget"
QT_MOC_LITERAL(20, 236, 7), // "_active"
QT_MOC_LITERAL(21, 244, 11), // "setGoalPosX"
QT_MOC_LITERAL(22, 256, 5), // "_posX"
QT_MOC_LITERAL(23, 262, 11), // "setGoalPosY"
QT_MOC_LITERAL(24, 274, 5), // "_posY"
QT_MOC_LITERAL(25, 280, 11), // "setGoalPosZ"
QT_MOC_LITERAL(26, 292, 5) // "_posZ"

    },
    "NGLScene\0numBoidsChanged\0\0setAddBoids\0"
    "_numOfBoids\0setRemoveBoids\0addBoids\0"
    "removeBoids\0setCohesion\0_weight\0"
    "setSeparation\0setAlignment\0setSeekWeight\0"
    "setMaxSpeed\0_maxSpeed\0setMaxForce\0"
    "_maxForce\0setAwareness\0_awarenessRadius\0"
    "activateTarget\0_active\0setGoalPosX\0"
    "_posX\0setGoalPosY\0_posY\0setGoalPosZ\0"
    "_posZ"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NGLScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   97,    2, 0x0a /* Public */,
       5,    1,  100,    2, 0x0a /* Public */,
       6,    0,  103,    2, 0x0a /* Public */,
       7,    0,  104,    2, 0x0a /* Public */,
       8,    1,  105,    2, 0x0a /* Public */,
      10,    1,  108,    2, 0x0a /* Public */,
      11,    1,  111,    2, 0x0a /* Public */,
      12,    1,  114,    2, 0x0a /* Public */,
      13,    1,  117,    2, 0x0a /* Public */,
      15,    1,  120,    2, 0x0a /* Public */,
      17,    1,  123,    2, 0x0a /* Public */,
      19,    1,  126,    2, 0x0a /* Public */,
      21,    1,  129,    2, 0x0a /* Public */,
      23,    1,  132,    2, 0x0a /* Public */,
      25,    1,  135,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Double,   22,
    QMetaType::Void, QMetaType::Double,   24,
    QMetaType::Void, QMetaType::Double,   26,

       0        // eod
};

void NGLScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NGLScene *_t = static_cast<NGLScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->numBoidsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setAddBoids((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setRemoveBoids((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->addBoids(); break;
        case 4: _t->removeBoids(); break;
        case 5: _t->setCohesion((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setSeparation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setAlignment((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setSeekWeight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setMaxSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->setMaxForce((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->setAwareness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->activateTarget((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->setGoalPosX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->setGoalPosY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->setGoalPosZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NGLScene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NGLScene::numBoidsChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject NGLScene::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_NGLScene.data,
      qt_meta_data_NGLScene,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NGLScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NGLScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NGLScene.stringdata0))
        return static_cast<void*>(const_cast< NGLScene*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int NGLScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void NGLScene::numBoidsChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
