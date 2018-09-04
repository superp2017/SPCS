#include "m_cvts_plot.h"
#include "qwt_text_label.h"

#define CURVE_DATA_SIZE_ERRPR QMessageBox::information(NULL,tr("Warning"),\
    tr("Curve data size error !"));

#define CURVE_EXIST_ERROR    QMessageBox::information(NULL,tr("Warning"),\
    tr("This Curve  was existed ,add curve Failed !"));


M_CVTS_Plot::M_CVTS_Plot(QString title, QWidget *parent) :
    QwtPlot(parent),
    m_title(title)
{
    init_plot();
    init_data();
    clean();
}
void M_CVTS_Plot::init_plot()
{
    setAutoReplot(false);
    setTitle(m_title);
    this->enableAxis(QwtPlot::yLeft,true);
    this->enableAxis(QwtPlot::xBottom,true);
    this->setCanvasBackground(QColor(Qt::black));
    m_legend =new QwtLegend();
    //    m_legend->setDefaultItemMode(QwtLegendData::Clickable );
    this->insertLegend(m_legend, QwtPlot::BottomLegend);
    show_grid(true);
    m_PM = new QwtPlotMagnifier(this->canvas());
    m_zoomer = new  MyZoomer(dynamic_cast<QwtPlotCanvas*>(this->canvas()));
    m_panner = new QwtPlotPanner(this->canvas());
    m_panner->setMouseButton(Qt::MidButton);
    setAxisAutoScale(QwtPlot::xBottom);
    setAxisAutoScale(QwtPlot::yLeft);
    setAxisMaxMajor(QwtPlot::yLeft , 6);
    setAxisMaxMinor(QwtPlot::yLeft, 10);
    setAutoReplot(true);


    QString ls_sheet = QString::fromUtf8("font: 13pt \"\346\245\267\344\275\223\";");


    this->titleLabel()->setStyleSheet(ls_sheet);
}

void M_CVTS_Plot::init_data()
{   
    m_de_max_x = -100000000000;
    m_de_min_x = 100000000000;
    m_de_max_y = -10000000000;
    m_de_min_y = 10000000000;
}

void M_CVTS_Plot::clean()
{
    detach_all();
}

void M_CVTS_Plot::detach_all()
{
    std::map<QString ,M_CVTS_Plot_Curve*>::iterator iter = m_curve.begin();
    while(iter!=m_curve.end())
    {
        iter->second->curve_clean();
        delete iter->second;
        ++iter;
    }
    m_curve.clear();
}

void M_CVTS_Plot::show_grid(bool p_show)
{
    if(p_show)
    {
        m_grid = new QwtPlotGrid;
        m_grid->enableXMin(true);
        m_grid->setMajorPen(QPen(Qt::white, 0, Qt::DotLine));
        m_grid->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
        m_grid->attach(this);
    }
}

bool M_CVTS_Plot::Curve_isexist(QString name)
{
    std::map<QString,M_CVTS_Plot_Curve *> ::iterator iter = m_curve.begin();
    while(iter != m_curve.end())
    {
        if(iter->second->title().text() == name)
        {
            return true;
        }
        ++iter;
    }
    return false;
}

void M_CVTS_Plot::attch_curve(M_CVTS_Plot_Curve *p_curve)
{
    m_curve[p_curve->title().text()] = p_curve;
    p_curve->attach(this);
    p_curve->init_curve();
}

void M_CVTS_Plot::set_curve_attribute(M_CVTS_Plot_Curve *p_curve, QColor color)
{
    QPen ls_pen(color,2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    p_curve->set_pen(ls_pen);
}


void M_CVTS_Plot::set_curve_data(M_CVTS_Plot_Curve *p_curve, int num, std::vector<QString> &y_data,\
                                 std::vector<QString> &x_data)
{
    p_curve->set_point_num(num);
    p_curve->y_data() = new double[num];
    p_curve->x_data() = new double[num];


    double m_max_x = x_data.at(0).toDouble();
    double m_max_y = y_data.at(0).toDouble();
    double m_min_x = x_data.at(0).toDouble();
    double m_min_y = y_data.at(0).toDouble();

    for(int i =0;i < num; ++i)
    {
        double ls_ydata  = y_data.at(i).toDouble();
        double ls_xdata  = x_data.at(i).toDouble();
        if(ls_xdata >= m_max_x)
            m_max_x = ls_xdata;
        if(ls_xdata <= m_min_x)
            m_min_x = ls_xdata;
        if(ls_ydata >= m_max_y)
            m_max_y = ls_ydata;
        if(ls_ydata <= m_min_y)
            m_min_y = ls_ydata;
        p_curve->x_data()[i] = ls_xdata;
        p_curve->y_data()[i] = ls_ydata;
    }

    if(m_max_x>m_de_max_x)
        m_de_max_x = m_max_x;
    if(m_max_y >m_de_max_y)
        m_de_max_y = m_max_y;
    if(m_min_x <m_de_min_x)
        m_de_min_x = m_min_x;
    if(m_min_y < m_de_min_y)
        m_de_min_y = m_min_y;
    setAxisScale(QwtPlot::xBottom,m_de_min_x,m_de_max_x);
    setAxisScale(QwtPlot::yLeft,m_de_min_y,m_de_max_y);
}

void M_CVTS_Plot::Create_new_Curve(QString name, QColor color, std::vector<QString> &y_data, std::vector<QString> &x_data, int pointnum)
{
    if(!Curve_isexist(name))
    {
        if(y_data.size() == x_data.size())
        {
            M_CVTS_Plot_Curve * ls_curve = new M_CVTS_Plot_Curve(name);
            set_curve_attribute(ls_curve,color);
            set_curve_data(ls_curve,pointnum,y_data,x_data);
            attch_curve(ls_curve);
        }else
            CURVE_DATA_SIZE_ERRPR
    }else
        CURVE_EXIST_ERROR
}

void M_CVTS_Plot::zoom_reset()
{
    if(m_curve.size()>0)
    {
        setAxisScale(QwtPlot::xBottom,m_de_min_x,m_de_max_x);
        setAxisScale(QwtPlot::yLeft,m_de_min_y,m_de_max_y);
    }
}

void M_CVTS_Plot::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton)
    {
        zoom_reset();
    }
}

