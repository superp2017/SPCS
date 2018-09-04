#include "eleswitch.h"
#include "teleswitch.h"

EleSwitch::EleSwitch(QObject *parent) :
    QObject(parent)
{
    reset();
}

EleSwitch::~EleSwitch()
{

}

void EleSwitch::reset()
{
    m_isopen = false;
 //   set_status(false);
}

bool &EleSwitch::get_status()
{
    return m_isopen;
}

void EleSwitch::set_status(bool isopen)
{
    if(isopen)
        open_all();
    else
        close_all();
}


void EleSwitch::open_all()
{
    m_isopen = true;
    TEleSwitch::instance()->turn_on_all();
}

void EleSwitch::close_all()
{
    m_isopen = false;
    TEleSwitch::instance()->turn_off_all();
}
