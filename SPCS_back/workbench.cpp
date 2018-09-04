#include "workbench.h"
#include "radarface.h"
#include "testresult.h"
#include "m_testinitdlg.h"
#include "m_dampingdlg.h"
#include "m_setfreqdlg.h"
#include "radaranaly.h"
#include "mainwindow.h"
#include "delaytask.h"
#include "troublecheck.h"
#include "m_setdev.h"
#include "tarray.h"


WorkBench::WorkBench(QWidget *parent) :
    QWidget(parent)
{
    m_widget = 0;
    connect(TestResult::instance(),SIGNAL(on_show_normal()),this,SLOT(show_result_normal()));
    connect(TestResult::instance(),SIGNAL(on_fullscreen()),this,SLOT(show_result_fullscreen()));
    connect(this,SIGNAL(change_btn_full()),TestResult::instance(),SIGNAL(change_btn_full()));
    connect(this,SIGNAL(change_btn_normal()),TestResult::instance(),SIGNAL(change_btn_normal()));
    connect(DelayTask::instance(),SIGNAL(tigger_delay_task()),SLOT(init_widget()));
}

void WorkBench::show_workarea(QWidget *widget)
{
    if(widget == 0) return ;
    if(widget == m_widget)
    {
        m_widget->showNormal();
        m_widget->setFixedSize(rect().width(), rect().height());
        return ;
    }
    if(m_widget != 0) m_widget->hide();
    m_widget = widget;
    m_widget->setParent(this);
    m_widget->setGeometry(rect());
    m_widget->showNormal();
}

void WorkBench::show_result_fullscreen()
{
    if(m_widget == TestResult::instance())
    {
        TestResult::instance()->setParent(0);
        TestResult::instance()->showFullScreen();
        TestResult::instance()->setFixedSize(QApplication::desktop()->width(),QApplication::desktop()->height());
        TestResult::instance()->setFocus();
        emit change_btn_normal();
    }
}

void WorkBench::show_result_normal()
{
    TestResult::instance()->setParent(this);
    show_workarea(TestResult::instance());
    this->setFocus();
    emit change_btn_full();
}

void WorkBench::init_widget()
{
    RadarFace::instance()->init(rect());
    RadarAnaly::instance()->init(rect());
    M_TestInitDlg::instance()->init();
    M_Dampingdlg::instance()->init();
    TroubleCheck::instance()->init(rect());
    TArray::instance()->init(rect());
}

void WorkBench::trouble_check()
{
    show_workarea(TroubleCheck::instance());
}

void WorkBench::show_radar_face()
{
    show_workarea(RadarFace::instance());
}

void WorkBench::show_result_area()
{   
    show_workarea(TestResult::instance());
}

void WorkBench::show_radar_analy()
{   
    show_workarea(RadarAnaly::instance());
}

void WorkBench::show_init_dlg()
{   
    M_TestInitDlg::instance()->exec();
}

void WorkBench::show_dev()
{   
    M_SetDev::instance()->showNormal();
}

void WorkBench::show_setfreq_dlg()
{   
    M_SetFreqdlg::instance()->exec();
}

void WorkBench::keyPressEvent(QKeyEvent *e)
{
    if(Qt::ControlModifier == e->modifiers() && Qt::Key_F == e->key())
    {
        show_result_fullscreen();
    }else if(Qt::ControlModifier == e->modifiers() && Qt::Key_Q == e->key())
    {
        show_result_normal();
    }
}
