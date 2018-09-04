#include "radarview.h"


RadarView::RadarView(QGraphicsScene *scene) :
    QGraphicsView(scene)
{
    m_full_screen = false;
}

void RadarView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void RadarView::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_full_screen = !m_full_screen;
    emit full_screen(m_full_screen);
}






