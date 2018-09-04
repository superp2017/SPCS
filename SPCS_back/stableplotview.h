#ifndef STABLEPLOTVIEW_H
#define STABLEPLOTVIEW_H

#include <QWidget>
#include "m_cvts_plot.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <set>
#include <QDateTime>
#include "m_plottestview.h"



/*!
 * \brief The StablePlotView class
 * 稳定性比较的plot显示类
 */
class StablePlotView : public QWidget
{
    Q_OBJECT
public:
    explicit StablePlotView(QWidget *parent = 0);
    ~StablePlotView();
    void del();
    void init();
    void reset();
    bool creat_curve(Curvedata &p_data, bool ishowmagn = true);
    void creatcurve(Curvedata &p_data);
    void export_curve_data();
public slots:
    void show_chart(CVTSChart &p_charts);
    void show_magn_chart();
    void show_two_chart();
    void show_phase_chart();
    void data_clear();
    void view_reset();
signals:
    void plot_import();
    
public slots:
private:
    QWidget*                m_main_widget;
    QVBoxLayout             m_Layout;
    CVTSChart               m_charts;
    int                     m_cur_wnd;
    std::vector<Curvedata>  m_curves_data;
    std::vector<QColor>     m_color;
    size_t                  m_color_index;
};

#endif // STABLEPLOTVIEW_H
