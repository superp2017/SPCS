#ifndef M_SETDEV_H
#define M_SETDEV_H

#include <QWidget>
#include <QDialog>
#include "powerate.h"
#include <QTableWidget>

namespace Ui {
class M_SetDev;
}


/*!
 * \brief The M_SetDev class
 * 硬件参数控制类，主要控制失网和衰减器
 */
class M_SetDev : public QDialog
{
    Q_OBJECT
    
protected:
    explicit M_SetDev(QWidget *parent = 0);
    ~M_SetDev();
public:
    static M_SetDev* instance()
    {
        static M_SetDev *dev = new M_SetDev;
        return dev;
    }
    static void  destory()
    {
        delete instance();
    }

    int  get_attan()            {return m_attan;}
    void get_PNA_set(QString &IF, QString &power, QString &sweeptime);
    void set_parame(QString IF,QString power,QString sweeptime,QString an);
    void init();

private:
    void update_table();
public slots:
    void sendstatus(bool isent);
private slots:
    void on_pushButton_default_clicked();
    void on_pushButto_OK_clicked();
    void on_pushButton_pulse_clicked();

    void on_pushButto_apply_clicked();

    void on_toolButton_clicked();

    void on_lineEdit_power_editingFinished();

    void on_lineEdit_power_textChanged(const QString &arg1);

private:
    Ui::M_SetDev *ui;
    int m_attan;
    Powerate        m_powerate;
    QTableWidget    m_table_widget;
};

#endif // M_SETDEV_H
