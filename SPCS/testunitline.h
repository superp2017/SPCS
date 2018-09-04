#ifndef TESTUNITLINE_H
#define TESTUNITLINE_H

#include <QtWidgets>

/*!
 * \brief The TestUnitLine class
 * 测试监控界面,item对象
 */
class TestUnitLine : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit TestUnitLine(QGraphicsItem *parent = 0);
    
signals:
    
public slots:
    void push_back(QPointF &pt);
    void valid_line();

public:
    virtual QRectF boundingRect() const;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QVector<QPointF>        m_pts;
    QLineF*                 m_lines;
    int                     m_count;
    QPainterPath            m_line_path;
};

#endif // TESTUNITLINE_H
