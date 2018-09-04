#include "m_cvts_plot_curve.h"

M_CVTS_Plot_Curve::M_CVTS_Plot_Curve(QString title):
    QwtPlotCurve(title),
    m_title(title)
{

}

void M_CVTS_Plot_Curve::init_curve()
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
            setSamples(m_xdata, m_ydata, m_point_num);
        }
    }
    ls_plot->replot();
}

void M_CVTS_Plot_Curve::curve_clean()
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
}
