#include "detector.h"
#include "radarscene.h"
#include "_global.h"

Detector::Detector(int cd, QRectF &rt, QGraphicsRectItem *item) :
    QGraphicsRectItem(item),
    m_sweep_timer(500*(cd/16.0+1) * (Grid_width - 1), this),
    m_rt(rt),
    m_cd(cd)
{
    m_sweep_timer.setUpdateInterval(500*(cd/16.0+1));
    connect(&m_sweep_timer, SIGNAL(valueChanged(qreal)), SLOT(sweep(qreal)));
    connect(&m_sweep_timer, SIGNAL(finished()), SLOT(sweep_finish()));
    m_sweep_timer.setEasingCurve(QEasingCurve::Linear);
    m_status = Dead;
    setRect(m_rt);
    reset();
}

void Detector::push_back(int ps, int rs)
{
    m_radars_map[ps - Grid_half_w-1].insert(rs);
}

void Detector::reset()
{
    for(int i=0; i<Grid_width; i++)
    {
        m_radars_map[i-Grid_half_w].clear();
    }
}

void Detector::begin_map()
{
    show();
    m_ps = 0;
    m_status = ALive;
    m_rtf.setRect(rect().left(), rect().top(), rect().width(), rect().height());
    m_p.setX(pos().x());
    m_p.setY(pos().y());

    //  emit check_radar(m_rtf, m_cd, m_ps);
      m_sweep_timer.start();
}

void Detector::begin_sweep(int ox, int oy, int ex, int ey)
{
    m_ox = ox;
    m_oy = oy;
    m_cx = ex - ox;
    m_cy = ey - oy;
    setPos(ox, oy);
    show();
    m_status = ALive;
    m_sweep_timer.start();
}

void Detector::stop_sweep()
{
    m_status = Dead;
    m_sweep_timer.stop();
}

void Detector::sweep(qreal value)
{
    if(m_status == ALive)
    {        
        m_p.setX(pos().x() + rect().width());
        m_p.setY(pos().y());
        setPos(m_p);
        m_rtf.setRect(m_p.x() + rect().width(), m_p.y() + m_rtf.height() * m_cd, m_rtf.width(), m_rtf.height());
        m_ps++;
        if(m_ps == (Grid_width - 1)) return ;
        emit check_radar(&m_rtf, m_cd, m_ps);
    }else {m_sweep_timer.stop();
    }
}


void Detector::sweep_finish()
{
    hide();
    m_status = Dead;
    emit next();
}

void Detector::to_next(int ps)
{
    QPointF p(pos().x() + ps * rect().width(), pos().y());
    setPos(p);
    //此处有内存泄漏
    emit check_radar(new QRectF(p.x(), p.y(), rect().width(), rect().height()), m_cd, ps);
}
