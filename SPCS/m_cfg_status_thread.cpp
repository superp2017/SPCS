#include "m_cfg_status_thread.h"
#include "m_cfg_status_dlg.h"
#include <QDebug>

m_CFG_STATUS_THread::m_CFG_STATUS_THread(QObject *parent) :
    QThread(parent)
{
}

void m_CFG_STATUS_THread::CALC(bool pismagn)
{
    m_ismagn = pismagn;
    start();

}


void m_CFG_STATUS_THread::run()
{
    if(m_ismagn)
        m_cfg_status_dlg::instance()->calc_magn();
    else
        m_cfg_status_dlg::instance()->calc_phase();
}
