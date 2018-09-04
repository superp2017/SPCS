#ifndef DETECTOR_H
#define DETECTOR_H
#include "radarwnd_global.h"
#include <QtWidgets>
#include "_global.h"
#include "PointMap.h"
#include <map>
#include <vector>
#include <set>

class RADARWNDSHARED_EXPORT Detector : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    enum DetectStatus{ALive, Dead};
public:
    explicit Detector(int cd, QRectF &rt, QGraphicsRectItem *item = 0);

    void push_back(int ps, int rs);
    void reset();
    void begin_map();
    ///std::map<int, std::set<int> > first param detector pos, second param radar id sets;
    std::map<int, std::set<int> >& radars(){return m_radars_map;}
signals:
    void next();
    void current_rect(QRectF &rt);
    void check_radar(QRectF *rt, int cd, int pos);
public slots:
    void begin_sweep(int ox, int oy, int ex, int ey);
    void stop_sweep();
    void sweep(qreal value);
    void sweep_finish();
    void to_next(int p);


private:
    QTimeLine                           m_sweep_timer;
    double                              m_cx;
    double                              m_cy;
    double                              m_ox;
    double                              m_oy;
    DetectStatus                        m_status;

    CVTS::SPoint                        m_pt;
    QRectF                              m_rt;
    int                                 m_cd;
    std::map<int, std::set<int> >       m_radars_map;

    int                                 m_ps;
    QRectF                              m_rtf;
    QPointF                             m_p;
};

#endif // DETECTOR_H
