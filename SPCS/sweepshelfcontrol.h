#ifndef SWEEPSHELFCONTROL_H
#define SWEEPSHELFCONTROL_H

#include <QWidget>

namespace Ui {
class SweepShelfControl;
}

/*!
 * \brief The SweepShelfControl class
 * …®√Ëº‹µ•∂¿øÿ÷∆¿‡
 */

class SweepShelfControl : public QWidget
{
    Q_OBJECT
    
public:
    explicit SweepShelfControl(QWidget *parent = 0);
    ~SweepShelfControl();
    
private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_org_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_move_clicked();

    void on_radioButton_dis_clicked();

    void on_radioButton_loca_clicked();
    void disableMove(bool enable);

    void on_pushButtonquery_clicked();

private:
    Ui::SweepShelfControl *ui;
};

#endif // SWEEPSHELFCONTROL_H
