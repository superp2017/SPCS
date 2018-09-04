#include "actions.h"



Actions::Actions(QObject *parent) :
    QObject(parent)
{
   connect(DelayTask::instance(), SIGNAL(tigger_delay_task()), this, SLOT(register_actions()));
}
