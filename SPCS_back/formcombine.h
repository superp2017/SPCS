#ifndef FORMCOMBINE_H
#define FORMCOMBINE_H

#include <QWidget>

namespace Ui {
class FormCombine;
}

class FormCombine : public QWidget
{
    Q_OBJECT

public:
    explicit FormCombine(QWidget *parent = 0);
    ~FormCombine();
    QString get_file();

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::FormCombine *ui;
};

#endif // FORMCOMBINE_H
