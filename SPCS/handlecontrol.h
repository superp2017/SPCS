#ifndef HANDLECONTROL_H
#define HANDLECONTROL_H

#include <QtWidgets>
#include "cparsefile.h"
#include "m_toolsthread.h"

namespace Ui {
class HandleControl;
}


/*!
 * \brief The HandleControl class
 * 集成的控制界面
 */
class HandleControl : public QWidget
{
    Q_OBJECT

protected:
    explicit HandleControl(QWidget *parent = 0);
    ~HandleControl();
public:
    static HandleControl* instance()
    {
        static HandleControl* handle = new HandleControl;
        return handle;
    }
    static void destory()
    {
        delete instance();
    }

    void cal_test();
    void stable_test();
private slots:

    void on_pushButton_default_vna_clicked();

    void on_pushButtonapply_clicked();

    void on_pushButton_open_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_move_0_clicked();

    void on_pushButton_query_clicked();

    void on_pushButton_move_clicked();

    void on_pushButton_connect_clicked();

    void on_pushButton_init_clicked();

    void on_pushButton_down_clicked();

    void on_pushButton_wave_control_clicked();

    void ID_or_RowCol();

    void Dis_or_Pos();

    void checkout_multi_switch();

    void on_pushButton_closeall_clicked();

    void on_radioButton_close_all_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void ElecSwitch_setCurrentStatus(QPushButton * button,int id);

    void on_checkBox_pulse_2_clicked();

    void on_checkBox_path0_2_clicked();

    void on_checkBox_path1_2_clicked();

    void on_checkBox_path2_2_clicked();

    void on_checkBox_path3_2_clicked();

    void on_checkBox_path4_2_clicked();

    void on_pushButton_ATTAN_apply_clicked();

    void on_pushButtonwave_default_clicked();

    void on_pushButton_paulse_clicked();

    void on_pushButton_vna_reset_clicked();

    void on_pushButton_seclect_clicked();

    void on_pushButton_collect_clicked();

    void on_pushButton_update_trace_clicked();

    void on_pushButton_stop_test_clicked();

    void changedecstatus(int dec);
    void on_pushButton_reconnect_clicked();

    void on_radioButton_stable_clicked();


    void on_radioButton_caltest_clicked();

    void on_pushButton_manual_clicked();

    void on_pushButton_interal_clicked();

signals:
    void test(bool iscal);
    void stop_test();
    void close_allDEC();
    void change_status(int dec);
protected:
    void init_elec_switch();
    void init_multi_switch();
    void init_connect();
    void init_data();
    void default_wave();
    void default_sweepshelf();
    void calc_freq();
    void vna_connect_failed();
    void get_comm_test_parame();

    void get_stable_test_parame();

public slots:
    void Testend();

private:
    Ui::HandleControl *ui;
    std::map<int,QRadioButton *>    m_multi_switch;
    std::map<int,QPushButton * >    m_elec_switch;
    std::map<int,bool >             m_elec_switch_status;
    CParsefile                      m_parse;
    std::vector<QString>            m_freq;
    int                             m_collect_nums;
    QString                         m_23_path;
    QString                         m_0_path;
    QString                         m_cal_path;
    QString                         m_collect_path;

    int                             m_cur_dec_num;
    bool                            m_isdec_click;
    double                          m_wait_times;
    bool                            m_isdiffer;
    M_ToolsThread                   m_thread;
    bool                             m_iscontinue;
    double                          m_switch_time;
};

#endif // HANDLECONTROL_H
