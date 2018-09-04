#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T09:04:28
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = TestSPCS_console
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = ../bin


QMAKE_LIBDIR += ../lib/msc
QMAKE_LIBDIR += ../lib
INCLUDEPATH  += ../INCLUDE
QMAKE_LIBDIR += ../bin

DEFINES    += QWT_DLL


UI_DIR = ../../temp/ui/TestSPCS_console
OBJECTS_DIR = ../../temp/obj/TestSPCS_console
MOC_DIR = ../../temp/moc/TestSPCS_console

QMAKE_CXXFLAGS += -wd4100
QMAKE_CXXFLAGS += -wd4996 -wd4522 -wd4189

contains(QWT_CONFIG, QwtSvg) {
    QT += svg
}
else {

    DEFINES += QWT_NO_SVG
}

SOURCES += main.cpp

HEADERS +=
