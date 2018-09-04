#ifndef M_SET_TIMES_H
#define M_SET_TIMES_H

#include <QDialog>

namespace Ui {
class M_Set_Times;
}


/*!
 * \brief The M_Set_Times class
 * 测试时间、流程控制界面，测试前的最后一个设置界面
 */
class M_Set_Times : public QDialog
{
    Q_OBJECT
    
protected:
    explicit M_Set_Times(QWidget *parent = 0);
    ~M_Set_Times();
  public:
    static M_Set_Times *instance()
    {
        static M_Set_Times * times = new M_Set_Times;
        return times;
    }
    static void destory()
    {
        delete instance();
    }
    void init();
    void reload_param(QString wave, QString mule, QString eles, QString sweep, QString mp_time, QString m_mp_times);
    void get_param(QString &wave, QString &mule, QString &eles, QString &sweep, QString &cfgmp_times, QString &m_mp_time, QString &pdelt_base_db);
private slots:
    void on_pushButton_default_clicked();

    void on_pushButtonload_clicked();

    void on_pushButton_ok_clicked();

    void on_pushButtonload_2_clicked();

private:
    Ui::M_Set_Times *ui;
};

#endif // M_SET_TIMES_H
