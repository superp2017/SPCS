#include "delaytask.h"

DelayTask::DelayTask(QObject *parent) :
    QObject(parent)
{
}

void DelayTask::do_delay_task()
{
    emit tigger_delay_task();
}
