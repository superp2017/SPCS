#ifndef M_SELECTGALLERYDLG_H
#define M_SELECTGALLERYDLG_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class M_SelectGallerydlg;
}


/*!
 * \brief The M_SelectGallerydlg class
 * 多路开关控制界面
 */
class M_SelectGallerydlg : public QDialog
{
    Q_OBJECT
    
protected:
    explicit M_SelectGallerydlg(QWidget *parent = 0);
    ~M_SelectGallerydlg();
public:
    static M_SelectGallerydlg *instance()
    {
        static M_SelectGallerydlg * dlg = new M_SelectGallerydlg();
        return dlg;
    }
    static void destory()
    {
        delete instance();
    }
public slots:
    void init();
    void open_port(int index);
    void reset();
    int CheckStatus();
    int  &get_port();
    void close_all();
private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::M_SelectGallerydlg       *ui;
    std::vector<QRadioButton *>   m_radio;
    int                           m_checked;
};

#endif // M_SELECTGALLERYDLG_H
