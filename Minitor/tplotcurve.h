#ifndef TPLOTCURVE_H
#define TPLOTCURVE_H

#include "qwt_plot_curve.h"

class TPlotCurve : public QwtPlotCurve
{
public:
    TPlotCurve(QString title);
    void init_curve();
    void clean();
    void setName(QString name_)              {m_title  =  name_;}
    void set_pen (QPen &pen)                 {m_pen    =    pen;}
    void setPointnums(int num)               {m_point_num = num;}
    double*& x_data()                        {return m_xdata;   }
    double*& y_data()                        {return m_ydata;   }
    void setCurPoint(int num)                {m_cur_point = num;}
    int &getCurPoint()                       {return m_cur_point;}
    void updateCurPoint();
    void update_curve();
private:
    double          *m_xdata;
    double          *m_ydata;
    QPen             m_pen;
    int              m_point_num;
    QString          m_title;
    int              m_cur_point;
};

#endif // TPLOTCURVE_H
