#ifndef M_SETPULSE_H
#define M_SETPULSE_H

#include <QWidget>

namespace Ui {
class M_SetPulse;
}
/*!
 * \brief The M_SetPulse class
 * ßÕ¯¬ˆ≥ÂΩÁ√Ê¿‡
 */
class M_SetPulse : public QWidget
{
    Q_OBJECT

protected:
    explicit M_SetPulse(QWidget *parent = 0);
    ~M_SetPulse();
public:
    static M_SetPulse *instance()
    {
        static M_SetPulse *pulse  = new M_SetPulse;
        return pulse;
    }
    static void destory()
    {
        delete instance();
    }
    void dosetting();
    void default_setting();
    void get_param(bool& isenable,QString &period\
                   ,bool &pulse0,QString &pulse0_wi,QString &pulse0_de\
                   ,bool &pulse1,QString &pulse1_wi,QString &pulse1_de\
                   ,bool &pulse2,QString &pulse2_wi,QString &pulse2_de\
                   ,bool &pulse3,QString &pulse3_wi,QString &pulse3_de\
                   ,bool &pulse4,QString &pulse4_wi,QString &pulse4_de);
    void Relad_Parame(bool isenable,QString period\
                      ,bool pulse0,QString pulse0_wi,QString pulse0_de\
                      ,bool pulse1,QString pulse1_wi,QString pulse1_de\
                      ,bool pulse2,QString pulse2_wi,QString pulse2_de\
                      ,bool pulse3,QString pulse3_wi,QString pulse3_de\
                      ,bool pulse4,QString pulse4_wi,QString pulse4_de);
private slots:
    void  enablePulse(bool enable);

    void on_pushButton_default_2_clicked();

    void on_checkBox_path1_2_clicked();

    void on_checkBox_path2_2_clicked();

    void on_checkBox_path3_2_clicked();

    void on_checkBox_path4_2_clicked();

    void on_checkBox_pulse_2_clicked();


    void on_pushButtonapply_clicked();


    void on_pushButton_ok_2_clicked();

private:
    Ui::M_SetPulse *ui;
};

#endif // M_SETPULSE_H
