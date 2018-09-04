#ifndef M_TESTINITDLG_H
#define M_TESTINITDLG_H

#include <QDialog>
#include "_global.h"
#include <QString>
#include <QFile>
#include <QMessageBox>

using namespace CVTS;
namespace Ui {
class M_TestInitDlg;
}
/*!
 * \brief The M_TestInitDlg class
 * 测试初始化界面
 */
class M_TestInitDlg : public QDialog
{
    Q_OBJECT
    
protected:
    explicit M_TestInitDlg(QWidget *parent = 0);
    ~M_TestInitDlg();
public:
    static M_TestInitDlg* instance()
    {
        static  M_TestInitDlg * init = new M_TestInitDlg();
        return init;
    }
    static void destroy()
    {
        delete  instance();
    }

    void reset();
    void init();
    void get_param(TEST_TYPE &type, WORK_STATUS &status,QString &caltable);
    void set_test_type(TEST_TYPE type);
    void set_work_status(WORK_STATUS status);
    void set_cfg_table(QString table);
signals:
    void Pulse(bool isenable);
private slots:
    void on_m_OK_clicked();
    void on_n_cancel_clicked();
    void on_radioButton_filed_test_clicked();
    void on_radioButton_phase_test_clicked();
    void init_test_job();
    void init_workstatue();
    void enablePulse();
    void on_pushButton_manu_test_clicked();
    void on_pushButton_select_cfg_table_clicked();

private:
    Ui::M_TestInitDlg *ui;
};

#endif // M_TESTINITDLG_H
