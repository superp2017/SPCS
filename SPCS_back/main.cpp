#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "delaytask.h"
#include "env_config.h"
#include "projectmanager.h"
#include "vnadapter.h"
#include "taskcenter_607.h"
#include "twoshorttoid.h"
#include "m_set_times.h"
#include <QSplashScreen>
#include "licv.h"
#include "pci_cardcent.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //    if(!LicV::validate("SPCS_607",".\\license\\SPCS_607.lic"))
    //        return a.exit(-1);
    ////////////////////////////
    /// \brief splash
    ///  启 动 图 片
    QSplashScreen  *splash  = new QSplashScreen();
    QString pic =QApplication::applicationDirPath() + "//" +"image/welcome.png";
    splash->setPixmap(QPixmap(pic));
    splash->show();
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignBottom ;
    splash->showMessage(QObject::tr("Set up the Main Window.."),topRight,Qt::white);
    ::Sleep(2000);
    ///////////////////////////////////


    MainWindow w;
    w.setFixedHeight(a.desktop()->availableGeometry().height()-20);
    w.setFixedWidth(a.desktop()->availableGeometry().width());
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint);
    MainWindow::instance(&w);
    /////////////////////////////
    splash->showMessage(QObject::tr("Load modules.."),topRight,Qt::white);
    ::Sleep(200);
    splash->showMessage(QObject::tr("Load Array Face.."),topRight,Qt::white);
    ::Sleep(200);
    splash->showMessage(QObject::tr("Load WorkSpace.."),topRight,Qt::white);
    ::Sleep(200);
    splash->showMessage(QObject::tr("Load Result model.."),topRight,Qt::white);
    ::Sleep(200);
    splash->showMessage(QObject::tr("Load Arrat Analy.."),topRight,Qt::white);
    ::Sleep(200);
    /////////////////////////////
    w.showMaximized();
    w.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));



    //////延时工作
    DelayTask::instance()->do_delay_task();
    ///////////2013/11/25  mp  加载默认的项目
    ProjectManager::instance()->set_default_info();
    //////////////////
    splash->showMessage(QObject::tr("Load Delay task.."),topRight,Qt::white);
    ::Sleep(100);
    splash->showMessage(QObject::tr("Load Completed.."),topRight,Qt::white);
    splash->finish(&w);
    delete splash;
    /////////////////

    PCI_CardCent::instance()->turn_on(17);
    return a.exec();
}
