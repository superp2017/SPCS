#ifndef TMONITOR_H
#define TMONITOR_H

#include <QtWidgets>
#include "monitor_global.h"
#include "_global.h"
#include <QtWidgets>
#include "t_left.h"
#include "t_right.h"

class MONITOR_EXPORT TMonitor : public QWidget
{
    Q_OBJECT
protected:
    explicit TMonitor(QWidget *parent = 0);
public:
    static TMonitor *instance()
    {
        static TMonitor * monitor = new TMonitor();
        return monitor;
    }
    static void destory()
    {
        delete instance();
    }

signals:
    void ShowMainWindow();
    void StopTest();
protected slots:
    void back();
public slots:
    void enableReturn(bool res);
    void Set_up_widget(QWidget *up);
    void Set_down_widget(QWidget *down);
    void UpdateData(int _ID, double freq_, double _M, double _P);
private:
    T_Right            m_right;
    T_Left             m_left;
    QGridLayout        m_grid_layout;
};

#endif // TMONITOR_H
