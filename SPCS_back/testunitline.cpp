#include "testunitline.h"

TestUnitLine::TestUnitLine(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    m_count = 0;
}

void TestUnitLine::push_back(QPointF &pt)
{
    m_pts.push_back(pt);
}

void TestUnitLine::valid_line()
{
    m_count = m_pts.size();
    if(m_count < 2) return ;
    m_line_path.moveTo(m_pts[0]);
    for(int i=1; i<m_pts.size(); i++)
    {
        m_line_path.lineTo(m_pts[i]);
    }
    update();
}

QRectF TestUnitLine::boundingRect() const
{
    return m_line_path.boundingRect();
}

void TestUnitLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(m_count < 2) return;
    painter->setPen(QPen(QColor(0,0,0), 2));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(m_line_path);
}
