#ifndef T_RIGHT_H
#define T_RIGHT_H

#include <QtWidgets>
#include "tplotview.h"

class T_Right : public QWidget
{
    Q_OBJECT
public:
    explicit T_Right(QWidget *parent = 0);
    void enableReturn(bool res);
signals:
    void back();
    void StopTest();
public slots:
    void UpdateData(int _ID, double freq_, double _M, double _P);
protected:
    virtual void resizeEvent(QResizeEvent *e);
private:
    TPlotView       m_view;
    QGroupBox       *ls_group;
    QGridLayout     m_grid_layout;
    QPushButton     *m_return;
    QPushButton     *m_stop;
};

#endif // T_RIGHT_H
