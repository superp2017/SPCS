#ifndef HGENARRAY_H
#define HGENARRAY_H

#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include "hrectanglearray.h"
#include "htrianglearray.h"
#include "hgridcirclearray.h"
#include "hplanecirclearray.h"
#include <QDebug>
#include "_global.h"
using namespace  CVTS;
namespace Ui {
class HGenArray;
}

class HGenArray : public QDialog
{
    Q_OBJECT
    
public:
    explicit HGenArray(QWidget *parent = 0);
    ~HGenArray();


private slots:
    void init();
    void init_data();
    void init_type();
    void init_array();
    bool check_value();
    bool check_rect();
    bool check_trigle();
    bool check_circle_plane();
    bool check_circle_grid();
    bool input_error();
    bool creat_rect_array();
    bool creat_trigle_array();
    bool creat_circle_plane();
    bool creat_circle_grid();
    bool creat_array(HArray * array);
    void data_clear();
    void on_radioButton_rect_2_clicked();
    void on_radioButton_trigle_2_clicked();
    void on_radioButton_circle_plane_2_clicked();
    void on_radioButton__circle_grid_2_clicked();
    void on_pushButton_ok_clicked();
    void on_pushButton_cancle_clicked();
    void get_coordinate(std::map<int,QString>&radar_coordinate,QString offset);
    bool out_range(QString text,QString information);
    void closeEvent(QCloseEvent *e);
private:
    Ui::HGenArray *ui;
    QString m_offset;
    QString m_path;
    std::map<int,QString>  m_radar_coordinate;
};

#endif // HGENARRAY_H
