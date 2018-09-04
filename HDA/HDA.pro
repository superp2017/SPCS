#-------------------------------------------------
#
# Project created by QtCreator 2013-08-29T10:09:26
#
#-------------------------------------------------

QT        += core gui

QT       += network widgets

TARGET   = HDA
TEMPLATE = lib

DESTDIR = ../bin

DEFINES += HDA_LIBRARY


UI_DIR = ../../temp/ui/HDA
OBJECTS_DIR = ../../temp/obj/HDA
MOC_DIR = ../../temp/moc/HDA

INCLUDEPATH += ../INCLUDE

QMAKE_CXXFLAGS += -wd4100 -wd4018 -wd4819 -wd4503 -wd4996
QMAKE_LFLAGS += /ignore:4099 /ignore:4044

SOURCES += \
    tswmatrixs.cpp \
    teleswitch.cpp \
    tdevice.cpp \
    tattenuation.cpp \
    rebpci2323.cpp \
    pci_cardcent.cpp \
    tmini_1to2.cpp \
    ic_controlcard.cpp



HEADERS += \
    tswmatrixs.h \
    teleswitch.h \
    tdevice.h \
    tattenuation.h \
    rebpci2323.h \
    pci_cardcent.h \
    hda_global.h \
    hda.h \
    tmini_1to2.h \
    ic_controlcard.h


INCLUDEPATH  += ../INCLUDE
QMAKE_LIBDIR += ../lib/msc
QMAKE_LIBDIR += ../lib
QMAKE_LIBDIR += ../bin

QMAKE_POST_LINK += "cmd /c copy /y ..\bin\\$${TARGET}.lib ..\lib"

CONFIG(debug, debug|release): LIBS += \
                               PCI2323.lib
CONFIG(release, debug|release): LIBS +=  \
                                PCI2323.lib

INCLUDEPATH += ../../../vslib/IC_Control/include
QMAKE_INCDIR += ../../../vslib/IC_Control/include
QMAKE_LIBDIR += ../../../vslib/IC_Control/lib
LIBS += test_comm.lib


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
