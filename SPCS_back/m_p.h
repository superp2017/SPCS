#ifndef M_P_H
#define M_P_H

#include <QWidget>
#include "_global.h"
using namespace CVTS;
namespace Ui {
class M_P;
}

class M_P : public QWidget
{
    Q_OBJECT


protected:
    explicit M_P(QWidget *parent = 0);
    ~M_P();
    
public :
    static M_P * instance()
    {
        static M_P* mp = new M_P;
        return mp;
    }
    static  void destory()
    {
        delete instance();
    }
    void test();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::M_P *ui;
    bool      m_continue;
};

#endif // M_P_H
