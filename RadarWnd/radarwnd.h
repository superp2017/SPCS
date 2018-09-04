#ifndef RADARWND_H
#define RADARWND_H

#include "radarwnd_global.h"
#include <QtWidgets>


class RADARWNDSHARED_EXPORT RadarWnd : public QWidget
{
    Q_OBJECT
public:
    explicit RadarWnd(QWidget *parent=0);
    ~RadarWnd();

public:
    bool load(QString file);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // RADARWND_H
