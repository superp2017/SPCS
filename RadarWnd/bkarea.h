#ifndef BKAREA_H
#define BKAREA_H
#include "radarwnd_global.h"
#include <QtWidgets>

class RADARWNDSHARED_EXPORT BkArea : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit BkArea(QGraphicsRectItem *parent = 0, int xp = 0, int yp =0);
    
    void has_text(bool ht){m_has_text = ht;}
signals:
    
public slots:
    void set_color(QColor &backcol,QColor &charactersCol);
protected:
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
protected:
    bool        m_has_text;
    QColor      m_backcol;
    QColor      m_charactersCol;
    int         m_xp;
    int         m_yp;
};

#endif // BKAREA_H
