#-------------------------------------------------
#
# Project created by QtCreator 2012-11-24T14:54:13
#
#-------------------------------------------------

QT       += core gui

TARGET = ChonoEdit
TEMPLATE = app


SOURCES += main.cpp\
        chronoedit.cpp

HEADERS  += chronoedit.h

FORMS    += chronoedit.ui


unix|win32: LIBS += -lqjson

RESOURCES += \
    ressources.qrc
