#-------------------------------------------------
#
# Project created by QtCreator 2012-02-04T15:51:54
#
#-------------------------------------------------

DEFINES += QWT_DLL

QT       += core gui webkit
QT       += sql
QT       += network

TARGET = Logger20
TEMPLATE = app



SOURCES += main.cpp\
    FenPrincipale.cpp \
    UI/mapsview.cpp \
    UI/graphicview.cpp \
    UI/boardingtable.cpp \
    InPut/serial.cpp \
    InPut/sensormanager.cpp \
    InPut/sensor.cpp \
    InPut/sensorvalue.cpp \
    dialog.cpp \
    ../ChronoReaderWidget/eventbox.cpp \
    ../ChronoReaderWidget/chronoreaderwidget.cpp \
    InPut/fileimportdialog.cpp \
    tablemgr.cpp \
    ../ChronoReaderWidget/TimeCalcs/timecalcs.cpp

HEADERS  += FenPrincipale.h \
    UI/mapsview.h \
    UI/graphicview.h \
    InPut/serial.h \
    InPut/sensormanager.h \
    InPut/sensor.h \
    UI/boardingtable.h \
    InPut/sensorvalue.h \
    defines.h \
    dialog.h \
    ../ChronoReaderWidget/eventbox.h \
    ../ChronoReaderWidget/chronoreaderwidget.h \
    InPut/fileimportdialog.h \
    tablemgr.h \
    ../ChronoReaderWidget/TimeCalcs/timecalcs.h

FORMS    += FenPrincipale.ui \
    dialog.ui \
    ../ChronoReaderWidget/eventbox.ui \
    ../ChronoReaderWidget/chronoreaderwidget.ui \
    InPut/fileimportdialog.ui

CONFIG += linusque

lucas {
    LIBS += C:\\QtSDK\\Desktop\\Qt\\4.8.1\\mingw\\lib\\libqwtd.a
}

robotik {
    LIBS += C:\\qwt-6.0.1\\lib\\libqwtd.a
}

linusque {
    LIBS += /usr/lib/libqwt.so
    LIBS += -lqjson
}

 #Ajouter les diffrents chemins selon les PC utiliss.

RESOURCES += ressources.qrc

OTHER_FILES += \
    ../ChronoReaderWidget/ChronoReaderWidget.pro \
    ../ChronoReaderWidget/chronologie.json
