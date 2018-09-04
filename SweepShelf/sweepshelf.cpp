#include "sweepshelf.h"

SweepShelf::SweepShelf(QObject *parent):
    QObject(parent)
{
    m_isopen = false;
}


SweepShelf *SweepShelf::instance()
{
    static SweepShelf * sweep = new SweepShelf;
    return sweep;
}

void SweepShelf::destory()
{
    delete instance();
}

bool SweepShelf::Open_DEV(QString com)
{
    if(m_isopen) return true;
    bool ret =   m_opera.S_OpenCOM(com);
    m_opera.S_serveon();
    m_isopen = true ;
    return  ret;
}

void SweepShelf::Close_DEV()
{
    if(m_isopen)
    {
        m_opera.S_CloseCOM();
        m_opera.S_serveoff();
        m_isopen = false;
    }
}

bool SweepShelf::MOVE_TO_Origin()
{
    if(!m_isopen) return false;
    return  m_opera.M_origin();
}

bool SweepShelf::MOVE_TO(double distance)
{
    if(!m_isopen) return false;
    return  m_opera.M_move(distance);
}

bool SweepShelf::IsMoveDone()
{
    if(!m_isopen)
    {
        emit MoveStatus(false);
        return false;
    }
    bool ret =  m_opera.S_movedone();
    emit MoveStatus(ret);
    return  ret;
}

double SweepShelf::Cur_Pos()
{
    if(!m_isopen) return 20000;
    return  m_opera.S_position();
}

void SweepShelf::reset()
{
    if(m_isopen)
        MOVE_TO_Origin();
}

void SweepShelf::ClearWarnning()
{
    if(m_isopen)
        m_opera.S_clearwarn();
}

void SweepShelf::SetMoveSpeed(MOVESPEESD speed)
{
    if(!m_isopen) return;
    m_opera.S_SetMoveSpeed(speed);
}

bool SweepShelf::Isopen()
{
    return m_isopen;
}
