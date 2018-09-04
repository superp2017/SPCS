#include "ic_controlcard.h"
#include <QSettings>
#include "test_comm.h"
#include "_global.h"
#include <QDebug>
IC_ControlCard::IC_ControlCard(QObject *parent) :
    QObject(parent)
{
    m_is_init = false;
}

void IC_ControlCard::init()
{
    QSettings sets(IC_CARD_CONFIG_PATH, QSettings::IniFormat);
    sets.beginGroup("IC");

    if(!controller_init(sets.value("ip").toString().toLocal8Bit().data(),\
                        sets.value("port").toString().toLocal8Bit().data()))
    {
        qDebug()<<"controller_init failed";
        m_is_init = false;
        return ;
    }else
        qDebug()<<"controller_init OK";
    sets.endGroup();
    m_is_init = true;
}

void IC_ControlCard::close_dev()
{
  if(m_is_init)
        controller_close();
}

void IC_ControlCard::turn_on_all()
{
 if(m_is_init)
        controller_set_all_channels(true);
}

void IC_ControlCard::turn_off_all()
{
    if(m_is_init)
        controller_set_all_channels(false);
}


void IC_ControlCard::turn_on(int pin)
{
    if(m_is_init)
        controller_set_channel(pin,true);
}

void IC_ControlCard::turn_off(int pin)
{
    if(m_is_init)
        controller_set_channel(pin,false);
}

