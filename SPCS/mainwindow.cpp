#include "mainwindow.h"
#include "_global.h"
#include "statusbar.h"
#include "delaytask.h"
#include "testimpl.h"
#include "controlpane.h"
#include "outputview.h"
#include "radarface.h"
#include "workbench.h"
#include "testresult.h"
#include "taskimpl.h"
#include "m_testinitdlg.h"
#include "m_setfreqdlg.h"
#include "m_setpnadlg.h"
#include "m_dampingdlg.h"
#include "m_selectgallerydlg.h"
#include "radaranaly.h"
#include "m_plottestview.h"
#include "env_config.h"
#include "pci_cardcent.h"
#include "tattenuation.h"
#include "teleswitch.h"
#include "tswmatrixs.h"
#include "radarview.h"
#include "datadapter_s.h"
#include "m_calibrationmangerdlg.h"
#include "m_calmanager.h"
#include "m_parsecurvedata.h"
#include "paramsetmanager.h"
#include "projectmanager.h"
#include "statusoutput.h"
#include "testimpl.h"
#include "troublecheck.h"
#include "sweepshelf.h"
#include "eleswitch.h"
#include "taskcenter_607.h"
#include "buziwidget.h"
#include "calibrationmp.h"
#include "tmonitor.h"
#include "BackHandle.h"
#include "twoshorttoid.h"
#include "m_setdev.h"
#include "trwavecontrol.h"
#include "m_set_times.h"
#include "tarray.h"
#include "m_setpulse.h"
#include "controlwave.h"
#include "searchunit.h"
#include "m_toolsthread.h"
#include "handlecontrol.h"
#include "resultcontrolpane.h"
#include "controlelecswitch.h"
#include "portchange.h"
#include "portchangethread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QString ls_sheet = QString::fromUtf8("font: 12pt \"\346\245\267\344\275\223\";");
    m_quit = false;
    setCentralWidget(&m_bkgnd);
    setStatusBar(StatusBar::instance());

    statusBar()->showMessage(CVTS::GBKToUnicode::toUnicode("ÔËÐÐ×´Ì¬:"));
    menuBar()->setStyleSheet(ls_sheet);
    statusBar()->setStyleSheet(ls_sheet);
    TestImpl::instance();
}

MainWindow::~MainWindow()
{

}

void MainWindow::register_menu(const QString &menu, QAction *act)
{
    QString ls_sheet = QString::fromUtf8("font: 11pt \"\346\245\267\344\275\223\";");
    if(act == 0) return;
    if(m_menus[menu] == 0)
    {
        m_menus[menu] = menuBar()->addMenu(menu);
        m_menus[menu]->setStyleSheet(ls_sheet);
        m_menus[menu]->addAction(act);
    }else
    {
        m_menus[menu]->addAction(act);
    }

}

void MainWindow::register_menu(const QString &menu_pa, const QString &menu)
{
    QString ls_sheet = QString::fromUtf8("font: 11pt \"\346\245\267\344\275\223\";");

    if(menu.isEmpty()) return ;
    if(m_menus[menu_pa] == 0)
    {
        m_menus[menu_pa] = menuBar()->addMenu(menu_pa);
        m_menus[menu_pa]->setStyleSheet(ls_sheet);
        m_menus[menu] =  m_menus[menu_pa]->addMenu(menu);
    }else
    {
        m_menus[menu_pa]->addMenu(menu);
    }
}

void MainWindow::insertSeparator(const QString &menu,QAction *act)
{
    if(act == 0) return;
    if(m_menus[menu] != 0)
    {
        m_menus[menu]->insertSeparator(act);
    }
}

void MainWindow::register_ToolBar(QString name, QAction *act, QToolBar *toolbar)
{
    if(name.isEmpty()) return;
    if(m_toolbars.count(name) == 0)
    {
        addToolBar(toolbar);
        m_toolbars[name] = toolbar;
        m_toolbars[name]->addAction(act);
    }else
    {
        m_toolbars[name]->addAction(act);
    }
    m_toolbars[name]->hide();
}



void MainWindow::register_tool(QAction *act)
{
    if(act == 0) return ;
    if(m_tools.find(act) == m_tools.end())
    {
        m_tools.insert(act);
    }
}

