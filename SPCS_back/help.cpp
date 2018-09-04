#include "help.h"
#include "_global.h"
#include "mainwindow.h"

Help::Help(QObject *parent) :
    Actions(parent)
{

}

void Help::register_actions()
{
    QString SHelp = CVTS::GBKToUnicode::toUnicode("&帮助");
    QString SVersion = CVTS::GBKToUnicode::toUnicode("&版权声明");
    QString SUMannual = CVTS::GBKToUnicode::toUnicode("&用户手册");
    QString INTALL = CVTS::GBKToUnicode::toUnicode("&安装手册");

    m_version_act = new QAction(SVersion, this);
    m_version_act->setShortcut(QKeySequence(tr("Ctrl+V")));
    m_user_mannul_act = new QAction(SUMannual, this);
    m_user_mannul_act->setShortcut(QKeySequence(tr("Ctrl+X")));

    m_install_mannul = new QAction(INTALL, this);

    MainWindow::instance()->register_menu(SHelp, m_version_act);
    MainWindow::instance()->register_menu(SHelp, m_user_mannul_act);
    MainWindow::instance()->register_menu(SHelp, m_install_mannul);

    connect(m_version_act,SIGNAL(triggered()),this,SLOT(on_Version()));
    connect(m_user_mannul_act,SIGNAL(triggered()),this,SLOT(on_UserMannual()));
    connect(m_install_mannul,SIGNAL(triggered()),this,SLOT(on_install()));

}

void Help::on_Version()
{
    QString title = CVTS::GBKToUnicode::toUnicode("Version");
    QMessageBox  mes;
    mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    mes.setParent(NULL);
    mes.setText(QString("Copyright Copyright (C), 2007-2014, Hollywell Electronic System Co."));
    mes.setWindowTitle(title);
     mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    mes.exec();
}

void Help::on_UserMannual()
{
    system((QString("")+"start " +QCoreApplication::applicationDirPath() + "/Help/UserManual_V1.0.pdf").toLocal8Bit().data());
}

void Help::on_install()
{
     system((QString("")+"start " +QCoreApplication::applicationDirPath() + "/Help/InstallManual_V1.0.pdf").toLocal8Bit().data());
}
