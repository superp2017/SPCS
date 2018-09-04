#include "tplot.h"

TPlot::TPlot(QString title, QWidget *parent):
    QwtPlot(parent),
    m_title(title),
    m_y_title("Y"),
    m_x_title("X")
{
    m_cur_curve = 0;
    m_last_curve_id = -1;
    InitPlot();
}

TPlot::~TPlot()
{
    clean();
}

void TPlot::InitPlot()
{
    setAutoReplot(false);
    m_title.setFont(QFont("ºÚÌå",11,QFont::Normal));
    m_y_title.setFont(QFont("ºÚÌå",11,QFont::Normal));
    m_x_title.setFont(QFont("ºÚÌå",11,QFont::Normal));
    setTitle(m_title);
    setAxisTitle(QwtPlot::xBottom,m_x_title);
    setAxisTitle(QwtPlot::yLeft,m_y_title);
    this->enableAxis(QwtPlot::yLeft,true);
    this->enableAxis(QwtPlot::xBottom,true);
    this->setCanvasBackground(QColor(Qt::black));
    show_grid(true);
    setAxisAutoScale(QwtPlot::xBottom);
    setAxisAutoScale(QwtPlot::yLeft);
    setAxisMaxMajor(QwtPlot::yLeft , 6);
    setAxisMaxMinor(QwtPlot::yLeft, 10);
    setAutoReplot(true);
}

void TPlot::set_title(QString title)
{
    m_title.setText(title);
    setTitle(m_title);
}

void TPlot::set_AxisTitle(int axisId, QString title)
{
    if(axisId == QwtPlot::xBottom)
    {
        m_x_title.setText(title);
        setAxisTitle(axisId,m_x_title);
    }
    if(axisId == QwtPlot::yLeft)
    {
        m_y_title.setText(title);
        setAxisTitle(axisId,m_y_title);
    }
}

void TPlot::show_grid(bool show)
{
    if(show)
    {
        m_grid = new QwtPlotGrid;
        m_grid->enableXMin(true);
        m_grid->setMajorPen(QPen(Qt::white, 0, Qt::DotLine));
        m_grid->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
        m_grid->attach(this);
    }
}

bool TPlot::curveIsExsit(int id)
{
    return m_curve.count(id) >0;
}

void TPlot::CreatCurve(double id_,double xdata, double ydata)
{
    if(curveIsExsit(id_))
    {
        TPlotCurve*  ls_curve = m_curve[id_];
        AppendCurve(ls_curve,xdata,ydata);
    }else
    {
        CreatNewCurve(id_,xdata,ydata);
    }
}

void TPlot::reset_curve()
{
    if(m_cur_curve)
    {
        m_cur_curve->setCurPoint(0);
        this->setAutoReplot(false);
        m_cur_curve->updateCurPoint();
        m_cur_curve->setCurPoint(0);
        m_cur_curve->setSamples(m_cur_curve->x_data(), m_cur_curve->y_data(),m_cur_curve->getCurPoint());
        this->updateAxes();
        this->setAutoReplot(true);
        this->replot();
    }
}

void TPlot::append_data(double id, double xdata, double ydata)
{
    if(!m_cur_curve)
    {
        CreatNewCurve(id,xdata,ydata);
        m_last_curve_id = id;
    }else
    {
        if(m_last_curve_id == id)
        {
            AppendCurve(m_cur_curve,xdata,ydata);
        }else
        {
            reset_curve();
            m_last_curve_id = id;
            AppendCurve(m_cur_curve,xdata,ydata);
        }
    }

}

void TPlot::CreatNewCurve(double id, double xdata, double ydata)
{
    QString name = QString("Unit%1").arg(id);
    TPlotCurve * ls_curve = new TPlotCurve(name);
    m_cur_curve = ls_curve;
    ls_curve->setPointnums(POINTNUMS);
     m_cur_curve->setCurPoint(0);
    ls_curve->x_data() = new double[POINTNUMS];
    ls_curve->y_data() = new double[POINTNUMS];
    if(ls_curve->getCurPoint() >= POINTNUMS-1) return;
    (ls_curve->x_data())[ls_curve->getCurPoint()] =  xdata;
    (ls_curve->y_data())[ls_curve->getCurPoint()] =  ydata;
    m_curve[id] = ls_curve;
    ls_curve->updateCurPoint();
    ls_curve->attach(this);
    ls_curve->init_curve();
}

void TPlot::AppendCurve(TPlotCurve* p_curve,double xdata,double ydata)
{
    if(p_curve->getCurPoint() >= POINTNUMS) return;
    this->setAutoReplot(false);
    (p_curve->x_data())[p_curve->getCurPoint()] = xdata;
    (p_curve->y_data())[p_curve->getCurPoint()] = ydata;
    p_curve->updateCurPoint();
    p_curve->update_curve();
    this->updateAxes();
    this->setAutoReplot(true);
    this->replot();
}


void TPlot::clean()
{
    std::map<int ,TPlotCurve*>::iterator iter = m_curve.begin();
    while(iter!=m_curve.end())
    {
        if(iter->second)
        {
            iter->second->clean();
            delete iter->second;
        }
        ++iter;
    }
    m_curve.clear();
}
