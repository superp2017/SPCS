#include "electronicswitch.h"
#include "_global.h"
#include "mainwindow.h"
#include "eleswitch.h"


ElectronicSwitch::ElectronicSwitch(QObject *parent)
    :Actions(parent)
{
}

void ElectronicSwitch::register_actions()
{
    QString ElecW = CVTS::GBKToUnicode::toUnicode("&电子开关");
    QString CloseAll = CVTS::GBKToUnicode::toUnicode("&关闭所有");

    QString control= CVTS::GBKToUnicode::toUnicode("&控制");


    m_close_all_act = new QAction(CloseAll, this);
    m_close_all_act->setShortcut(QKeySequence(tr("Ctrl+A")));

    m_control_act= new QAction(QIcon("./image/elecswitch.png"),control, this);
    m_control_act->setShortcut(QKeySequence(tr("Ctrl+Shift +C ")));

    MainWindow::instance()->register_menu(ElecW, m_close_all_act);
    MainWindow::instance()->insertSeparator(ElecW, m_control_act);
    MainWindow::instance()->register_menu(ElecW, m_control_act);

    toolbar = new ToolBar(ElecW);

    MainWindow::instance()->register_ToolBar(ElecW,m_control_act,toolbar);

    connect(m_close_all_act,SIGNAL(triggered()),EleSwitch::instance(),SLOT(close_all()));

    connect(toolbar,SIGNAL(P_show(QString,bool)),this,SIGNAL(P_show(QString,bool)));
    connect(m_control_act,SIGNAL(triggered()),this,SLOT(settings()));

}

void ElectronicSwitch::settings()
{
    ControlElecSwitch::instance()->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    ControlElecSwitch::instance()->showNormal();
}