void MainWindow::show_bar(QString p_name,bool checked)
{
    if(p_name.isEmpty()) return;
    if(m_toolbars.count(p_name) == 0)
        return;
    bool hide = m_toolbars[p_name]->isHidden();
    if(checked&&hide)
        m_toolbars[p_name]->show();
    else
    {
        if(hide) return;
        m_toolbars[p_name]->hide();
    }
}


void MainWindow::close_progress()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    // ProjectManager::instance()->on_save();
    // TaskCenter_607::instance()->donwpower();
   // ALl_destory();
}


void MainWindow::ALl_destory()
{
    m_quit = true;                          qDebug()<<"closeEvent";
    PortChange::destory();                  qDebug()<<"PortChange";
    PortChangeThread::destory();            qDebug()<<"PortChangeThread";
    ResultControlPane::destory();           qDebug()<<"ResultControlPane";
    TMonitor::destory();                    qDebug()<<"TMonitor";

    BackgroundPixmap::destroy();            qDebug()<<"BackgroundPixmap";
    M_CalibrationMangerdlg::destory();      qDebug()<<"M_CalibrationMangerdlg";
    M_CalManager::destory();                qDebug()<<"M_CalManager";
    M_ParseCurveData::destory();            qDebug()<<"M_ParseCurveData";
    ParamSetManager::destory();             qDebug()<<"ParamSetManager";
    ProjectManager::destory();              qDebug()<<"ProjectManager";
    StatusOutput::destory();                qDebug()<<"StatusOutput";
    TestImpl::destroy();                    qDebug()<<"TestImpl";
    SweepShelf::destory();                  qDebug()<<"SweepShelf";

    M_TestInitDlg::destroy();               qDebug()<<"M_TestInitDlg";
    M_SetFreqdlg::destory();                qDebug()<<"M_SetFreqdlg";
    M_Dampingdlg::destory();                qDebug()<<"M_Dampingdlg";
    M_SetPNAdlg::destory();                 qDebug()<<"M_SetPNAdlg";
    M_SelectGallerydlg::destory();          qDebug()<<"M_SelectGallerydlg";
    M_PlotTestView::destory();              qDebug()<<"M_PlotTestView";
    StatusBar::destroy();                   qDebug()<<"StatusBar";
    DelayTask::destroy();                   qDebug()<<"DelayTask";
    ControlPane::destroy();                 qDebug()<<"ControlPane";
    ControlWave::destory();                 qDebug()<<"ControlWave";
    OutputView::destroy();                  qDebug()<<"OutputView";
    RadarFace::destroy();                   qDebug()<<"RadarFace";
    RadarAnaly::destroy();                  qDebug()<<"RadarAnaly";
    TestResult::destroy();                  qDebug()<<"TestResult";
    WorkBench::destroy();                   qDebug()<<"WorkBench";
    TaskImpl::destroy();                    qDebug()<<"TaskImpl";
    ENV_config::destroy();                  qDebug()<<"ENV_config";
    //BuziWidget has been destroy by its parent class
    //BuziWidget::destroy();                qDebug()<<"BuziWidget";

    BackHandle::destory();                  qDebug()<<"BackHandle";
    //TaskCenter_607::destroy();              qDebug()<<"TaskCenter_607";
    TwoShortToId::destry();                 qDebug()<<"TwoShortToId";
    M_SetPulse::destory();                  qDebug()<<"M_SetPulse";
    M_Set_Times::destory();                 qDebug()<<"M_Set_Times";
    //  TRWaveControl::destory();               qDebug()<<"TRWaveControl";
    SearchUnit::destory();                  qDebug()<<"SearchUnit";
    M_SetDev::destory();                    qDebug()<<"M_SetDev";
    TArray::destroy();                      qDebug()<<"TArray";
     TroubleCheck::destory();                qDebug()<<"TroubleCheck";
    PCI_CardCent::destory();                qDebug()<<"PCI_CardCent";
    TAttenuation::destroy();                qDebug()<<"TAttenuation";
    TEleSwitch::destroy();                  qDebug()<<"TEleSwitch";
    TSWMatrixs::destroy();                  qDebug()<<"TSWMatrixs";
    EleSwitch::destory();                   qDebug()<<"EleSwitch";
    ControlElecSwitch::destory();           qDebug()<<"EleSwitch";
    HandleControl::destory();               qDebug()<<"HandleControl";
    qDebug()<<"close end";
}


