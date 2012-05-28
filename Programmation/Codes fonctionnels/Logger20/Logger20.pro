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
    graphicview.cpp

HEADERS  += Line.h \
    FenPrincipale.h \
    Donnees.h \
    serial.h \
    boardingtable.h \
    defines.h \
    graphicview.h

FORMS    += \
    FenPrincipale.ui

CONFIG += lucas

lucas {
    LIBS += C:\QtSDK\Desktop\Qt\4.8.1\mingw\lib\libqwtd.a
} #Ajouter les différents chemins selon les PC utilisés.
