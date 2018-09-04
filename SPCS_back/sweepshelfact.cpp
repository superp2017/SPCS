#include "sweepshelfact.h"
#include "_global.h"
#include "mainwindow.h"
#include "sweepshelf.h"

SweepShelfAct::SweepShelfAct(QObject *parent) :
    Actions(parent)
{

}

void SweepShelfAct::register_actions()
{
    QString     Shelf = CVTS::GBKToUnicode::toUnicode("&É¨Ãè¼Ü");
    QString     Reset = CVTS::GBKToUnicode::toUnicode("&¸´Î»");
    QString     control = CVTS::GBKToUnicode::toUnicode("&É¨Ãè¼Ü¿ØÖÆ");

    m_reset_act= new QAction(Reset, this);
    m_reset_act->setShortcut(QKeySequence(tr("Ctrl+R")));

    m_control_act = new QAction(QIcon("./image/sweepshelf.png"),control, this);
    m_control_act->setShortcut(QKeySequence(tr("Ctrl+L")));


    MainWindow::instance()->register_menu(Shelf, m_reset_act);
    MainWindow::instance()->register_menu(Shelf, m_control_act);


    toolbar = new ToolBar(Shelf);

    MainWindow::instance()->register_ToolBar(Shelf,m_control_act,toolbar);


    connect(m_reset_act,SIGNAL(triggered()),this,SLOT(P_reset()));
    connect(m_control_act,SIGNAL(triggered()),this,SLOT(p_control()));
    connect(toolbar,SIGNAL(P_show(QString,bool)),this,SIGNAL(P_show(QString,bool)));

}


void SweepShelfAct::p_control()
{
    m_control.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    m_control.showNormal();
}


void SweepShelfAct::P_reset()
{
    SweepShelf::instance()->reset();
}
