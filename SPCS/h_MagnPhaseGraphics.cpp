#include "h_MagnPhaseGraphics.h"

h_MagnPhaseGraphics::h_MagnPhaseGraphics(QWidget *parent) :
    QWidget(parent)
{
    m_widget = 0;
    m_layout = new QGridLayout(this);
    setLayout(m_layout);
}

void h_MagnPhaseGraphics::show_widget(QWidget *widget)
{
    if(widget == 0) return ;
    if(widget == m_widget)
    {
        m_layout->addWidget(m_widget);
        m_widget->setGeometry(rect());
        m_widget->showNormal();
        return ;
    }
    if(m_widget != 0) m_widget->hide();
    m_widget = widget;

    m_layout->addWidget(m_widget);
    m_widget->setGeometry(rect());
    m_widget->showNormal();
}

void h_MagnPhaseGraphics::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    QRectF rts(rect().left(), rect().top(), rect().width() -1, rect().height() -1);
    painter.setPen(QPen(QColor(155,155,155), 0));
    painter.drawRect(rts);
}



