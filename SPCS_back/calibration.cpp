#include "calibration.h"
#include "_global.h"
#include "mainwindow.h"
#include "m_calibrationmangerdlg.h"

Calibration::Calibration(QObject *parent) :
    Actions(parent)
{
}

void Calibration::register_actions()
{
    QString     Cali = CVTS::GBKToUnicode::toUnicode("&校准");
    QString     CalMgr = CVTS::GBKToUnicode::toUnicode("&校准库管理");
    QString     Magn = CVTS::GBKToUnicode::toUnicode("&幅值校准");
    QString     Phase = CVTS::GBKToUnicode::toUnicode("&相位校准");
    QString     MagnPhase = CVTS::GBKToUnicode::toUnicode("&福相校准");

    m_cal_manager_act = new QAction(CalMgr, this);
    m_cal_manager_act->setShortcut(QKeySequence(tr("Ctrl+G")));

    m_cal_magn_act = new QAction(Magn, this);
    m_cal_magn_act->setShortcut(QKeySequence(tr("Ctrl+M")));
    m_cal_phase_act = new QAction(Phase, this);
    m_cal_phase_act->setShortcut(QKeySequence(tr("Ctrl+H")));
    m_cal_magn_phase_act = new QAction(MagnPhase, this);
    m_cal_magn_phase_act->setShortcut(QKeySequence(tr("Ctrl+J")));

    MainWindow::instance()->register_menu(Cali, m_cal_manager_act);
    MainWindow::instance()->insertSeparator(Cali, m_cal_manager_act);
    MainWindow::instance()->register_menu(Cali, m_cal_magn_act);
    MainWindow::instance()->register_menu(Cali, m_cal_phase_act);
    MainWindow::instance()->register_menu(Cali, m_cal_magn_phase_act);
    toolbar = new   ToolBar(Cali);
    MainWindow::instance()->register_ToolBar(Cali,m_cal_manager_act, toolbar);
    MainWindow::instance()->register_ToolBar(Cali,m_cal_magn_act, toolbar);
    MainWindow::instance()->register_ToolBar(Cali,m_cal_phase_act, toolbar);
    MainWindow::instance()->register_ToolBar(Cali,m_cal_magn_phase_act, toolbar);

    connect(m_cal_manager_act,SIGNAL(triggered()),this,SLOT(show_cal_manger_dlg()));
    connect(m_cal_magn_act,SIGNAL(triggered()),this,SLOT(magn_manager()));
    connect(m_cal_phase_act,SIGNAL(triggered()),this,SLOT(phase_manager()));
    connect(m_cal_magn_phase_act,SIGNAL(triggered()),this,SLOT(magn_phase_manager()));
    connect(toolbar,SIGNAL(P_show(QString,bool)),this,SIGNAL(P_show(QString,bool)));
}

void Calibration::show_cal_manger_dlg()
{
//    M_CalibrationMangerdlg::instance()->init();
//    M_CalibrationMangerdlg::instance()->exec();
}

void Calibration::magn_manager()
{

}

void Calibration::phase_manager()
{

}

void Calibration::magn_phase_manager()
{

}
