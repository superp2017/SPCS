#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T09:03:36
#
#-------------------------------------------------

QT       += core gui serialport
QT       += network widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SPCS
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


INCLUDEPATH += ../../../vslib/libxl/include
QMAKE_INCDIR += ../../../vslib/libxl/include
QMAKE_LIBDIR += ../../../vslib/libxl/lib

INCLUDEPATH += ../../../vslib/licV/include
QMAKE_INCDIR += ../../../vslib/licV/include
QMAKE_LIBDIR += ../../../vslib/licV/lib

INCLUDEPATH += ../../../vslib/IC_Control/include
QMAKE_INCDIR += ../../../vslib/IC_Control/include
QMAKE_LIBDIR += ../../../vslib/IC_Control/lib
LIBS += test_comm.lib


INCLUDEPATH += ../Calibration

QMAKE_INCDIR += ../RadarWnd

INCLUDEPATH  += ../HDA
QMAKE_INCDIR += ../HDA

INCLUDEPATH  += ../ConfigPhase
QMAKE_INCDIR += ../ConfigPhase

INCLUDEPATH  += ../Minitor
QMAKE_INCDIR += ../Minitor

INCLUDEPATH  += ../SweepShelf
QMAKE_INCDIR += ../SweepShelf


INCLUDEPATH  += ../TRWaveControl
QMAKE_INCDIR += ../TRWaveControl

QMAKE_LIBDIR += ../lib/msc
QMAKE_LIBDIR += ../lib

INCLUDEPATH  += ../INCLUDE
QMAKE_LIBDIR += ../bin
LIBS += licV.lib

DEFINES    += QWT_DLL

CONFIG(debug, debug|release) {
    LIBS += qwtd.lib
    LIBS += RadarWndd.lib
    LIBS += HDA.lib
    LIBS += SweepShelf.lib
    LIBS += libxl.lib
    LIBS += Calibration.lib
    LIBS += Minitor.lib
    LIBS += TRWaveControl.lib
    LIBS += ConfigPhase.lib
} else {
    LIBS += qwt.lib
    LIBS += RadarWnd.lib
    LIBS += HDA.lib
    LIBS += SweepShelf.lib
    LIBS += libxl.lib
    LIBS += Calibration.lib
    LIBS += Minitor.lib
    LIBS += TRWaveControl.lib
    LIBS += ConfigPhase.lib
}


CONFIG(debug, debug|release) {
    LIBS += visa32.lib
    LIBS += agvisa32.lib
    LIBS += agvisaext.lib
    LIBS += visaext.lib
} else {
    LIBS += visa32.lib
    LIBS += agvisa32.lib
    LIBS += agvisaext.lib
    LIBS += visaext.lib
}


UI_DIR = ../../temp/ui/SPCS
OBJECTS_DIR = ../../temp/obj/SPCS
MOC_DIR = ../../temp/moc/SPCS


QMAKE_CXXFLAGS += -wd4100  -wd4005 -wd4503
QMAKE_CXXFLAGS += -wd4996  -wd4522 -wd4189

contains(QWT_CONFIG, QwtSvg) {
    QT += svg
}
else {

    DEFINES += QWT_NO_SVG
}


