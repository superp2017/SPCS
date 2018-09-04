#ifndef PORTCHANGE_H
#define PORTCHANGE_H

#include <QtWidgets>
#include <map>
#include "_global.h"
using namespace CVTS;

namespace Ui {
class PortChange;
}

typedef struct _CHAGE
{
    std::vector<QString> t_freq;
    int                  t_cur_row;
    std::map<QString,std::pair<double,double> > t_s11_match;
    std::map<QString,std::pair<double,double> > t_s11_short;
    std::map<QString,std::pair<double,double> > t_s21_test;
    std::map<QString,std::pair<double,double> > t_s21_calc;
}CHAGE;


/////通道转化界面
class PortChange : public QWidget
{
    Q_OBJECT

protected:
    explicit PortChange(QWidget *parent = 0);
    ~PortChange();
public:
    static PortChange* instance()
    {
        static PortChange * c = new PortChange();
        return c;
    }
    static void destory()
    {
        delete instance();
    }
        void testS11();
signals:
    void test();


private slots:
    void on_pushButton_compare_clicked();
    void init_ui();
    void on_pushButton_clicked();
    void calc_freq();

    void init_tablewidget(QTableWidget *tab, int prow, int value);
    void set_compare_widget();
    void update_tableWidget();

    void on_pushButton_clear_clicked();

private:
    Ui::PortChange *ui;
    std::vector<QString>    m_freqs;
    std::map<int,CHAGE>     m_test_data;
    int                     m_cur_elec;
    int                     m_changePhase;
    int                     m_cur_row;
    double                  m_power;
    double                  m_if;
    bool                    m_changeVNA;
    WORK_STATUS             m_work_status;
};

#endif // PORTCHANGE_H
