#include "portchangethread.h"
#include "portchange.h"

PortChangeThread::PortChangeThread()
{
}


void PortChangeThread::T_test()
{
    start();
}


void PortChangeThread::run()
{
    PortChange::instance()->testS11();
    emit testend();
}
