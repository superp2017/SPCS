#include "tools.h"
#include "mainwindow.h"
#include "m_calibrationmangerdlg.h"
#include "portchange.h"

Tools::Tools(QObject *parent) :
    Actions(parent)
{
}

void Tools::register_actions()
{
    QString Control = CVTS::GBKToUnicode::toUnicode("&工具");

    QString  HAND   = CVTS::GBKToUnicode::toUnicode("&手动控制");
    QString  CAL    = CVTS::GBKToUnicode::toUnicode("&校准库管理");

    QString  Stable = CVTS::GBKToUnicode::toUnicode("&稳定性检验");

    QString  DIFFER = CVTS::GBKToUnicode::toUnicode("&数据比较");

    QString  COMBINE = CVTS::GBKToUnicode::toUnicode("&数据合并");

    QString  port = CVTS::GBKToUnicode::toUnicode("&通道转换");

    m_control = new QAction(/*QIcon(QApplication::applicationDirPath() +"./image/new.png"),*/HAND, this);
    m_control->setShortcut(QKeySequence(tr("Ctrl+P")));

    m_cal_libs = new QAction(/*QIcon(QApplication::applicationDirPath() +"./image/new.png"),*/CAL, this);
    m_cal_libs->setShortcut(QKeySequence(tr("Ctrl+L")));

    m_stable_tools = new QAction(/*QIcon(QApplication::applicationDirPath() +"./image/new.png"),*/Stable, this);
    m_stable_tools->setShortcut(QKeySequence(tr("Ctrl+S")));

    m_caldiffer_tools = new QAction(/*QIcon(QApplication::applicationDirPath() +"./image/new.png"),*/DIFFER, this);
    m_caldiffer_tools->setShortcut(QKeySequence(tr("Ctrl+D")));

    m_combine_tools = new QAction(/*QIcon(QApplication::applicationDirPath() +"./image/new.png"),*/COMBINE, this);
    m_combine_tools->setShortcut(QKeySequence(tr("Ctrl+B")));

    m_portchange_tools= new QAction(/*QIcon(QApplication::applicationDirPath() +"./image/new.png"),*/port, this);


    MainWindow::instance()->register_menu(Control, m_control);
    MainWindow::instance()->register_menu(Control, m_cal_libs);
    MainWindow::instance()->register_menu(Control, m_stable_tools);
    MainWindow::instance()->register_menu(Control, m_caldiffer_tools);
    MainWindow::instance()->register_menu(Control, m_combine_tools);
    MainWindow::instance()->register_menu(Control, m_portchange_tools);

    toolbar = new ToolBar(Control);

    MainWindow::instance()->register_ToolBar(Control, m_control,toolbar);
    MainWindow::instance()->register_ToolBar(Control, m_cal_libs,toolbar);
    MainWindow::instance()->register_ToolBar(Control, m_stable_tools,toolbar);
    MainWindow::instance()->register_ToolBar(Control, m_caldiffer_tools,toolbar);
    MainWindow::instance()->register_ToolBar(Control, m_combine_tools,toolbar);
    MainWindow::instance()->register_ToolBar(Control, m_portchange_tools,toolbar);


    connect(m_control,SIGNAL(triggered()),this,SLOT(on_coltrol()));
    connect(m_cal_libs,SIGNAL(triggered()),this,SLOT(on_cal()));
    connect(m_stable_tools,SIGNAL(triggered()),this,SLOT(on_stable()));
    connect(m_caldiffer_tools,SIGNAL(triggered()),this,SLOT(on_differ()));
    connect(m_combine_tools,SIGNAL(triggered()),this,SLOT(on_combine()));
    connect(m_portchange_tools,SIGNAL(triggered()),this,SLOT(portchange()));

    connect(toolbar,SIGNAL(P_show(QString,bool)),this,SIGNAL(P_show(QString,bool)));

}

void Tools::on_coltrol()
{
    HandleControl::instance()->showNormal();
}

void Tools::on_cal()
{
    M_CalibrationMangerdlg::instance()->exec();
}

void Tools::on_stable()
{
    m_stabletools.showMaximized();
}

void Tools::on_differ()
{
    m_differ_tools.showMaximized();
}

void Tools::on_combine()
{
    m_combine.showNormal();
}

void Tools::portchange()
{
    PortChange::instance()->showMaximized();
}
