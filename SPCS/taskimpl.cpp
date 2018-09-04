#include "taskimpl.h"
#include "taskcenter_607.h"
#include "mainwindow.h"
#include "tmonitor.h"
#include "buziwidget.h"
#include "outputview.h"
#include "projectmanager.h"
#include "BackHandle.h"
#include "m_set_times.h"
#include "m_testinitdlg.h"
#include "m_setdev.h"
#include "m_setfreqdlg.h"
#include "radarface.h"
#include "m_setpulse.h"
#include  "tarray.h"
#include "projectmanager.h"
#include "controlpane.h"

TaskImpl::TaskImpl(QThread *parent) :
    QThread(parent)
{
    reset();
}

TaskImpl::~TaskImpl()
{

}

TaskImpl *TaskImpl::instance()
{
    static TaskImpl *s_impl = new TaskImpl();
    return s_impl;
}

void TaskImpl::destroy()
{
    delete instance();
}

void TaskImpl::reset()
{
    m_paused = false;
    m_isconnect = false;
}

bool TaskImpl::is_paused()
{
    return m_paused;
}

void TaskImpl::begin()
{
    TEST_TYPE  type;
    WORK_STATUS status;
    QString m_cfg_table;
    M_SetDev::instance();
    M_SetFreqdlg::instance();
    M_SetPulse::instance();
    M_TestInitDlg::instance()->get_param(type,status,m_cfg_table);
    TaskCenter_607::instance()->init_cfg_table(m_cfg_table);
    M_Set_Times::instance()->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    TaskCenter_607::instance()->init_test_type(type,status);
    if(M_Set_Times::instance()->exec() == 123)
    {
        connect(this, SIGNAL(trigger_monitor()), \
                this, SLOT(show_monitor()), Qt::QueuedConnection);

        if(!m_isconnect)
        {
            connect(TaskCenter_607::instance(),SIGNAL(Handledata()),BackHandle::instance(),\
                    SLOT(HandleData()),Qt::QueuedConnection);

            connect(TaskCenter_607::instance(),SIGNAL(Handledata()),ControlPane::instance(),\
                    SLOT(TestEnd_mode()),Qt::QueuedConnection);


            //            connect(this,SIGNAL(test_stop()),this,SLOT(stop()),\
            //                    Qt::QueuedConnection);

        }

        connect(BuziWidget::instance(),SIGNAL(show_array()),this,SLOT(show_array()),\
                Qt::QueuedConnection);
        emit Panebeign();
        ProjectManager::instance()->on_save();
        start();
    }
}

void TaskImpl::stop()
{
    qDebug()<<"stop......................................";
    this->terminate();
    TaskCenter_607::instance()->clear_buf();
}

void TaskImpl::pause(bool is_pause)
{
    m_paused = true;
}


void TaskImpl::continue_run()
{
    m_paused = false;
}

void TaskImpl::show_monitor()
{
    if(!m_isconnect)
    {
        connect(TaskCenter_607::instance(),SIGNAL(WAVE_CONNECT_FAILED()),this,SLOT(wave_connect_failed()),Qt::QueuedConnection);
        connect(TaskCenter_607::instance(),SIGNAL(VNA_CONNECT_FAILED()),this,SLOT(VNA_connect_failed()),Qt::QueuedConnection);
        connect(TaskCenter_607::instance(),SIGNAL(Serialport_connect_failed()),this,SLOT(Serialport_connect_failed()),Qt::QueuedConnection);

        connect(TMonitor::instance(),SIGNAL(StopTest()),ControlPane::instance(),SLOT(inner_stop()),Qt::QueuedConnection);
        connect(ControlPane::instance(),SIGNAL(stoptest()),TMonitor::instance(),SLOT(back()),Qt::QueuedConnection);
        connect(ControlPane::instance(),SIGNAL(stoptest()),TaskCenter_607::instance(),SLOT(stop_test()),Qt::QueuedConnection);
        connect(TMonitor::instance(),SIGNAL(ShowMainWindow()),MainWindow::instance(),SLOT(showMaximized()),Qt::QueuedConnection);
        connect(TaskCenter_607::instance(),SIGNAL(SHOW_CAL_STATUS()),this,SLOT(SHOW_CAL_STATUS()),Qt::QueuedConnection);

    }
    MainWindow::instance()->hide();
    TMonitor::instance()->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    TMonitor::instance()->showFullScreen();
    TMonitor::instance()->Set_up_widget(BuziWidget::instance());
    TMonitor::instance()->Set_down_widget(OutputView::instance());
    m_isconnect = true;
}

void TaskImpl::show_array()
{
    TArray::instance()->exec();
}

void TaskImpl::wave_connect_failed()
{
    QMessageBox mes;
    QString title = CVTS::GBKToUnicode::toUnicode("警告");
    QString text = CVTS::GBKToUnicode::toUnicode("波控连接失败!");
    mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    mes.setWindowTitle(title);
    mes.setText(text);
    mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    mes.exec();
}

void TaskImpl::VNA_connect_failed()
{
    QMessageBox mes;
    QString title = CVTS::GBKToUnicode::toUnicode("警告");
    QString text = CVTS::GBKToUnicode::toUnicode("矢网连接失败!");
    mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    mes.setWindowTitle(title);
    mes.setText(text);
    mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    mes.exec();
}


void TaskImpl::Serialport_connect_failed()
{
    QMessageBox mes;
    QString title = CVTS::GBKToUnicode::toUnicode("警告");
    QString text = CVTS::GBKToUnicode::toUnicode("串口COM4打开失败!");
    mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    mes.setWindowTitle(title);
    mes.setText(text);
    mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    mes.exec();
}


void TaskImpl::SHOW_CAL_STATUS()
{
    m_cfg_status_dlg::instance()->init_data(TaskCenter_607::instance()->get_org_data().t_cfg_magnphase,\
                                            TaskCenter_607::instance()->get_org_data().t_cfg_mp_1,\
                                            TaskCenter_607::instance()->get_freqs(),\
                                            TaskCenter_607::instance()->get_delt_mag(),\
                                            TaskCenter_607::instance()->get_base_add_db(),\
                                            TaskCenter_607::instance()->get_org_base_mp(),\
                                            TaskCenter_607::instance()->get_id());

    if( m_cfg_status_dlg::instance()->exec() == 0)
    {
        TaskCenter_607::instance()->update_org_cal( m_cfg_status_dlg::instance()->get_org_cal());
        TaskCenter_607::instance()->BASE_MP(  m_cfg_status_dlg::instance()->get_base_mp());
    }
}


void TaskImpl::run()
{
    emit  trigger_monitor();
    ::Sleep(1000);
    TaskCenter_607::instance()->begin_test();
}
