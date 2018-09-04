#ifndef CALDIFFERCONTROLPANE_H
#define CALDIFFERCONTROLPANE_H

#include <QWidget>

namespace Ui {
class CalDifferControlPane;
}
/*!
 * \brief The CalDifferControlPane class
 * 数据比较界面的控制界面
 */
class CalDifferControlPane : public QWidget
{
    Q_OBJECT
    
public:
    explicit CalDifferControlPane(QWidget *parent = 0);
    ~CalDifferControlPane();
signals:
    void compare(QString path1,QString path2);
    void add_curve(QString  path);
    void add_s2p(QString path);
    void clear_view();
private slots:
    void on_pushButton_file1_clicked();
    void on_pushButton_file2_clicked();
    void on_pushButton_cpmpare_clicked();
    QString get_files();
    void file_not_exist();

    void on_pushButton_file3_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_clicked();

    void on_pushButton_file3_S2P_clicked();

    void on_pushButton_add_s2p_clicked();

private:
    Ui::CalDifferControlPane *ui;
};

#endif // CALDIFFERCONTROLPANE_H
