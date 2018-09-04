#ifndef M_SETTRIGSINGAL_H
#define M_SETTRIGSINGAL_H

#include <QDialog>
#include <QWidget>


namespace Ui {
class M_SetTrigSingal;
}

class M_SetTrigSingal : public QWidget
{
    Q_OBJECT
    
protected:
    explicit M_SetTrigSingal(QWidget *parent = 0);
    ~M_SetTrigSingal();
 public:
    static M_SetTrigSingal *instance()
    {
        static M_SetTrigSingal *pulse  = new M_SetTrigSingal;
        return pulse;
    }
    static void destory()
    {
        delete instance();
    }
    void dosetting();
private slots:
    void on_pushButton_default_clicked();

    void on_checkBox_path1_clicked();

    void on_checkBox_path3_clicked();

    void on_checkBox_path4_clicked();

    void on_checkBox_path2_clicked();

    void on_checkBox_pulse_clicked();
    void default_setting();

    void on_pushButton_ok_clicked();
    void  enablePulse(bool enable);

private:
    Ui::M_SetTrigSingal *ui;
};

#endif // M_SETTRIGSINGAL_H
