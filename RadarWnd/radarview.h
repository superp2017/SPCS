#ifndef RADARVIEW_H
#define RADARVIEW_H

#include "radarwnd_global.h"
#include <QtWidgets>


class BackgroundPixmap
{
protected:
    BackgroundPixmap()
    {

    }
    ~BackgroundPixmap()
    {
        QList<QPixmap*>::iterator iter = m_pixmaps.begin();
        while(iter != m_pixmaps.end())
        {
            delete *iter;
            iter++;
        }
    }

public:
    static BackgroundPixmap* instance()
    {
        static BackgroundPixmap *s_bkmap = new BackgroundPixmap;
        return s_bkmap;
    }
    static void destroy()
    {
        delete instance();
    }


    QPixmap* generate(int w=640, int h=480, int inr=10)
    {
        QPixmap *pixmap = new QPixmap(w, h);
        m_pixmaps.push_back(pixmap);
        QPainter painter(pixmap);
        painter.fillRect(pixmap->rect(), QBrush(QColor(0,35,5)));
        QPen pen(QColor(5,5,5));
        pen.setWidth(1);
        painter.drawRect(pixmap->rect());

        int ew = 0;
        int bx = 0;
        int by = 0;

        painter.drawLine(QPointF(bx, by), QPointF(bx+w, by+h));
        while(ew < w)
        {
            painter.drawLine(QPointF(bx, by+ew), QPointF(bx+w, by+ew));
            painter.drawLine(QPointF(bx+ew, by), QPointF(bx+ew,by+h));
            ew += inr;
        }
        return pixmap;
    }

private:
    QList<QPixmap*>     m_pixmaps;
};


class RADARWNDSHARED_EXPORT RadarView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit RadarView(QGraphicsScene *scene = 0);
    
protected:
    void resizeEvent(QResizeEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
signals:
    void full_screen(bool bl);
public slots:
    
private:
    bool        m_full_screen;
};

#endif // RADARVIEW_H
