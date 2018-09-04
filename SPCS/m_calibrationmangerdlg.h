#ifndef M_CALIBRATIONMANGERDLG_H
#define M_CALIBRATIONMANGERDLG_H

#include <QDialog>
#include "m_calmanager.h"
#include <QMessageBox>
#include <QFileDialog>
#include<QListWidgetItem>
#include "_global.h"

namespace Ui {
class M_CalibrationMangerdlg;
}
using namespace CVTS;

enum CURRENT_TABLE
{BASE,USER,NON};

/*!
 * \brief The M_CalibrationMangerdlg class
 * 校准库管理类
 *
 */
class M_CalibrationMangerdlg : public QDialog
{
    Q_OBJECT
protected:
    explicit M_CalibrationMangerdlg(QWidget *parent = 0);
    ~M_CalibrationMangerdlg();
public:
    static M_CalibrationMangerdlg* instance()
    {
        static M_CalibrationMangerdlg *cal = new M_CalibrationMangerdlg();
        return cal;
    }
    static void destory()
    {
        delete instance();
    }
//    QString &get_current_calfile();
    void reset();
    void init();
    void init_lineedit();
private slots:
//    void on_pushButton_clicked();//添加
//    void on_pushButton_2_clicked();//删除
//    void on_pushButton_3_clicked();//确定
//    void on_pushButton_4_clicked();//取消
//    void on_listWidget_base_doubleClicked(const QModelIndex &index);
//    void on_listWidget_user_doubleClicked(const QModelIndex &index);
//    void update_baselibs(QList<QString> &list_item, bool add_);
//    void add_user_item();
//    void add_base_item();
//    void on_listWidget_base_itemPressed(QListWidgetItem *item);
//    void on_listWidget_user_itemPressed(QListWidgetItem *item);

    void get_exist_file(QLineEdit *edit);

    void   files_isnot_exist(QString filename = "");

    void   note_sucess();

    bool repeat_file(QString new_path, QString name, bool flag = true, bool isnote = true);

    void on_pushButton_t_all_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_s1_clicked();

    void on_pushButton_s2_clicked();

    void on_pushButton_s3_clicked();

    void on_pushButton_s4_clicked();

    void on_pushButton_s5_clicked();

    void on_pushButton_s6_clicked();

    void on_pushButton_s7_clicked();

    void on_pushButton_s8_clicked();

    void on_pushButton_s9_clicked();

    void on_pushButton_s10_clicked();

    void on_pushButton_s11_clicked();

    void on_pushButton_s12_clicked();

    void on_pushButton_s13_clicked();

    void on_pushButton_s14_clicked();

    void on_pushButton_s15_clicked();

    void on_pushButton_s16_clicked();

    void on_pushButton_t1_clicked();

    void on_pushButton_t2_clicked();

    void on_pushButton_t3_clicked();

    void on_pushButton_t4_clicked();

    void on_pushButton_t5_clicked();

    void on_pushButton_t6_clicked();

    void on_pushButton_t7_clicked();

    void on_pushButton_t8_clicked();

    void on_pushButton_t9_clicked();

    void on_pushButton_t10_clicked();

    void on_pushButton_t11_clicked();

    void on_pushButton_t12_clicked();

    void on_pushButton_t13_clicked();

    void on_pushButton_t14_clicked();

    void on_pushButton_t15_clicked();

    void on_pushButton_t16_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_rest_org_clicked();

    void on_pushButton_s1_2_clicked();

    void on_pushButton_s2_2_clicked();

    void on_pushButton_s3_2_clicked();

    void on_pushButton_s4_2_clicked();

    void on_pushButton_s5_2_clicked();

    void on_pushButton_s6_2_clicked();

    void on_pushButton_s7_2_clicked();

    void on_pushButton_s8_2_clicked();

    void on_pushButton_s9_2_clicked();

    void on_pushButton_s10_2_clicked();

    void on_pushButton_s11_2_clicked();

    void on_pushButton_s12_2_clicked();

    void on_pushButton_s13_2_clicked();

    void on_pushButton_s14_2_clicked();

    void on_pushButton_s15_2_clicked();

    void on_pushButton_s16_2_clicked();

private:
    Ui::M_CalibrationMangerdlg *ui;
  //  QString m_select_calfile_path;
  //  CURRENT_TABLE current_tab;

    std::map<int,QLineEdit *> m_lineedits_match;
     std::map<int,QLineEdit *> m_lineedits_short;

};

#endif // M_CALIBRATIONMANGERDLG_H
