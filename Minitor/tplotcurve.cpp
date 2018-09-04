#include "tplotcurve.h"
#include "qwt_plot.h"

TPlotCurve::TPlotCurve(QString title):
    QwtPlotCurve(title),
    m_title(title),
    m_pen(Qt::green, 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin)
{
    m_cur_point = 0;
}

void TPlotCurve::init_curve()
{
    QwtPlot* ls_plot = plot();
    if(ls_plot)
    {
        ls_plot->setAutoReplot(false);
        ls_plot->enableAxis(QwtPlot::yLeft);
        this->setTitle(m_title);
        setRenderHint(QwtPlotItem::RenderAntialiased);
        setPen(m_pen);
        setLegendAttribute(QwtPlotCurve::LegendShowLine);
        setYAxis(QwtPlot::yLeft);
        ls_plot->setAutoReplot(true);

        if(-1 != m_point_num && m_xdata && m_ydata)
        {
            setSamples(m_xdata, m_ydata, m_cur_point);
        }
    }
    ls_plot->replot();
}

void TPlotCurve::clean()
{
    QwtPlot* ls_plot = plot();
    if(ls_plot)
    {
        ls_plot->enableAxis(yAxis(),false);
        detach();
    }
    delete [] m_xdata;
    delete [] m_ydata;

    m_xdata = 0;
    m_ydata = 0;
    m_cur_point = 0;
}

void TPlotCurve::updateCurPoint()
{
    m_cur_point +=1;
}

void TPlotCurve::update_curve()
{
    setSamples(m_xdata, m_ydata, m_cur_point);
}
