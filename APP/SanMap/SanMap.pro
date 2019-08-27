#-------------------------------------------------
#
# Project created by QtCreator 2019-07-19T12:34:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SanMap
TEMPLATE = app

INCLUDEPATH +=  ../../Module\
                ../../Module/SM_DemoSet\


CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../../../build/bin/Debug
    TARGET = SanMapd
    LIBS += ../../../build/bin/Debug/SM_DemoSetd.lib
}else{
    DESTDIR = $$PWD/../../../build/bin/Release
    TARGET = SanMap
    LIBS += $$PWD/../../../build/bin/Release/SM_DemoSet.lib
}

SOURCES += main.cpp\
        SM_WndMain.cpp

HEADERS  += SM_WndMain.h

FORMS    += SM_WndMain.ui
