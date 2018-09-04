#include "files.h"
#include "mainwindow.h"
#include "_global.h"
#include <QApplication>
#include "paramsetmanager.h"
#include "m_setfreqdlg.h"
#include "m_setpnadlg.h"
#include "eleswitch.h"
#include "m_selectgallerydlg.h"
#include "m_testinitdlg.h"
#include "m_dampingdlg.h"
#include "statusoutput.h"
#include "m_plottestview.h"
#include "testbackgnd.h"

Files::Files(QObject *parent) :
    Actions(parent)
{
}

void Files::register_actions()
{
    QString File = CVTS::GBKToUnicode::toUnicode("&文件");
    QString New = CVTS::GBKToUnicode::toUnicode("&新建");
    QString Open = CVTS::GBKToUnicode::toUnicode("&打开");
    QString Save = CVTS::GBKToUnicode::toUnicode("&保存");
    QString Exit = CVTS::GBKToUnicode::toUnicode("&退出");
    m_new_act = new QAction(QIcon(QApplication::applicationDirPath() +"./image/new.png"),New, this);
    m_new_act->setShortcut(QKeySequence::New);
    m_open_act = new QAction(QIcon(QApplication::applicationDirPath() +"./image/open.png"),Open, this);
    m_open_act->setShortcut(QKeySequence::Open);
    m_save_act = new QAction(QIcon(QApplication::applicationDirPath() +"./image/save.png"),Save, this);
    m_save_act->setShortcut(QKeySequence::Save);
    m_exit_act = new QAction(QIcon(QApplication::applicationDirPath() +"./image/exit.png"),Exit, this);
    m_exit_act->setShortcut(QKeySequence::Close);
    MainWindow::instance()->register_menu(File, m_new_act);
    MainWindow::instance()->register_menu(File, m_open_act);
    MainWindow::instance()->register_menu(File, m_save_act);
    MainWindow::instance()->insertSeparator(File, m_save_act);
    MainWindow::instance()->register_menu(File, m_exit_act);
    MainWindow::instance()->insertSeparator(File, m_exit_act);
    toolbar = new ToolBar(File);

    MainWindow::instance()->register_ToolBar(File, m_new_act,toolbar);
    MainWindow::instance()->register_ToolBar(File, m_open_act,toolbar);
    MainWindow::instance()->register_ToolBar(File, m_save_act,toolbar);
    MainWindow::instance()->register_ToolBar(File, m_exit_act,toolbar);

    connect(m_new_act,SIGNAL(triggered()),this,SLOT(on_new()));
    connect(m_open_act,SIGNAL(triggered()),this,SLOT(on_open()));
    connect(m_save_act,SIGNAL(triggered()),this,SLOT(on_save()));
    connect(m_exit_act,SIGNAL(triggered()),this,SLOT(on_exit()));
    connect(toolbar,SIGNAL(P_show(QString,bool)),this,SIGNAL(P_show(QString,bool)));
}

void Files::on_new()
{
    ///////////2013/11/25  mp
    /////////
    QString name = QFileDialog::getSaveFileName(MainWindow::instance(),tr("Creat Project"),\
                                                QApplication::applicationDirPath(), tr("Project Files (*.spcs)"));
    if(name.isEmpty()) return;
    ProjectManager::instance()->reset();
    ProjectManager::instance()->on_new(name);
    ControlPane::instance()->CreatNew_mode();
    on_save();
}

void Files::on_open()
{
    QString  p_path = QFileDialog::getOpenFileName(MainWindow::instance(),tr("Param File"),\
                                                   QApplication::applicationDirPath(), tr("Project Files (*.spcs)"));
    QFile ls_info(p_path);
    if(!p_path.isEmpty()&&ls_info.exists())
    {
        //////////////////////////
        ////////////2013/11/25  MP
        ProjectManager::instance()->on_open(p_path);
        ControlPane::instance()->open_mode();       
        on_save();
    }
}

void Files::on_save()
{
    ProjectManager::instance()->on_save();
}

void Files::on_exit()
{
    on_save();
    MainWindow::instance()->close_progress();
}

