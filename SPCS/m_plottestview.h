#ifndef M_PLOTTESTVIEW_H
#define M_PLOTTESTVIEW_H

#include <QWidget>
#include "m_cvts_plot.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include "m_parsecurvedata.h"
#include <set>
#include <QDateTime>

enum ChartNum{C_ONE, C_TWO, C_FOUR, C_EIGHT, C_SIXTEEN, C_NONE = -1};

typedef struct _CVTSChart
{
    ChartNum                    t_num;
    std::vector<M_CVTS_Plot*>    t_plots;
    _CVTSChart()
    {
        t_num = C_NONE;
    }
    void reset()
    {
        std::vector<M_CVTS_Plot*>::iterator ls_iter = t_plots.begin();

        while(ls_iter != t_plots.end())
        {
            (*ls_iter)->clean();
            ls_iter++;
        }
        t_num = C_NONE;
    }
    void del()
    {
        std::vector<M_CVTS_Plot*>::iterator ls_iter = t_plots.begin();

        while(ls_iter != t_plots.end())
        {
            delete *ls_iter;
            ls_iter++;
        }
        t_plots.clear();
        t_num = C_NONE;
    }

}CVTSChart;

/*!
 * \brief The M_PlotTestView class
 * plot 显示类 用来加载多个plot
 */
class M_PlotTestView : public QWidget
{
    Q_OBJECT
protected:
    M_PlotTestView(QWidget *parent = 0);
    ~M_PlotTestView();
public:
    static  M_PlotTestView* instance()
    {
        static M_PlotTestView * view = new M_PlotTestView();
        return view;
    }
    static void  destory()
    {
        delete instance();
    }

    void del();
    void init();
    void reset();
    bool creat_curve(Curvedata &p_data, bool ishowmagn = true);
    void export_curve_data(std::vector<QString> p_id,bool isdb,bool is360 ,QWidget *w=0);
public slots:
    void show_chart(CVTSChart &p_charts);
    void show_magn_chart();
    void show_two_chart();
    void show_phase_chart();
    void data_clear();
    void view_reset();
    void IdToRC(int id, short &row, short &col);
signals:
    void plot_import();

protected:
    QWidget*                m_main_widget;
    QVBoxLayout             m_Layout;
    CVTSChart               m_charts;
    int                     m_cur_wnd;
    std::vector<Curvedata>  m_curves_data;
    std::vector<QColor>     m_color;
    size_t                  m_color_index;
};

#endif // M_PLOTTESTVIEW_H
