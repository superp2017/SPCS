#include "radar.h"
#include <QToolTip>

Radar::Radar(int id, CVTS::SPoint &sp, QGraphicsEllipseItem *parent) :
    QGraphicsEllipseItem(parent),
    m_time_high_light(3000, this),
    m_time_flicker(1000, this),
    m_id(id)
{
    m_radar_status = Dead;

    m_time_high_light.setUpdateInterval(5);
    connect(&m_time_high_light, SIGNAL(valueChanged(qreal)), SLOT(high_light(qreal)));
    connect(&m_time_high_light, SIGNAL(finished()), SLOT(high_light_finish()));
    m_time_high_light.setEasingCurve(QEasingCurve::OutCurve);

    m_time_flicker.setUpdateInterval(5);
    connect(&m_time_flicker, SIGNAL(valueChanged(qreal)), SLOT(flicker(qreal)));
    connect(&m_time_flicker, SIGNAL(finished()), SLOT(flicker_finish()));
    m_time_flicker.setEasingCurve(QEasingCurve::OutCurve);
    reset();
    // 保存原始坐标；
    m_default_sp.x = sp.x;
    m_default_sp.y = sp.y;
    m_default_sp.z = sp.z;
    // x坐标和y坐标互换，对应实际系统

//    m_sp.x = sp.y + 2 ;
//    m_sp.y = sp.x - 12 ;
//    m_sp.z = sp.z;
    setRect(m_default_sp.x-5, m_default_sp.y-5, 10, 10);

    set_color(QColor::fromRgbF(0, 1, 1, 1));

    m_tipText = QString::number(m_id);
}

Radar::Radar(Radar *radar, QGraphicsEllipseItem *parent)
    : QGraphicsEllipseItem(parent),
      m_time_high_light(3000, this),
      m_time_flicker(1000, this),
      m_id(radar->id())
{
    m_radar_status = Dead;

    m_time_high_light.setUpdateInterval(5);
    connect(&m_time_high_light, SIGNAL(valueChanged(qreal)), SLOT(high_light(qreal)));
    connect(&m_time_high_light, SIGNAL(finished()), SLOT(high_light_finish()));
    m_time_high_light.setEasingCurve(QEasingCurve::OutCurve);

    m_time_flicker.setUpdateInterval(5);
    connect(&m_time_flicker, SIGNAL(valueChanged(qreal)), SLOT(flicker(qreal)));
    connect(&m_time_flicker, SIGNAL(finished()), SLOT(flicker_finish()));
    m_time_flicker.setEasingCurve(QEasingCurve::OutCurve);
    reset();

    m_sp.x = radar->center_pt().x();
    m_sp.y = radar->center_pt().y();
    m_sp.z = 0;
    setRect(m_sp.x, m_sp.y, 10, 10);

    set_color(QColor::fromRgbF(0, 1, 1, 1));

    m_tipText = QString::number(m_id);
}

void Radar::turn_on()
{
    if(m_radar_status == TurnOn) return ;

    reset();
    m_radar_status = TurnOn;
    int n = (rect().width() + rect().height())/4;
    m_cur_radius = n;
    m_radar_gradient.setCenter(rect().left() + n, rect().top() + n);
    m_radar_gradient.setRadius(n);
    m_radar_gradient.setFocalPoint(rect().left() + n, rect().top() + n);
    m_radar_gradient.setColorAt(0, m_color);
    m_radar_gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
    setBrush(m_radar_gradient);

    m_radar_pen.setColor(QColor::fromRgbF(0.1,0.8,0,0));
    m_radar_pen.setWidth(1);
    setPen(m_radar_pen);
    show();
}

void Radar::turn_on_forever()
{
    reset();
    m_radar_status = TurnOn;
    int n = (rect().width() + rect().height())/4;
    m_cur_radius = n;
    m_radar_gradient.setCenter(rect().left() + n, rect().top() + n);
    m_radar_gradient.setRadius(n);
    m_radar_gradient.setFocalPoint(rect().left() + n, rect().top() + n);
    m_radar_gradient.setColorAt(0, m_color);
    m_radar_gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
    setBrush(m_radar_gradient);

    m_radar_pen.setColor(QColor::fromRgbF(0.1,0.8,0,0));
    m_radar_pen.setWidth(1);
    setPen(m_radar_pen);
    show();
}

void Radar::to_high_light()
{
    if(m_radar_status == HighLight) return ;
    reset();
    m_radar_status = HighLight;
    int n = (rect().width() + rect().height())/4;
    m_cur_radius = n;
    m_radar_gradient.setCenter(rect().left() + n, rect().top() + n);
    m_radar_gradient.setRadius(n);
    m_radar_gradient.setFocalPoint(rect().left() + n, rect().top() + n);
    m_radar_gradient.setColorAt(0, m_color);
    m_radar_gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
    setBrush(m_radar_gradient);

    m_radar_pen.setColor(QColor::fromRgbF(0.1,0.8,0,0));
    m_radar_pen.setWidth(1);
    setPen(m_radar_pen);
    show();
    m_time_high_light.start();
}