SOURCES += main.cpp\
        mainwindow.cpp \
    testbackgnd.cpp \
    rightpane.cpp \
    leftpane.cpp \
    workbench.cpp \
    outputview.cpp \
    controlpane.cpp \
    testresult.cpp \
    testunitscene.cpp \
    testunit.cpp \
    actions.cpp \
    testunitline.cpp \
    radarface.cpp \
    statusoutput.cpp \
    statusbar.cpp \
    testimpl.cpp \
    vnaaction.cpp \
    electronicswitch.cpp \
    multiswitch.cpp \
    m_testinitdlg.cpp \
    m_setpnadlg.cpp \
    m_setfreqdlg.cpp \
    m_selectgallerydlg.cpp \
    m_plottestview.cpp \
    m_parsecurvedata.cpp \
    m_dampingdlg.cpp \
    m_cvts_plot_curve.cpp \
    m_cvts_plot.cpp \
    m_calmanager.cpp \
    help.cpp \
    numvalue_convert.cpp \
    radaranaly.cpp \
    datadapter_s.cpp \
    m_calibrationmangerdlg.cpp \
    taskimpl.cpp \
    delaytask.cpp\
    view.cpp\
    toolbar.cpp\
    vnadapter.cpp \
    paramsetmanager.cpp \
    env_config.cpp \
    sweepshelfact.cpp \
    files.cpp \
    projectmanager.cpp \
    troublecheck.cpp \
    eleswitch.cpp \
    buziwidget.cpp \
    parseresultdata.cpp \
    wave_control.cpp \
    taskcenter_607.cpp \
    BackHandle.cpp \
    datamanage.cpp \
    sweepshelfcontrol.cpp \
    controlwave.cpp\
    h_TestOutArea.cpp \
    h_MagnPhaseGraphics.cpp \
    controlelecswitch.cpp \
    twoshorttoid.cpp \
    m_setdev.cpp \
    m_set_times.cpp \
    searchunit.cpp \
    tarray.cpp \
    m_setpulse.cpp \
    configerexcel.cpp \
    handlecontrol.cpp \
    tools.cpp \
    cparsefile.cpp \
    stablecontrolpane.cpp \
    m_stabletools.cpp \
    stableplotview.cpp \
    caldiffercontrolpane.cpp \
    m_caldiffer_tools.cpp \
    m_toolsthread.cpp \
    combinetools.cpp \
    rs_vnadapter.cpp \
    afgadapter.cpp \
    m_cfg_status_dlg.cpp \
    resultcontrolpane.cpp \
    m_cfg_status_thread.cpp \
    powerate.cpp \
    portchangethread.cpp \
    portchange.cpp \
    H_probe_test.cpp \
    probe_test.cpp


HEADERS  += mainwindow.h \
    testbackgnd.h \
    rightpane.h \
    leftpane.h \
    workbench.h \
    outputview.h \
    controlpane.h \
    testresult.h \
    testunitscene.h \
    testunit.h \
    actions.h \
    testunitline.h \
    radarface.h \
    statusoutput.h \
    statusbar.h \
    testimpl.h \
    vnaaction.h \
    delaytask.h \
    electronicswitch.h \
    multiswitch.h \
    m_testinitdlg.h \
    m_setpnadlg.h \
    m_setfreqdlg.h \
    m_selectgallerydlg.h \
    m_plottestview.h \
    m_parsecurvedata.h \
    m_dampingdlg.h \
    m_cvts_plot_curve.h \
    m_cvts_plot.h \
    m_calmanager.h \
    help.h \
    numvalue_convert.h \
    radaranaly.h \
    datadapter_s.h \
    m_calibrationmangerdlg.h \
    taskimpl.h \
    view.h\
    toolbar.h\
    vnadapter.h \
    paramsetmanager.h \
    env_config.h \
    sweepshelfact.h \
    files.h \
    projectmanager.h \
    troublecheck.h \
    eleswitch.h \
    buziwidget.h \
    parseresultdata.h \
    wave_control.h \
    taskcenter_607.h \
    BackHandle.h \
    datamanage.h \
    sweepshelfcontrol.h \
    controlwave.h\
    h_TestOutArea.h \
    h_MagnPhaseGraphics.h \
    controlelecswitch.h \
    twoshorttoid.h \
    m_setdev.h \
    m_set_times.h \
    searchunit.h \
    tarray.h \
    m_setpulse.h \
    configerexcel.h \
    handlecontrol.h \
    tools.h \
    cparsefile.h \
    stablecontrolpane.h \
    m_stabletools.h \
    stableplotview.h \
    caldiffercontrolpane.h \
    m_caldiffer_tools.h \
    m_toolsthread.h \
    combinetools.h \
    rs_vnadapter.h \
    afgadapter.h \
    m_cfg_status_dlg.h \
    resultcontrolpane.h \
    m_cfg_status_thread.h \
    powerate.h \
    portchangethread.h \
    portchange.h \
    H_probe_test.h \
    probe_test.h


FORMS += \
    m_testinitdlg.ui \
    m_setpnadlg.ui \
    m_setfreqdlg.ui \
    m_dampingdlg.ui \
    m_calibrationmangerdlg.ui\
    m_selectgallerydlg.ui \
    sweepshelfcontrol.ui \
    controlwave.ui \
    controlelecswitch.ui \
    m_setdev.ui \
    m_set_times.ui \
    searchunit.ui \
    m_setpulse.ui \
    handlecontrol.ui \
    stablecontrolpane.ui \
    caldiffercontrolpane.ui \
    combinetools.ui \
    m_cfg_status_dlg.ui \
    resultcontrolpane.ui \
    portchange.ui \
    H_probe_test.ui
