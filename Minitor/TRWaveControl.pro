#-------------------------------------------------
#
# Project created by QtCreator 2014-03-31T13:10:55
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = TRWaveControl
TEMPLATE = lib

DEFINES += TRWAVECONTROL_LIBRARY

DESTDIR = ../bin

QT       += network widgets

QMAKE_CXXFLAGS += -wd4100 -wd4018 -wd4819 -wd4503 -wd4996
QMAKE_LFLAGS += /ignore:4099 /ignore:4044

QMAKE_POST_LINK += "cmd /c copy /y ..\bin\\$${TARGET}.lib ..\lib"

SOURCES += trwavecontrol.cpp \
    pclient.cpp \
    parseconfig.cpp

HEADERS += trwavecontrol.h\
        TRWaveControl_global.h \
    pclient.h \
    parseconfig.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
