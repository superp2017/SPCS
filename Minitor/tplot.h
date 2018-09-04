#ifndef TPLOT_H
#define TPLOT_H
#include "qwt_plot.h"
#include <QtWidgets>
#include "tplotcurve.h"
#include "qwt_plot_grid.h"

#define POINTNUMS       2048

class TPlot : public QwtPlot
{
    Q_OBJECT
public:
    TPlot(QString title,QWidget *parent = 0);
    ~TPlot();
    void clean();
    void set_title(QString title);
    void set_AxisTitle(int axisId, QString title);
    void CreatCurve(double id, double xdata, double ydata);
    void reset_curve();
    void append_data(double id, double xdata, double ydata);
protected:
    void InitPlot();
    void show_grid(bool show);
    bool curveIsExsit(int id);
    void CreatNewCurve(double id, double xdata, double ydata);
    void AppendCurve(TPlotCurve *p_curve, double xdata, double ydata);
private:
    QwtText                      m_title;
    QwtText                      m_y_title;
    QwtText                      m_x_title;
    std::map<int,TPlotCurve *>   m_curve;
    QwtPlotGrid                  *m_grid;
    TPlotCurve *                 m_cur_curve;
    int                          m_last_curve_id;
};

#endif // TPLOT_H
