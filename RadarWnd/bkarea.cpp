#include "bkarea.h"
#include "_global.h"

BkArea::BkArea(QGraphicsRectItem *parent,int xp,int yp) :
    QGraphicsRectItem(parent),
    m_backcol(0,35,5),
    m_xp(xp),
    m_yp(yp),
    m_charactersCol(255,255,0)
{
    m_has_text = true;
}

void BkArea::set_color(QColor &backcol, QColor &charactersCol)
{
    m_backcol = backcol;
    m_charactersCol = charactersCol;
}

void BkArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{ 
    if(m_has_text)
    {
        painter->fillRect(rect(), QBrush(QColor(0,35,5)));
    }
    QPen pen(QColor(5,5,5));
    pen.setWidth(1);
    painter->drawRect(rect());

    int w = rect().width();
    int h = rect().height();
    double dw = w/(Grid_width+2.0);
    double dh = h/(Grid_height+2.0);

   // painter->setPen(QPen(QColor(125,155,0)));
     painter->setPen(QPen(QColor(0,0,0)));
    for(int i=0; i<Grid_width+1; i++)
    {
        painter->drawLine(QPointF((i+1)*dw, dh), QPointF((i+1)*dw, h-dh));
    }

    for(int i=0; i<Grid_height+1; i++)
    {
        painter->drawLine(QPointF(dw, (i+1)*dh), QPointF(w-dw, (i+1)*dh));
    }

    if(m_has_text)
    {
        painter->setPen(QPen(QColor(255,255,0)));
        for(int i=0; i<Grid_width; i++)
        {
            QRect rt((i+1)*dw, m_yp, dw, dh);
            painter->drawText(rt, Qt::AlignCenter, QString::number(i-Grid_half_w));
        }

        for(int i=0; i<Grid_height; i++)
        {
            QRect rt(m_xp, (i+1)*dh, dw, dh);
            painter->drawText(rt, Qt::AlignCenter, QString::number(i+1));
        }

        QPainterPath path;
        path.addEllipse(rect().width()/2-5, rect().height()/2-5, 10, 10);

        QRadialGradient brush;
        brush.setCenter(rect().width()/2, rect().height()/2);
        brush.setRadius(5);
        brush.setFocalPoint(rect().width()/2, rect().height()/2);
        brush.setColorAt(0, QColor::fromRgbF(1, 0, 0, 1));
        brush.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
        painter->fillPath(path, brush);
    }

}
