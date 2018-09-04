#include "testunit.h"

TestUnit::TestUnit(QString &text, QRectF rect, UniType type, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_text(text),
    m_type(type),
    m_rect(rect),
    m_fill_rect(rect.left()+1, rect.top()+1, rect.width()-2, rect.height()-2),
    m_high_color(QColor(155,255,155)),
    m_low_color(QColor(155,200,155)),
    m_pen_color(QColor(0,0,0)),
    m_top(rect.left() + rect.width()/2, rect.top()),
    m_bottom(rect.left() + rect.width()/2, rect.bottom()),
    m_left(rect.left(), rect.top() + rect.height()/2),
    m_right(rect.right(), rect.top() + rect.height()/2)
{
    m_pressed = false;
    switch (m_type) {
    case RoundRect:
    {
        m_paint_path.addRoundedRect(m_rect, 10, 10);
        m_fill_path.addRoundedRect(m_fill_rect, 10, 10);
        break;
    }
    case Rect:
    {
        m_paint_path.addRect(m_rect);
        m_fill_path.addRect(m_fill_rect);
        break;
    }
    case Ecllipse:
    {
        m_paint_path.addEllipse(m_rect);
        m_fill_path.addEllipse(m_fill_rect);
        break;
    }
    case Prismatic:
    {
        m_paint_path.moveTo(m_rect.left() + m_rect.width()/2, m_rect.top());
        m_paint_path.lineTo(m_rect.right(), m_rect.top() + m_rect.height()/2);
        m_paint_path.lineTo(m_rect.left() + m_rect.width()/2, m_rect.bottom());
        m_paint_path.lineTo(m_rect.left(), m_rect.top() + m_rect.height()/2);
        m_paint_path.closeSubpath();

        m_fill_path.moveTo(m_fill_rect.left() + m_fill_rect.width()/2, m_fill_rect.top());
        m_fill_path.lineTo(m_fill_rect.right(), m_fill_rect.top() + m_fill_rect.height()/2);
        m_fill_path.lineTo(m_fill_rect.left() + m_fill_rect.width()/2, m_fill_rect.bottom());
        m_fill_path.lineTo(m_fill_rect.left(), m_fill_rect.top() + m_fill_rect.height()/2);
        m_fill_path.closeSubpath();
        break;
    }
    default:
        break;
    }

    m_color_map[Unit_Init].first = QColor(200,200,200);
    m_color_map[Unit_Init].second = QColor(150,150,150);

    m_color_map[Unit_Normal].first = QColor(155,255,155);
    m_color_map[Unit_Normal].second = QColor(155,200,155);

    m_color_map[Unit_Warning].first = QColor(255,255,155);
    m_color_map[Unit_Warning].second = QColor(200,200,155);

    m_color_map[Unit_Error].first = QColor(255,155,155);
    m_color_map[Unit_Error].second = QColor(200,155,155);

    m_color_map[Unit_Finish].first = QColor(100,200,155);
    m_color_map[Unit_Finish].second = QColor(100,155,100);

    m_status = Unit_Normal;


}

void TestUnit::set_status(TestUnit::UnitStatus status)
{
    m_status = status;
}

TestUnit::UnitStatus TestUnit::status()
{
    return m_status;
}

void TestUnit::actions()
{
}

void TestUnit::init_widgets()
{
}

void TestUnit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit pressed();
    m_pressed = true;
    update();
}

void TestUnit::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_pressed = false;
    update();
}

void TestUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(QColor(0,0,0), 2));
    painter->drawPath(m_paint_path);
    if(m_pressed)
    {
        QBrush brush(m_color_map[m_status].second);
        painter->fillPath(m_fill_path, brush);
        painter->drawText(m_fill_rect,Qt::AlignCenter, m_text);
    }else
    {
        QBrush brush(m_color_map[m_status].first);
        painter->fillPath(m_fill_path, brush);
        painter->drawText(m_fill_rect, Qt::AlignCenter, m_text);
    }
}

QRectF TestUnit::boundingRect() const
{
    return m_rect;
}
