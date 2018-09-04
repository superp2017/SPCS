#ifndef M_CVTS_PLOT_H
#define M_CVTS_PLOT_H
#include <QtWidgets>
#include "_My_Plot.h"
#include "m_cvts_plot_curve.h"
#include "numvalue_convert.h"
#include "_global.h"
#include  <QVector>
#include  <complex>
#include <QMouseEvent>
#include <QColorDialog>

using namespace CVTS;


/*!
 * \brief The MyZoomer class
 * plot ¿‡
 */
class MyZoomer: public QwtPlotZoomer
{
public:
    MyZoomer(QwtPlotCanvas *canvas):
        QwtPlotZoomer(canvas)
    {
        setTrackerMode(AlwaysOn);
        setMousePattern(QwtEventPattern::MouseSelect2,
                        Qt::NoButton, Qt::ControlModifier);
        setMousePattern(QwtEventPattern::MouseSelect3,
                        Qt::NoButton);

        setRubberBandPen(QColor(Qt::gray));
        setTrackerPen(QColor(Qt::black));
    }
    virtual QwtText trackerTextF(const QPointF &pos) const
    {
        QColor bg(Qt::white);
        bg.setAlpha(200);
        QwtText text = QwtPlotZoomer::trackerTextF(pos);
        text.setBackgroundBrush( QBrush( bg ));
        return text;
    }
};

class M_CVTS_Plot : public QwtPlot
{
    Q_OBJECT
public:
    explicit M_CVTS_Plot(QString title,QWidget *parent = 0);
    void clean();
    void Create_new_Curve(QString name, QColor color, \
                          std::vector<QString> &y_data,\
                          std::vector<QString> &x_data,\
                          int pointnum);
    void init_data();
protected:
    void zoom_reset();
    void init_plot();
    void detach_all();
    void show_grid(bool p_show);
    bool Curve_isexist(QString name);
    void attch_curve(M_CVTS_Plot_Curve * p_curve);
    void set_curve_attribute(M_CVTS_Plot_Curve * p_curve,QColor color);
    void set_curve_data(M_CVTS_Plot_Curve *p_curve, int num,\
                        std::vector<QString> &y_data, \
                        std::vector<QString> &x_data);
    void mousePressEvent(QMouseEvent *e);
private:
    QwtLegend                              *m_legend;
    QwtPlotGrid                            *m_grid;
    std::map<QString,M_CVTS_Plot_Curve *>   m_curve;
    QString                                 m_title;
    QwtPlotMagnifier                       *m_PM;
    MyZoomer                               *m_zoomer;
    QwtPlotPanner                          *m_panner;


    double                                  m_de_max_x;
    double                                  m_de_min_x;
    double                                  m_de_max_y;
    double                                  m_de_min_y;
};

#endif // M_CVTS_PLOT_H
