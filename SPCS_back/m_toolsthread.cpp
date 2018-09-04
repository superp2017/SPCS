#include "m_toolsthread.h"


#include "handlecontrol.h"

M_ToolsThread::M_ToolsThread()
{

}


void M_ToolsThread::run()
{
    if(m_iscal)
        HandleControl::instance()->cal_test();
    else
        HandleControl::instance()->stable_test();
    ::Sleep(100);
    emit testend();
}


void M_ToolsThread::T_test(bool iscal)
{
    if(this->isRunning()) return ;
    m_iscal = iscal;
   ::Sleep(100);
    start();
}

void M_ToolsThread::stop_test()
{
    this->terminate();
}

