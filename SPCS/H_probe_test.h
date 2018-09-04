#ifndef H_PROBE_TEST_H
#define H_PROBE_TEST_H

#include <QWidget>
#include <QThread>
#include <map>
#include <QString>
#include <QTextStream>
#include <QCheckBox>

namespace Ui {
class H_probe_test;
}
///电子开关测试工具
class H_probe_test : public QWidget
{
    Q_OBJECT

public:
    explicit H_probe_test(QWidget *parent = 0);
    ~H_probe_test();
    void test();

private slots:
    void on_pushButton_vna_reset_clicked();

    void on_pushButtonapply_clicked();

    void on_pushButton_update_trace_clicked();

    void on_pushButton_select_path_clicked();
    void init();
    void calc_freq();

    void on_pushButton_test_clicked();

    void on_pushButton_manual_clicked();

    void on_pushButton_interal_clicked();
    void collect_S22(QTextStream &out);
    void collect_data(QTextStream &out);
    void end_test();
    void update_cur_pos(int value);
    void on_groupBox_4_clicked();
    void push_checkbox();
    void getCheckStatus();

signals:
    void begin_test();
    void test_finshed();
    void cur_pos(int index);
private:

    Ui::H_probe_test *ui;
    std::vector<QString>            m_freq;
    QMap<int,bool>                  m_elec;
    QVector<QCheckBox*>             m_checkbox;
    double                          m_sleep_time;
    double                          m_wait_times;
    double                          m_collect_nums;
    double                          m_switch_time;
    QString                         m_save_path;
    bool                            m_s11;
    bool                            m_s22;
    bool                            m_s21;
    bool                            m_s12;
    bool                            m_is_ele_switch;


};

#endif // H_PROBE_TEST_H
