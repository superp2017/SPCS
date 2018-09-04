#ifndef M_SETFREQDLG_H
#define M_SETFREQDLG_H

#include <QDialog>
#include<QString>
#include <vector>
#include<QTableWidgetItem>
#include "_global.h"
#include <QDebug>
#include <QMessageBox>
#include "statusoutput.h"
#include <QFileDialog>

namespace Ui {
class M_SetFreqdlg;
}
using namespace CVTS;

class Compare_freq
{
public:
    bool operator()(const QString &L_, const QString &R_)
    {
        double ls_R = R_.toDouble();
        double ls_L = L_.toDouble();
        return ls_L < ls_R;
    }
};

/*!
 * \brief The M_SetFreqdlg class
 * ÆµÂÊÉèÖÃÀà
 */

class M_SetFreqdlg : public QDialog
{
    Q_OBJECT
protected:
    explicit M_SetFreqdlg(QWidget *parent = 0);
    ~M_SetFreqdlg();
public:
    static M_SetFreqdlg* instance()
    {
        static M_SetFreqdlg *freq = new M_SetFreqdlg();
        return freq;
    }
    static void destory()
    {
        delete instance();
    }
    void reset();
    void init();
    std::vector<QString>& get_freq();
    QString get_freq_step();
    void setfreq(VNA_SWEEP_TYPE type,double start = 0,double end =0,QString step = "3");
    void setfreq(VNA_SWEEP_TYPE type,std::vector<QString> &freq);
private slots:
    void init_item();
    void init_type();
    void init_data();
    void init_tablewidget();
    bool Calculate_freq();
    void display_freq();
    void form_hide();
    void form_expand();
    bool update_freq();
    void set_single_point_freq();
    void remove_all();
    void AllItemAlignment( int row_);
    void on_radioButton_single_clicked();
    void on_radioButton_range_clicked();
    void on_pushButton_OK_clicked();
    void on_pushButton_cancel_clicked();
    void on_pushButton_expand_clicked();
    void on_pushButton_update_clicked();
    void update_outstatus_freq();
    void sort_freqs();
    void range();
    void single();
    void ParsefreqList(QString filename);
    bool parse(QString p_path);
    void on_pushButton_load_clicked();

    void on_radioButton_load_clicked();

private:
    Ui::M_SetFreqdlg        *ui;
    std::vector<QString>    m_freq;
    bool                    expand;
    bool                    m_init;

};

#endif // M_SETFREQDLG_H
