#-------------------------------------------------
#
# Project created by QtCreator 2013-09-03T17:17:15
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib

DEFINES += RADARWND_LIBRARY

DESTDIR = ../bin





CONFIG(debug, debug|release) {
    TARGET = RadarWndd
} else {
    TARGET = RadarWnd
}

UI_DIR = ../../temp/ui/RadarWnd
OBJECTS_DIR = ../../temp/obj/RadarWnd
MOC_DIR = ../../temp/moc/RadarWnd

QMAKE_POST_LINK += "cmd /c copy /y ..\bin\\$${TARGET}.lib ..\lib"

INCLUDEPATH += ../INCLUDE

QMAKE_CXXFLAGS += -wd4100 -wd4018 -wd4819 -wd4503 -wd4996
QMAKE_LFLAGS += /ignore:4099 /ignore:4044

SOURCES += radarwnd.cpp \
    faceadapter.cpp \
    radarview.cpp \
    radar.cpp \
    detector.cpp \
    bkarea.cpp \
    radarscene.cpp \
    sweepline.cpp

HEADERS += radarwnd.h\
        radarwnd_global.h \
    faceadapter.h \
    radarview.h \
    radar.h \
    detector.h \
    bkarea.h \
    radarscene.h \
    sweepline.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
