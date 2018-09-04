#ifndef REBPCI2323_H
#define REBPCI2323_H
#include "Windows.h"
#include "PCI2323.h"
#include <stdio.h>
#include "hda_global.h"

class HDASHARED_EXPORT  RebPCI2323
{      
public:
    RebPCI2323();
    virtual  ~RebPCI2323();
public:
    void turn_on(int n);
    void turn_off(int n);
    void setDeviceDO();
    void turn_on_all();
    void turn_off_all();
    void init(int id =0);
    void destory_device();
    int id();
private:
    void reset();
    void Creat_Device();
private:
    HANDLE              m_handle;
    int                 m_devid;
    BYTE                m_DO[16];
};

#endif // REBPCI2323_H
