#include "rightpane.h"
#include "controlpane.h"
#include "delaytask.h"
#include <QDebug>

RightPane::RightPane(QWidget *parent) :
    QWidget(parent),
    m_gridLayout(this)
{
    setFixedWidth(240);
    m_gridLayout.addWidget(ControlPane::instance(this),0,0);
    setLayout(&m_gridLayout);
}


void RightPane::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRectF rt(rect().left(), rect().top(), rect().width() -1, rect().height() -1);
    painter.setPen(QPen(QColor(155,155,155), 0));
    painter.drawRect(rt);
}