void Radar::to_flicker()
{
    if(m_radar_status == Flicker) return ;
    reset();
    m_radar_status = Flicker;
    m_flicker_direction = Positive;

    m_radar_pen.setColor(QColor::fromRgbF(0.1,0.8,0,0));
    m_radar_pen.setWidth(1);
    setPen(m_radar_pen);

    int n = (rect().width() + rect().height())/4;
    m_cur_radius = n;
    m_radar_gradient.setCenter(rect().left() + n, rect().top() + n);
    m_radar_gradient.setRadius(n);
    m_radar_gradient.setFocalPoint(rect().left() + n, rect().top() + n);
    m_radar_gradient.setColorAt(0, m_color);
    m_radar_gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
    setBrush(m_radar_gradient);
    show();
    //m_time_flicker.start();
}

void Radar::reset()
{
    m_isbad = false;
    m_time_flicker.stop();
    m_time_high_light.stop();
    m_radar_status = Dead;
    m_radar_brush.setColor(QColor(0,0,0,0));
    m_radar_pen.setColor(QColor(0,0,0,0));
    update();
    hide();
}

Radar::RadarStatus Radar::status()
{
    return m_radar_status;
}

QPointF Radar::center_pt()
{
    //return QPointF(m_sp.x, m_sp.y);
    return QPointF(rect().left() + rect().width()/2, rect().top() + rect().height()/2);
}

QPointF Radar::origin_pt()
{
    return QPointF(m_default_sp.x, m_default_sp.y);
}

CVTS::SPoint &Radar::get_default_point()
{
    return m_default_sp;
}

void Radar::set_color(QColor &c)
{
    m_color = c;
}

void Radar::to_config_phase()
{
    reset();
    m_radar_status = TurnOn;
    //    int n = (rect().width() + rect().height())/4;
    //    m_cur_radius = n;
    //    m_radar_gradient.setCenter(rect().left() + n, rect().top() + n);
    //    m_radar_gradient.setRadius(n);
    //    m_radar_gradient.setFocalPoint(rect().left() + n, rect().top() + n);
    //    m_radar_gradient.setColorAt(0, m_color);
    //    m_radar_gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
    setBrush(QBrush(m_color));

    m_radar_pen.setColor(QColor::fromRgbF(0.1,0.8,0,0));
    m_radar_pen.setWidth(1);
    setPen(m_radar_pen);
    show();
}

void Radar::set_tip_text(QString &tip)
{
    m_tipText = tip;
}

void Radar::set_isbad(bool bug)
{
    m_isbad = bug;
}

bool &Radar::isbad()
{
    return  m_isbad;
}

void Radar::set_bad_num(int num)
{
    m_bad_num = num;
    if(num != 1)
        set_isbad(true);
    else
        set_isbad(false);
}

int &Radar::get_bad_num()
{
    return m_bad_num;
}

RadarDataMap &Radar::get_data()
{
    return m_radar_data_map;
}

void Radar::high_light(qreal value)
{
    if(m_radar_status == HighLight)
    {
        m_radar_gradient.setColorAt(0, QColor::fromRgbF(0, 1, 1, 1-value*0.9));
        m_radar_gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));

        m_radar_pen.setColor(QColor::fromRgbF(0.1,0.8,0.0,0.2*(1-value*0.9)));
        setBrush(m_radar_gradient);
    }else reset();
}

void Radar::high_light_finish()
{

}


void Radar::flicker_finish()
{
    if(m_flicker_direction == Positive)
        m_flicker_direction = Negative;
    else m_flicker_direction = Positive;
    m_time_flicker.start();
}


void Radar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QToolTip::showText(event->screenPos(), m_tipText);
}


void Radar::flicker(qreal value)
{
    if(m_radar_status == Flicker)
    {
        if(m_flicker_direction == Positive)
        {
            m_radar_gradient.setColorAt(0, QColor::fromRgbF(0, 1, 1, 1-value*0.7));
            m_radar_gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
            //m_radar_gradient.setRadius(m_cur_radius *2 - m_cur_radius * value);
            setBrush(m_radar_gradient);
        }else
        {
            m_radar_gradient.setColorAt(0, QColor::fromRgbF(0, 1, 1, 0.3 + value*0.7));
            m_radar_gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
            //m_radar_gradient.setRadius(m_cur_radius + m_cur_radius * value);
            setBrush(m_radar_gradient);
        }
    }else reset();
}
