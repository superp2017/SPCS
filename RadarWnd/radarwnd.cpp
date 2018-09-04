#include "radarwnd.h"


RadarWnd::RadarWnd(QWidget *parent)
    : QWidget(parent)
{

}

RadarWnd::~RadarWnd()
{

}

bool RadarWnd::load(QString file)
{
    return true;
}


void RadarWnd::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(QColor(0,0,0)));
}
