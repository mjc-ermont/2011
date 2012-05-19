#-------------------------------------------------
#
# Project created by QtCreator 2012-02-04T15:51:54
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = Logger20
TEMPLATE = app


SOURCES += main.cpp\
    Line.cpp \
    FenPrincipale.cpp \
    Donnees.cpp \
    serial.cpp \
    boardingtable.cpp

HEADERS  += Line.h \
    FenPrincipale.h \
    Donnees.h \
    serial.h \
    boardingtable.h

FORMS    += \
    FenPrincipale.ui

OTHER_FILES += \
    DefautBDD.sql.zip
