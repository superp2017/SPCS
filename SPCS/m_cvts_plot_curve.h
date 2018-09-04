#ifndef M_CVTS_PLOT_CURVE_H
#define M_CVTS_PLOT_CURVE_H

#include"qwt_plot_curve.h"
#include <QString>
#include <QPen>
#include "_global.h"
#include "qwt_plot.h"

using namespace CVTS;


/*!
 * \brief The M_CVTS_Plot_Curve class
 * ÇúÏßÀà
 */
class M_CVTS_Plot_Curve : public QwtPlotCurve
{
public:
    M_CVTS_Plot_Curve(QString title);
    void init_curve();
    void curve_clean();
    void set_name(QString name_)             {m_title  =  name_;}
    void set_pen (QPen &pen)                 {m_pen    =    pen;}
    void set_point_num(int num)              {m_point_num = num;}
    void set_curve_type(CURVE_TYPE type)     {m_type  =    type;}
    double*& x_data()                        {return m_xdata;   }
    double*& y_data()                        {return m_ydata;   }
private:
    double          *m_xdata;
    double          *m_ydata;
    QPen             m_pen;
    int              m_point_num;
    CURVE_TYPE       m_type;
    QString          m_title;
};

#endif // M_CVTS_PLOT_CURVE_H
