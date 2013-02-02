/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created: Sat Feb 2 16:29:45 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Logger21/dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AskDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      34,   29,   10,   10, 0x08,
      78,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AskDialog[] = {
    "AskDialog\0\0continueClicked()\0arg1\0"
    "on_selectEntry_currentIndexChanged(QString)\0"
    "on_addToList_clicked()\0"
};

void AskDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AskDialog *_t = static_cast<AskDialog *>(_o);
        switch (_id) {
        case 0: _t->continueClicked(); break;
        case 1: _t->on_selectEntry_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_addToList_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AskDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AskDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AskDialog,
      qt_meta_data_AskDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AskDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AskDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AskDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AskDialog))
        return static_cast<void*>(const_cast< AskDialog*>(this));
    if (!strcmp(_clname, "Ui::Dialog"))
        return static_cast< Ui::Dialog*>(const_cast< AskDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int AskDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
