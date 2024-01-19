/****************************************************************************
** Meta object code from reading C++ file 'slider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../src/vision_debug_widgets/include/vision_debug_widgets/slider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'slider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_vision_debug_widgets__Slider_t {
    QByteArrayData data[8];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vision_debug_widgets__Slider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vision_debug_widgets__Slider_t qt_meta_stringdata_vision_debug_widgets__Slider = {
    {
QT_MOC_LITERAL(0, 0, 28), // "vision_debug_widgets::Slider"
QT_MOC_LITERAL(1, 29, 10), // "valChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 12), // "onValChanged"
QT_MOC_LITERAL(4, 54, 5), // "value"
QT_MOC_LITERAL(5, 60, 18), // "onValChangedDouble"
QT_MOC_LITERAL(6, 79, 16), // "onEditValChanged"
QT_MOC_LITERAL(7, 96, 22) // "onEditValChangedDouble"

    },
    "vision_debug_widgets::Slider\0valChanged\0"
    "\0onValChanged\0value\0onValChangedDouble\0"
    "onEditValChanged\0onEditValChangedDouble"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vision_debug_widgets__Slider[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   40,    2, 0x08 /* Private */,
       5,    1,   43,    2, 0x08 /* Private */,
       6,    0,   46,    2, 0x08 /* Private */,
       7,    0,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void vision_debug_widgets::Slider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Slider *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valChanged(); break;
        case 1: _t->onValChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onValChangedDouble((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onEditValChanged(); break;
        case 4: _t->onEditValChangedDouble(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Slider::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Slider::valChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject vision_debug_widgets::Slider::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_vision_debug_widgets__Slider.data,
    qt_meta_data_vision_debug_widgets__Slider,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *vision_debug_widgets::Slider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vision_debug_widgets::Slider::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vision_debug_widgets__Slider.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int vision_debug_widgets::Slider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void vision_debug_widgets::Slider::valChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
