#ifndef M_SETPNADLG_H
#define M_SETPNADLG_H

#include <QDialog>
#include "_global.h"
using namespace CVTS;
#include <QDebug>
#include "m_settrigsingal.h"
namespace Ui {
class M_SetPNAdlg;
}
/*!
 * \brief The M_SetPNAdlg class
 * 失网单独控制界面，目前已经不适用
 */

class M_SetPNAdlg : public QDialog
{
    Q_OBJECT
    
protected:
    explicit M_SetPNAdlg(QWidget *parent = 0);
    ~M_SetPNAdlg();
public:
    static M_SetPNAdlg*instance()
    {
        static M_SetPNAdlg *pna = new M_SetPNAdlg();
        return pna;
    }
    static void destory()
    {
        delete instance();
    }
    void reset();
    void init();
    QString &get_param(VNA_SWEEP_TYPE &t_type);
    void     set_sweep_type(VNA_SWEEP_TYPE type);
    void     set_freq_bandwidth(QString width);
    void     set_send_power(QString db);
    void     set_collect_continue_time(QString time);
    void     set_collect_step_time(double time);
public slots:
    void  range_click();
    void  single_clicK();
signals:
    void  range();
    void  single();
private slots:
    void on_pushButton_clicked();
    void fill_param();

    void on_pushButton_adv_clicked();

private:
    Ui::M_SetPNAdlg *ui;
    QString m_pna;
};

#endif // M_SETPNADLG_H
