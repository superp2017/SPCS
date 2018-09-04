#include "wave_control.h"
#include "_global.h"
#include "mainwindow.h"
#include "controlwave.h"


Wave_Control::Wave_Control(QObject *parent) :
    Actions(parent)
{
}
void Wave_Control::register_actions()
{
    QString SWave = CVTS::GBKToUnicode::toUnicode("&波控分机");
    QString S_manual_operation_act = CVTS::GBKToUnicode::toUnicode("&手动配置");

    m_manual_operation_act = new QAction(QIcon("./image/wavecontrol.bmp"),S_manual_operation_act, this);
    m_manual_operation_act->setShortcut(QKeySequence(tr("Ctrl+L")));

    MainWindow::instance()->register_menu(SWave, m_manual_operation_act);

    toolbar = new ToolBar(SWave);

    MainWindow::instance()->register_ToolBar(SWave,m_manual_operation_act,toolbar);

    connect(m_manual_operation_act,SIGNAL(triggered()),this,SLOT(manual_operation()));
    connect(toolbar,SIGNAL(P_show(QString,bool)),this,SIGNAL(P_show(QString,bool)));

}

void Wave_Control::manual_operation()
{
    ControlWave::instance()->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    ControlWave::instance()->show();
}
