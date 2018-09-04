#ifndef M_CFG_STATUS_DLG_H
#define M_CFG_STATUS_DLG_H

#include <QDialog>
#include "_global.h"
#include "m_cfg_status_thread.h"
using namespace CVTS;

namespace Ui {
class m_cfg_status_dlg;
}

/*!
 * \brief The m_cfg_status_dlg class
 * 人工修改校准基准值界面
 */
class m_cfg_status_dlg : public QDialog
{
    Q_OBJECT
    
protected:
    m_cfg_status_dlg(QWidget *parent = 0);
    ~m_cfg_status_dlg();
public:
    static m_cfg_status_dlg * instance()
    {
        static m_cfg_status_dlg *dlg = new m_cfg_status_dlg();
        return dlg;
    }
    static void destory()
    {
        delete instance();
    }
    std::map<QString,std::pair<double,double> > & get_base_mp();
    Task_Cmp&get_org_cal()             {return m_cal_data;}
    void init_data(Task_Cmp &p_cmp, Task_Cmp &p_cmp_1,std::vector<QString> pfreqs,\
                   std::map<int,double>  &p_delt_data,double &p_delt_db,\
                   std::map<QString, std::pair<double, double> > &p_base_mp,\
                   std::vector<int> &p_id);
    void calc_magn();
    void calc_phase();
signals:
    void calc(bool ismagn);
    void note(double rate,QString freq);
    void note_2(double rate,QString freq);
private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_calc_db_clicked();
    void calc_delt_rate(double value);
    void on_pushButton_calc_phase_clicked();
    void note_empty();
    bool check_status(double ismagn, double &rate);
    void note_success(double rate, QString freq);
    void note_cur_rate(double rate, QString freq);

    void on_radioButton_rate_clicked();

    void on_radioButton_value_clicked();
    void calc_valuse(QString &pfreq);
    void calc_ave();
    void update_rate();
    void update_add_delt_rate(double value, double rate);

    void on_pushButton_recalc_clicked();
    double calc_base(QString cur_freq, double db);
    void  reCalc_cal(QString cur_freq, double value);

private:
    Ui::m_cfg_status_dlg *ui;
    std::map<QString,std::pair<double,double> > m_base_data;
    Task_Cmp                                    m_cal_data;
    Task_Cmp                                    m_cal_mp_1;
    double                                      m_nums;
    double                                      m_step;
    double                                      m_values;
    QString                                     m_cur_freq;
    m_CFG_STATUS_THread                         m_thread;
    std::map<QString,std::pair<double,double> > m_cal_minmax;
    std::map<QString,double>                    m_cal_ave;
    std::map<int,double>                        m_delt_data;
    double                                      m_add_db;
    double                                      m_cur_add_db;
    std::vector<int>                            m_id;
    std::vector<QString>                        m_freqs;

};

#endif // M_CFG_STATUS_DLG_H
