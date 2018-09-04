#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T09:03:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestSPCS
TEMPLATE = app

DESTDIR = ../bin

INCLUDEPATH += ../../../vslib/logger/include
QMAKE_INCDIR += ../../../vslib/logger/include
QMAKE_LIBDIR += ../../../vslib/logger/lib

INCLUDEPATH += ../../../vslib/TaskManager/include
QMAKE_INCDIR += ../../../vslib/TaskManager/include
QMAKE_LIBDIR += ../../../vslib/TaskManager/lib

INCLUDEPATH += ../../../vslib/Boost_1.52/include
QMAKE_INCDIR += ../../../vslib/Boost_1.52/include
QMAKE_LIBDIR += ../../../vslib/Boost_1.52/lib

INCLUDEPATH += ../../../vslib/qwt-6.1.2/include
QMAKE_INCDIR += ../../../vslib/qwt-6.1.2/include
QMAKE_LIBDIR += ../../../vslib/qwt-6.1.2/lib

INCLUDEPATH  += ../Minitor
QMAKE_INCDIR += ../Minitor

QMAKE_LIBDIR += ../lib/msc
QMAKE_LIBDIR += ../lib

INCLUDEPATH  += ../INCLUDE
QMAKE_LIBDIR += ../bin
QMAKE_INCDIR += ../RadarWnd

DEFINES    += QWT_DLL

CONFIG(debug, debug|release) {
    LIBS += qwtd.lib
    LIBS += Minitor.lib
    LIBS += RadarWndd.lib
} else {
    LIBS += qwt.lib
    LIBS += Minitor.lib
    LIBS += RadarWndd.lib
}

CONFIG(debug, debug|release) {
    LIBS += visa32.lib
} else {
    LIBS += visa32.lib
}

UI_DIR = ../../temp/ui/TestSPCS
OBJECTS_DIR = ../../temp/obj/TestSPCS
MOC_DIR = ../../temp/moc/TestSPCS

QMAKE_CXXFLAGS += -wd4100
QMAKE_CXXFLAGS += -wd4996

contains(QWT_CONFIG, QwtSvg) {
    QT += svg
}
else {

    DEFINES += QWT_NO_SVG
}


SOURCES += main.cpp\
        mainwindow.cpp \


HEADERS  += mainwindow.h \

