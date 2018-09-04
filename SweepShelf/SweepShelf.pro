#-------------------------------------------------
#
# Project created by QtCreator 2013-09-03T16:10:24
#
#-------------------------------------------------

QT       += core  gui serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SweepShelf
TEMPLATE = lib

DESTDIR = ../bin

UI_DIR = ../../temp/ui/SweepShelf
OBJECTS_DIR = ../../temp/obj/SweepShelf
MOC_DIR = ../../temp/moc/SweepShelf


DEFINES += SWEEPSHELF_LIBRARY

SOURCES += sweepshelf.cpp \
    operacmd.cpp \
    hserialport.cpp

HEADERS += sweepshelf.h\
        sweepshelf_global.h \
    operacmd.h \
    hserialport.h

QMAKE_POST_LINK += "cmd /c copy /y ..\bin\\$${TARGET}.lib ..\lib"

QMAKE_CXXFLAGS += -wd4100  -wd4005
QMAKE_CXXFLAGS += -wd4996  -wd4522 -wd4189

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
