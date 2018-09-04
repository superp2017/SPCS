#-------------------------------------------------
#
# Project created by QtCreator 2013-09-02T14:19:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceRadar
TEMPLATE = app

DESTDIR = ../bin


INCLUDEPATH += ../../../vslib/logger/include
QMAKE_INCDIR += ../../../vslib/logger/include
QMAKE_LIBDIR += ../../../vslib/logger/lib

INCLUDEPATH += ../../../vslib/TaskManager/include
QMAKE_INCDIR += ../../../vslib/TaskManager/include
QMAKE_LIBDIR += ../../../vslib/TaskManager/lib

INCLUDEPATH += ../INCLUDE


SOURCES += main.cpp\
    harray.cpp \
    hrectanglearray.cpp \
    htrianglearray.cpp \
    hplanecirclearray.cpp \
    hgridcirclearray.cpp \
    hgenarray.cpp

HEADERS  +=  harray.h \
    hrectanglearray.h \
    htrianglearray.h \
    hplanecirclearray.h \
    hgridcirclearray.h \
    hgenarray.h

FORMS    += \
    hgenarray.ui

CONFIG(debug, debug|release) {

} else {

}
QMAKE_LFLAGS += /ignore:4099 /ignore:4044 /ignore:4100
QMAKE_CXXFLAGS += -wd4100 -wd4018 -wd4819 -wd4503 -wd4996

UI_DIR = ../../temp/ui/FaceRadar
OBJECTS_DIR = ../../temp/obj/FaceRadar
MOC_DIR = ../../temp/moc/FaceRadar
