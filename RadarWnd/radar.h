#ifndef RADAR_H
#define RADAR_H

#include "radarwnd_global.h"
#include <QtWidgets>
#include "_global.h"
using namespace CVTS;

class RADARWNDSHARED_EXPORT Radar : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
public:
    enum RadarStatus{TurnOn, HighLight,Flicker,Dead};
    enum FlickerDirection{Positive, Negative};
public:
    explicit Radar(int id, CVTS::SPoint &sp, QGraphicsEllipseItem *parent = 0);
    Radar(Radar* radar, QGraphicsEllipseItem *parent = 0);

    void turn_on();
    int id(){return m_id;}
    void turn_on_forever();
    void to_high_light();
    void to_flicker();
    void reset();
    RadarStatus status();
    QPointF center_pt();
    QPointF origin_pt();
    CVTS::SPoint &get_default_point();
    void set_color(QColor &c);
    void to_config_phase();
    void set_tip_text(QString &tip);
    bool &isbad();
    void set_bad_num(int num);
    int &get_bad_num();
    RadarDataMap &get_data();
    void set_isbad(bool bug);


signals:
    void register_radar(int id);
public slots:
    void high_light(qreal value);
    void high_light_finish();
    void flicker(qreal value);
    void flicker_finish();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    QTimeLine           m_time_high_light;
    QTimeLine           m_time_flicker;
    RadarStatus         m_radar_status;
    QBrush              m_radar_brush;
    QPen                m_radar_pen;
    double              m_cur_radius;
    QRadialGradient     m_radar_gradient;
    FlickerDirection    m_flicker_direction;
    CVTS::SPoint        m_sp;
    CVTS::SPoint        m_default_sp;
    int                 m_id;
    QColor              m_color;
    QString             m_tipText;
    bool                m_isbad;
    int                 m_bad_num;
    RadarDataMap        m_radar_data_map;
};

#endif // RADAR_H
