#ifndef SWEEPLINE_H
#define SWEEPLINE_H

#include "radarwnd_global.h"
#include <QtWidgets>
#include <QGraphicsLineItem>

class RADARWNDSHARED_EXPORT SweepLine : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

    enum DetectStatus{ALive, Dead};
    enum SweepDirection{Positvie, Negative};
public:
    explicit SweepLine(QGraphicsLineItem *parent=0);

signals:
    void current_pos(QPointF &pt);
    void current_neg(QPointF &pt);
    void finish();
public slots:
    void begin_sweep(int ox, int oy, int ex, int ey);
    void stop_sweep();
    void sweep(qreal value);
    void sweep_finish();

private:
    QTimeLine       m_sweep_timer;

    double          m_cx;
    double          m_cy;
    double          m_ox;
    double          m_oy;
    DetectStatus    m_status;
    SweepDirection  m_direction;
};

#endif // SWEEPLINE_H
