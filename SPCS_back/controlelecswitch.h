#ifndef CONTROLELECSWITCH_H
#define CONTROLELECSWITCH_H

#include <QWidget>
#include "_global.h"
#include <QPushButton>

namespace Ui {
class ControlElecSwitch;
}

/*!
 * \brief The ControlElecSwitch class
 * 电子开关单独的控制界面
 */

class ControlElecSwitch : public QWidget
{
    Q_OBJECT
    
protected:
    explicit ControlElecSwitch(QWidget *parent = 0);
    ~ControlElecSwitch();
public :
    static  ControlElecSwitch* instance()
    {
        static ControlElecSwitch* ele = new ControlElecSwitch();
        return ele;
    }
    static void destory()
    {
        delete instance();
    }

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

    void on_pushButton5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_close_clicked();
    void on_pushButton_17_clicked();

protected:
    void    StatusChange(bool isopen);
    QString status(int i, bool &res);
    void    setCurrentStatus(QPushButton * button,int id);
private:
    Ui::ControlElecSwitch      *ui;
    std::map<int,bool>         m_button_status;
    std::map<int,QPushButton *> m_buttons;
};

#endif // CONTROLELECSWITCH_H
