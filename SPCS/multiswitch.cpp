#include "multiswitch.h"
#include "_global.h"
#include "mainwindow.h"
#include "m_selectgallerydlg.h"

MultiSwitch::MultiSwitch(QObject *parent) :
    Actions(parent)
{
}

void MultiSwitch::register_actions()
{
    init_dlg();
    QString     MultiS = CVTS::GBKToUnicode::toUnicode("&���ؾ���");
    QString     Channel = CVTS::GBKToUnicode::toUnicode("&ͨ��ѡ��");
    QString     CloseAll = CVTS::GBKToUnicode::toUnicode("&ȫ���ر�");

    m_channel_act = new QAction(QIcon("./image/multiswitch.png"),Channel, this);
    m_channel_act->setShortcut(QKeySequence(tr("Ctrl+U")));

    m_close_all_act = new QAction(CloseAll, this);
    m_close_all_act->setShortcut(QKeySequence(tr("Ctrl+K")));

    MainWindow::instance()->register_menu(MultiS, m_channel_act);
    MainWindow::instance()->insertSeparator(MultiS, m_channel_act);
    MainWindow::instance()->register_menu(MultiS, m_close_all_act);

    toolbar = new ToolBar(MultiS);

    MainWindow::instance()->register_ToolBar(MultiS,m_channel_act,toolbar);
   // MainWindow::instance()->register_ToolBar(MultiS,m_close_all_act,toolbar);

    connect(m_channel_act,SIGNAL(triggered()),this,SLOT(show_SelectGallery_dlg()));
    connect(m_close_all_act,SIGNAL(triggered()),M_SelectGallerydlg::instance(),SLOT(close_all()));
    connect(toolbar,SIGNAL(P_show(QString,bool)),this,SIGNAL(P_show(QString,bool)));

}

void MultiSwitch::show_SelectGallery_dlg()
{
    M_SelectGallerydlg::instance()->showNormal();
}

void MultiSwitch::init_dlg()
{
    M_SelectGallerydlg::instance()->init();
}
