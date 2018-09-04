#ifndef BUZIWIDGET_H
#define BUZIWIDGET_H

#include <QGraphicsScene>
#include <QtWidgets>
#include "_global.h"

class BuziUnit;
/*!
 * \brief The BuziScene class
 *  监控界面的系统动态效果
 */
class BuziScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BuziScene(qreal x, qreal y, qreal width, qreal height);



signals: 
    void muti_switch(int id);
    void show_array();
public slots:
    void switch_on(int id);
    void switch_off(int id);
    void detector_on(int id);
    void detector_off(int id);
    void scanner_pos(double pos);

protected:
    void init();

protected:

private:
    qreal       m_x;
    qreal       m_y;
    qreal       m_w;
    qreal       m_h;
    BuziUnit*   m_scanner;
    BuziUnit*   m_detector[16];
    BuziUnit*   m_radar;
    BuziUnit*   m_near_detector;
    BuziUnit*   m_vna;
    BuziUnit*   m_attenuator;
    BuziUnit*   m_electronic_switch[17];
    BuziUnit*   m_muti_switch;

    bool        m_ele_id[16];
    int         m_last_det_id;
    int         m_last_ele_id;
};

class BuziLine : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit BuziLine(QGraphicsItem *parent = 0);

signals:

public slots:
    void push_back(QPointF &pt);
    void valid_line();
    void set_line_width(double w);
    void set_line_color(QColor c);

public:
    virtual QRectF boundingRect() const;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QVector<QPointF>        m_pts;
    QLineF*                 m_lines;
    int                     m_count;
    QPainterPath            m_line_path;
    double                  m_line_width;
    QColor                  m_line_color;
};

class BuziUnit : public QObject, public QGraphicsItem
{
    Q_OBJECT

    Q_INTERFACES(QGraphicsItem)
public:
    enum UniType{RoundRect, Rect, Prismatic, Ecllipse, Detector, Scanner, EleSwitch, MutiSwitch, UniNum};
    enum UnitStatus{Unit_Init, Unit_Normal, Unit_Warning, Unit_Error, Unit_Finish};
public:
    BuziUnit(QString &text, QRectF rect, UniType type = Rect, QGraphicsItem *parent = 0);

    void set_status(BuziUnit::UnitStatus status);
    UnitStatus status();

    virtual void actions();
    virtual void init_widgets();

    QPointF left()
    {
        return m_left;
    }

    QPointF right()
    {
        return m_right;
    }

    QPointF top()
    {
        return m_top;
    }

    QPointF bottom()
    {
        return m_bottom;
    }

    void scanner_pos(double pos)
    {
        if(pos < -15 || pos > 15) return;
        m_scanner_pos = pos;
        update();
    }


signals:
    void pressed();

public slots:
    void switch_on()
    {
        m_switch_color = QColor(155,255,155);
        update();
    }

    void switch_off()
    {
        m_switch_color = QColor(0,0,0);
        update();
    }

    void detector_on()
    {
        m_detector_width = 1;
        m_detector_color = QColor(125,255,0);
        update();
    }

    void detector_off()
    {
        m_detector_color = QColor(0,0,0);
        m_detector_width = 1;
        update();
    }

    void muti_switch(int id)
    {
        if(id == -1) m_muti_id = id;
        m_muti_id = id%SPCS_Muti_N;
        update();
    }

    void set_id(int id)
    {
        m_id = id;
    }

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    virtual QRectF boundingRect() const;

private:
    UniType         m_type;
    QRectF          m_rect;
    QRectF          m_fill_rect;
    bool            m_pressed;
    bool            m_connected;

    QColor          m_high_color;
    QColor          m_low_color;
    QColor          m_detector_color;
    int             m_detector_width;
    QPen            m_pen_color;
    QColor          m_switch_color;
    QString         m_text;
    QPainterPath    m_paint_path;
    QPainterPath    m_fill_path;
    UnitStatus      m_status;
    QMap<UnitStatus, QPair<QColor,QColor> >        m_color_map;

    ///
    QAction*        m_acts;
    QWidget*        m_widgets;
    QPointF*        m_muti_pts;

    ///
    QPointF         m_top;
    QPointF         m_bottom;
    QPointF         m_left;
    QPointF         m_right;
    int             m_muti_id;
    int             m_id;
    QPointF         m_muti_begin_pts;

    double          m_scanner_pos;
};

class BuziWidget : public QGraphicsView
{
    Q_OBJECT
protected:
    explicit BuziWidget(BuziScene *parent = 0);
    ~BuziWidget();

public:
    static BuziWidget*  instance();
public:
    void muti_switch_s(int id){ emit muti_switch(id);}
    void switch_on_s(int id){emit switch_on(id);}
    void switch_off_s(int id){emit switch_off(id);}
    void detector_on_s(int id){emit detector_on(id);}
    void detector_off_s(int id){emit detector_off(id);}
    void scanner_pos_s(double pos){emit scanner_pos(pos);}
signals:
    void muti_switch(int id);
    void switch_on(int id);
    void switch_off(int id);
    void detector_on(int id);
    void detector_off(int id);
    void scanner_pos(double pos);
    void show_array();
public slots:

private:
    BuziScene*      m_sence;
};

#endif // BUZIWIDGET_H
