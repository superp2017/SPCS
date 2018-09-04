#-------------------------------------------------
#
# Project created by QtCreator 2014-02-19T14:49:15
#
#-------------------------------------------------

QT       -= gui

TARGET = ConfigPhase
TEMPLATE = lib

DESTDIR = ../bin

DEFINES += CONFIGPHASE_LIBRARY

SOURCES += configphase.cpp

HEADERS += configphase.h\
        configphase_global.h

QMAKE_CXXFLAGS += -wd4522 -wd4189

QMAKE_POST_LINK += "cmd /c copy /y ..\bin\\$${TARGET}.lib ..\lib"

INCLUDEPATH  += ../INCLUDE
QMAKE_LIBDIR += ../bin

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
