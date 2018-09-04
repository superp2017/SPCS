#ifndef TPLOTVIEW_H
#define TPLOTVIEW_H

#include <QtWidgets>
#include "tplot.h"
#include "_global.h"
using namespace CVTS;
enum Chart{M_ONE, M_TWO,M_NONE = -1};

#define MAGNAME  CVTS::GBKToUnicode::toUnicode("幅度  ")
#define PHANAME  CVTS::GBKToUnicode::toUnicode("相位  ")
#define UNITNAME CVTS::GBKToUnicode::toUnicode("阵元编号:")
#define MAG      MAGNAME +UNITNAME + QString("%1").arg(m_cur_unit_id)
#define PHA      PHANAME +UNITNAME + QString("%1").arg(m_cur_unit_id)

typedef struct _MonitorChart
{
    Chart                       t_num;
    std::vector<TPlot*>         t_plots;
    _MonitorChart()
    {
        t_num = M_NONE;
    }
    void reset()
    {
        std::vector<TPlot*>::iterator ls_iter = t_plots.begin();

        while(ls_iter != t_plots.end())
        {
            (*ls_iter)->clean();
            ls_iter++;
        }
        t_num = M_NONE;
    }
    void reset_curve()
    {
        std::vector<TPlot*>::iterator ls_iter = t_plots.begin();

        while(ls_iter != t_plots.end())
        {
            (*ls_iter)->reset_curve();
            ls_iter++;
        }
        t_num = M_NONE;
    }
    void del()
    {
        std::vector<TPlot*>::iterator ls_iter = t_plots.begin();

        while(ls_iter != t_plots.end())
        {
            delete *ls_iter;
            ls_iter++;
        }
        t_plots.clear();
        t_num = M_NONE;
    }

}MonitorChart;


class TPlotView : public QWidget
{
    Q_OBJECT
public:
    explicit TPlotView(QWidget *parent = 0);
signals:
protected:
    void init();
    void clean();
    void show_chart(MonitorChart &p_charts);
    void show_two_chart();
public slots:
    void UpdateData(int _ID, double freq_, double _M, double _P);
private:
    QVBoxLayout             m_Layout;
    MonitorChart            m_charts;
    int                     m_cur_wnd;
    int                     m_cur_unit_id;
    
};

#endif // TPLOTVIEW_H
