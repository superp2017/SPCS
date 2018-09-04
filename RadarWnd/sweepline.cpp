#include "sweepline.h"

SweepLine::SweepLine(QGraphicsLineItem *parent)
    : QGraphicsLineItem(parent),
      m_sweep_timer(10000, this)
{
    m_sweep_timer.setUpdateInterval(10);
    connect(&m_sweep_timer, SIGNAL(valueChanged(qreal)), SLOT(sweep(qreal)));
    connect(&m_sweep_timer, SIGNAL(finished()), SLOT(sweep_finish()));
    m_sweep_timer.setEasingCurve(QEasingCurve::Linear);
    m_status = Dead;
}


void SweepLine::begin_sweep(int ox, int oy, int ex, int ey)
{
    if(m_status == ALive) return ;
    m_ox = ox;
    m_oy = oy;
    m_cx = ex - ox;
    m_cy = ey - oy;
    setPos(ox, oy);
    show();
    m_status = ALive;
    m_direction = Positvie;
    QPen pen;
    pen.setColor(QColor(255,25,25,155));
    pen.setWidth(3);
    setPen(pen);
    show();
    m_sweep_timer.start();
}

void SweepLine::stop_sweep()
{
    m_sweep_timer.stop();
    m_status = Dead;
    m_direction = Positvie;
}

void SweepLine::sweep(qreal value)
{
    if(m_status == ALive)
    {
        if(m_direction == Positvie)
        {
            QPointF ptf(m_ox + m_cx * value, m_oy);
            setPos(ptf);
            emit current_pos(ptf);
        }else
        {
            QPointF ptf(m_ox + m_cx * (1 - value), m_oy);
            setPos(ptf);
            emit current_neg(ptf);
        }
    }else m_sweep_timer.stop();
}

void SweepLine::sweep_finish()
{
    if(m_direction == Positvie)
    {
        m_direction = Negative;
        m_sweep_timer.start();
    }
    else
    {
        hide();
        emit finish();
    }
}
