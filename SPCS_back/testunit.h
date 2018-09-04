#ifndef TESTUNIT_H
#define TESTUNIT_H

#include <QtWidgets>
#include <QGraphicsItem>


/*!
 * \brief The TestUnit class
 * 监控界面，系统的动态效果，每个itme 对象
 */
class TestUnit : public QObject, public QGraphicsItem
{
    Q_OBJECT

    Q_INTERFACES(QGraphicsItem)
public:
    enum UniType{RoundRect, Rect, Prismatic, Ecllipse};
    enum UnitStatus{Unit_Init, Unit_Normal, Unit_Warning, Unit_Error, Unit_Finish};
public:
    TestUnit(QString &text, QRectF rect, UniType type = Rect, QGraphicsItem *parent = 0);
    
    void set_status(TestUnit::UnitStatus status);
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
signals:
    void pressed();

public slots:


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

    QColor          m_high_color;
    QColor          m_low_color;
    QPen            m_pen_color;
    QString         m_text;
    QPainterPath    m_paint_path;
    QPainterPath    m_fill_path;
    UnitStatus      m_status;
    QMap<UnitStatus, QPair<QColor,QColor> >        m_color_map;


    ///
    QAction*        m_acts;
    QWidget*        m_widgets;

    ///
    QPointF         m_top;
    QPointF         m_bottom;
    QPointF         m_left;
    QPointF         m_right;
};

#endif // TESTUNIT_H
