#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent) :
    QStatusBar(parent)
{
    setFixedHeight(15);
}

StatusBar *StatusBar::instance()
{
    static StatusBar *statusBar = new StatusBar();
    return statusBar;
}

void StatusBar::destroy()
{
    delete instance();
}

void StatusBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRectF rt(rect().left(), rect().top(), rect().width() -1, rect().height() -1);
    painter.setPen(QPen(QColor(155,155,155), 0));
    painter.drawRect(rt);
}
