#ifndef M_DAMPINGDLG_H
#define M_DAMPINGDLG_H

#include <QDialog>
#include "_global.h"

namespace Ui {
class M_Dampingdlg;
}
using namespace CVTS;


/*!
 * \brief The M_Dampingdlg class
 * 衰减器控制界面，目前没有使用
 */
class M_Dampingdlg : public QDialog
{
    Q_OBJECT
    
protected:
    explicit M_Dampingdlg(QWidget *parent = 0);
    ~M_Dampingdlg();
public:
    static M_Dampingdlg* instance()
    {
        static M_Dampingdlg *damp = new M_Dampingdlg();
        return damp;
    }
    static void destory()
    {
        delete instance();
    }
    void reset();
    void init();
    int get_dampling();
    void attenuation(CVTS::NI_ANTENNA na);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::M_Dampingdlg                         *ui;
    AN_Map                                   m_map_damping;
};

#endif // M_DAMPINGDLG_H
