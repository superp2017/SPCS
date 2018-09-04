#ifndef CONTROLWAVE_H
#define CONTROLWAVE_H

#include <QDialog>

namespace Ui {
class ControlWave;
}
/*!
 * \brief The ControlWave class
 * 波控分机的单独控制界面
 *
 */
class ControlWave : public QDialog
{
    Q_OBJECT
    
protected:
    explicit ControlWave(QWidget *parent = 0);
    ~ControlWave();
  public:
    static ControlWave* instance()
    {
        static ControlWave * control = new ControlWave;
        return control;
    }
    static void destory()
    {
        delete instance();
    }
private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_control_clicked();

    void on_pushButton_down_clicked();

    void on_pushButton_connecttest_clicked();

    void on_pushButton_attaninit_2_clicked();

    void on_pushButton_default_clicked();




private:
    Ui::ControlWave *ui;
};

#endif // CONTROLWAVE_H
