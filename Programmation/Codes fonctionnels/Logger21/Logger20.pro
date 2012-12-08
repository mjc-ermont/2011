#-------------------------------------------------
#
# Project created by QtCreator 2012-02-04T15:51:54
#
#-------------------------------------------------

DEFINES += QWT_DLL

QT       += core gui webkit
QT       += sql

TARGET = Logger20
TEMPLATE = app



SOURCES += main.cpp\
    Line.cpp \
    FenPrincipale.cpp \
    Donnees.cpp \
    serial.cpp \
    boardingtable.cpp \
    graphicview.cpp \
    mapsview.cpp \
    sensormanager.cpp \
    sensor.cpp \
    value.cpp \
    UI/mapsview.cpp \
    UI/graphicview.cpp \
    UI/boardingtable.cpp \
    InPut/serial.cpp \
    InPut/sensormanager.cpp \
    InPut/sensor.cpp \
    InPut/sensorvalue.cpp

HEADERS  += Line.h \
    FenPrincipale.h \
    Donnees.h \
    serial.h \
    boardingtable.h \
    defines.h \
    graphicview.h \
    mapsview.h \
    sensormanager.h \
    sensor.h \
    value.h \
    UI/mapsview.h \
    UI/graphmanager.h \
    UI/graphicview.h \
    InPut/serial.h \
    InPut/sensormanager.h \
    InPut/sensor.h \
    UI/boardingtable.h \
    InPut/sensorvalue.h

FORMS    += FenPrincipale.ui

CONFIG += linusque

lucas {
    LIBS += C:\QtSDK\Desktop\Qt\4.8.1\mingw\lib\libqwtd.a
}

robotik {
    LIBS += C:\qwt-6.0.1\lib\libqwtd.a
}

linusque {
    LIBS += /usr/lib/libqwt.so
}

 #Ajouter les diffrents chemins selon les PC utiliss.

RESOURCES += ressources.qrc