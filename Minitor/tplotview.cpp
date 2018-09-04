#include "tplotview.h"

TPlotView::TPlotView(QWidget *parent) :
    QWidget(parent),
    m_Layout(this)
{
    m_Layout.setSpacing(2);
    m_Layout.setContentsMargins(1,1,1,1);
    setLayout(&m_Layout);
    init();
}

void TPlotView::init()
{
    m_charts.t_num = M_TWO;
    m_cur_unit_id = -1;

    TPlot *ls_plot = new TPlot(MAG, this);
    ls_plot->setFrameShape(QFrame::StyledPanel);
    ls_plot->setCanvasBackground(QColor(Qt::black));
    ls_plot->set_AxisTitle(QwtPlot::yLeft,"Mag");
    ls_plot->set_AxisTitle(QwtPlot::xBottom,"Frequency");
    ls_plot->setVisible(false);

    m_charts.t_plots.push_back(ls_plot);
    ls_plot = new TPlot(PHA, this);
    ls_plot->setFrameShape(QFrame::StyledPanel);
    ls_plot->setCanvasBackground(QColor(Qt::black));
    ls_plot->set_AxisTitle(QwtPlot::yLeft,"Phase");
    ls_plot->set_AxisTitle(QwtPlot::xBottom,"Frequency");
    ls_plot->setVisible(false);
    m_charts.t_plots.push_back(ls_plot);
    m_cur_wnd = 0;

    show_chart(m_charts);
}

void TPlotView::clean()
{
    m_cur_unit_id = -1;
    m_charts.reset();
}

void TPlotView::show_chart(MonitorChart &p_charts)
{
    m_charts = p_charts;
    if(m_charts.t_num == M_NONE) return ;
    switch(m_charts.t_num)
    {
    case M_ONE:
    {
        break;
    }
    case M_TWO:
    {
        show_two_chart();
        break;
    }
    }
}

void TPlotView::show_two_chart()
{
    if(m_cur_wnd == 2) return ;
    if(m_cur_wnd == 1)
    {
        m_Layout.removeWidget(m_charts.t_plots[0]);
    }else if(m_cur_wnd == 4)
    {
        m_Layout.removeWidget(m_charts.t_plots[0]);
        m_Layout.removeWidget(m_charts.t_plots[1]);
    }
    m_Layout.addWidget(m_charts.t_plots[0],0);
    m_Layout.addWidget(m_charts.t_plots[1],1);
    m_charts.t_plots[0]->setVisible(true);
    m_charts.t_plots[1]->setVisible(true);
    m_Layout.setStretch(0,1);
    m_Layout.setStretch(1,1);
    m_Layout.setSpacing(2);
    m_Layout.setSizeConstraint(QLayout::SetDefaultConstraint);
    m_cur_wnd = 2;
}

void TPlotView::UpdateData(int _ID,double freq_,double _M, double _P)
{
    if(m_cur_unit_id != _ID)
    {
        //clean();
        m_cur_unit_id = _ID;
    }
   // if(_M <= 0) return ;
    double db = SPCS_dB::dB(_M);
    m_charts.t_plots[0]->set_title(MAG);
    m_charts.t_plots[1]->set_title(PHA);

    m_charts.t_plots[0]->append_data(_ID,freq_,db);
    m_charts.t_plots[1]->append_data(_ID,freq_,_P);
}
