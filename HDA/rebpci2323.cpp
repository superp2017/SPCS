#include "rebpci2323.h"

RebPCI2323::RebPCI2323()
{
    m_handle = 0;
    m_devid = -1;
}

RebPCI2323::~RebPCI2323()
{
    destory_device();
}

void RebPCI2323::destory_device()
{
    if(m_handle)PCI2323_ReleaseDevice(m_handle);
    m_handle = 0;
}

int RebPCI2323::id()
{
    return m_devid;
}


void RebPCI2323::init(int id)
{
    if(m_handle == 0)
    {
        m_devid = id;
        Creat_Device();
        reset();
    }
}


void RebPCI2323::Creat_Device()
{
    m_handle = PCI2323_CreateDevice(m_devid);
    if(m_handle == INVALID_HANDLE_VALUE)
    {
        qDebug()<<"PCI2323 Creat Device error ..id = "<<m_devid;
        destory_device();
    }
    else
        qDebug()<<"Creat Device,id =" << m_devid;
}


void RebPCI2323::reset()
{
    for(int i =0;i<16;++i)
    {
        m_DO[i] = 0;
    }
    setDeviceDO();
}

void RebPCI2323::turn_on(int n)
{
    if(n<0 || n > 15)return;
    for(int i=0; i<16; i++)
    {
        if(i == n)
        {
            *(m_DO+i) = 1;
        }
    }
}

void RebPCI2323::turn_off(int n)
{
    if(n<0 || n > 15)return;
    for(int i=0; i<16; i++)
    {
        if(i == n)
        {
            *(m_DO+i) = 0;
        }
    }
}

void RebPCI2323::setDeviceDO()
{
    PCI2323_SetDeviceDO(m_handle, m_DO);
}

void RebPCI2323::turn_on_all()
{
    for(int i=0; i<16; i++)
    {
        *(m_DO+i) = 1;
    }
    setDeviceDO();
}

void RebPCI2323::turn_off_all()
{
    for(int i=0; i<16; i++)
    {
        *(m_DO+i) = 0;
    }
    setDeviceDO();
}


