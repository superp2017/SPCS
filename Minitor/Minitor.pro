#-------------------------------------------------
#
# Project created by QtCreator 2013-12-05T17:16:36
#
#-------------------------------------------------

QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Minitor
TEMPLATE = lib
DEFINES += MONITOR_LIBRARY

DESTDIR = ../bin


UI_DIR = ../../temp/ui/Minitor
OBJECTS_DIR = ../../temp/obj/Minitor
MOC_DIR = ../../temp/moc/Minitor

QMAKE_CXXFLAGS += -wd4100 -wd4018 -wd4819 -wd4503 -wd4996
QMAKE_LFLAGS += /ignore:4099 /ignore:4044

INCLUDEPATH  += ../INCLUDE
QMAKE_LIBDIR += ../lib/msc
QMAKE_LIBDIR += ../lib
QMAKE_LIBDIR += ../bin


INCLUDEPATH += ../../../vslib/qwt-6.1.2/include
QMAKE_INCDIR += ../../../vslib/qwt-6.1.2/include
QMAKE_LIBDIR += ../../../vslib/qwt-6.1.2/lib



CONFIG(debug, debug|release) {
    LIBS += qwtd.lib
} else {
    LIBS += qwt.lib
}



DEFINES    += QWT_DLL

contains(QWT_CONFIG, QwtSvg) {
    QT += svg
}
else {

    DEFINES += QWT_NO_SVG
}


SOURCES +=  tmonitor.cpp \
    tplot.cpp \
    tplotcurve.cpp \
    tplotview.cpp \
    t_left.cpp \
    t_right.cpp


HEADERS  += \
    monitor_global.h \
    tmonitor.h \
    tplot.h \
    tplotcurve.h \
    tplotview.h \
    t_left.h \
    t_right.h
