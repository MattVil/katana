/****************************************************************************
** Meta object code from reading C++ file 'BurnInTestWindow.h'
**
** Created: Thu Jul 5 13:23:02 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "inc/BurnInTestWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BurnInTestWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_BurnInTestWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      27,   17,   17,   17, 0x08,
      35,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BurnInTestWindow[] = {
    "BurnInTestWindow\0\0browse()\0start()\0exit()\0"
};

const QMetaObject BurnInTestWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BurnInTestWindow,
      qt_meta_data_BurnInTestWindow, 0 }
};

const QMetaObject *BurnInTestWindow::metaObject() const
{
    return &staticMetaObject;
}

void *BurnInTestWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BurnInTestWindow))
	return static_cast<void*>(const_cast<BurnInTestWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int BurnInTestWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: browse(); break;
        case 1: start(); break;
        case 2: exit(); break;
        }
        _id -= 3;
    }
    return _id;
}
