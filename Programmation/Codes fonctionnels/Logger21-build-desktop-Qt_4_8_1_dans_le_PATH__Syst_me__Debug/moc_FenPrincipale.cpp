/****************************************************************************
** Meta object code from reading C++ file 'FenPrincipale.h'
**
** Created: Sat Feb 2 15:34:54 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Logger21/FenPrincipale.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FenPrincipale.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FenPrincipale[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   15,   14,   14, 0x0a,
      40,   14,   14,   14, 0x0a,
      53,   14,   14,   14, 0x0a,
      87,   14,   14,   14, 0x0a,
      98,   14,   14,   14, 0x0a,
     119,   14,   14,   14, 0x0a,
     140,   14,   14,   14, 0x0a,
     158,   14,   14,   14, 0x0a,
     181,   14,   14,   14, 0x0a,
     210,   14,   14,   14, 0x0a,
     231,   14,   14,   14, 0x0a,
     258,  252,   14,   14, 0x0a,
     298,   14,   14,   14, 0x0a,
     321,   14,   14,   14, 0x0a,
     335,   14,   14,   14, 0x0a,
     352,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FenPrincipale[] = {
    "FenPrincipale\0\0message\0message(QString)\0"
    "requestAct()\0informationsReceived(QStringList)\0"
    "syncTime()\0on_b_param_clicked()\0"
    "on_b_table_clicked()\0on_b_tb_clicked()\0"
    "on_b_console_clicked()\0"
    "on_actionQuitter_triggered()\0"
    "on_b_carte_clicked()\0on_b_graph_clicked()\0"
    "index\0on_sel_capteur_currentIndexChanged(int)\0"
    "on_add_graph_clicked()\0graphClosed()\0"
    "optimise_graph()\0on_btn_optimiser_clicked()\0"
};

void FenPrincipale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FenPrincipale *_t = static_cast<FenPrincipale *>(_o);
        switch (_id) {
        case 0: _t->message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->requestAct(); break;
        case 2: _t->informationsReceived((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->syncTime(); break;
        case 4: _t->on_b_param_clicked(); break;
        case 5: _t->on_b_table_clicked(); break;
        case 6: _t->on_b_tb_clicked(); break;
        case 7: _t->on_b_console_clicked(); break;
        case 8: _t->on_actionQuitter_triggered(); break;
        case 9: _t->on_b_carte_clicked(); break;
        case 10: _t->on_b_graph_clicked(); break;
        case 11: _t->on_sel_capteur_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_add_graph_clicked(); break;
        case 13: _t->graphClosed(); break;
        case 14: _t->optimise_graph(); break;
        case 15: _t->on_btn_optimiser_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FenPrincipale::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FenPrincipale::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FenPrincipale,
      qt_meta_data_FenPrincipale, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FenPrincipale::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FenPrincipale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FenPrincipale::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FenPrincipale))
        return static_cast<void*>(const_cast< FenPrincipale*>(this));
    if (!strcmp(_clname, "Ui::FenPrincipale"))
        return static_cast< Ui::FenPrincipale*>(const_cast< FenPrincipale*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FenPrincipale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
