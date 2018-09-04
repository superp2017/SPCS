#include "h_TestOutArea.h"

h_TestOutArea::h_TestOutArea(QWidget *parent) :
    QWidget(parent),
    m_grid_layout(this)
{
    initWidget();
}


void h_TestOutArea::initWidget()
{
    M_PlotTestView::instance()->init();
    m_mp_gra.show_widget(M_PlotTestView::instance());
    m_grid_layout.addWidget(&m_mp_gra,0);
    m_grid_layout.addWidget(ResultControlPane::instance());
    m_grid_layout.setStretch(0,8);
    m_grid_layout.setStretch(1,1);
    setLayout(&m_grid_layout);
}

void h_TestOutArea::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QRectF rt(rect().left(), rect().top()-1, rect().width() -1, rect().height());
    painter.setPen(QPen(QColor(100,100,100), 0));
    painter.drawRect(rt);
}

















