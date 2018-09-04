#ifndef HTESTINIT_H
#define HTESTINIT_H

#include <QDialog>
#include<QString>
#include <QFile>
#include <QMessageBox>
#include "_global.h"

using namespace CVTS;
namespace Ui {
class HTestInit;
}


class HTestInit : public QDialog
{
    Q_OBJECT
    
protected:
    explicit HTestInit(QWidget *parent = 0);
    ~HTestInit();
public:
    static HTestInit* instance()
    {
      static  HTestInit init;
        return &init;
    }
    static void destroy()
    {
        delete  instance();
    }
private slots:
    void on_m_OK_clicked();
    void init();
    void init_test_job();
    void init_workstatue();
    void on_radioButton_filed_test_clicked();
    void on_radioButton_phase_test_clicked();
    void on_n_cancel_clicked();
private:
    Ui::HTestInit *ui;
};

#endif // HTESTINIT_H
