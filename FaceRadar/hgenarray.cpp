#include "hgenarray.h"
#include "ui_hgenarray.h"

HGenArray::HGenArray(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HGenArray)
{
    ui->setupUi(this);
    init();
//    QString ls_sheet = QString::fromUtf8("font: 11pt \"\346\245\267\344\275\223\";");

//    this->setStyleSheet(ls_sheet);
}

HGenArray::~HGenArray()
{
    delete ui;
}

void HGenArray::init()
{
    init_array();
    init_type();
    init_data();
}

void HGenArray::init_type()
{
    ui->lineEdit_circle_num_grid_2->setValidator(new QIntValidator(0.0, 100000000000.0, this));
    ui->lineEdit_circle_r_plane_2->setValidator(new QDoubleValidator(0.0, 100000000000.0,5, this));
    ui->lineEdit_radial_range_2->setValidator(new QDoubleValidator(0.0, 100000000000.0, 5, this));
    ui->lineEdit_x_num_rect_2->setValidator(new QIntValidator(0.0, 100000000000.0, this));
    ui->lineEdit_x_num_trigle_2->setValidator(new QIntValidator(0.0, 100000000000.0, this));
    ui->lineEdit_x_range_plane_2->setValidator(new QDoubleValidator(0.0, 100000000000.0, 5, this));
    ui->lineEdit_x_range_rect_2->setValidator(new QDoubleValidator(0.0, 100000000000.0, 5, this));;
    ui->lineEdit_x_range_trigle_2->setValidator(new QDoubleValidator(0.0, 100000000000.0, 5, this));
    ui->lineEdit_y_num_rect_2->setValidator(new QIntValidator(0.0, 100000000000.0,this));
    ui->lineEdit_y_num_trigle_2->setValidator(new QIntValidator(0.0, 100000000000.0,this));
    ui->lineEdit_y_range_plane_2->setValidator(new QDoubleValidator(0.0, 100000000000.0, 5, this));
    ui->lineEdit_y_range_rect_2->setValidator(new QDoubleValidator(0.0, 100000000000.0, 5, this));
    ui->lineEdit__circle_r_grid_2->setValidator(new QDoubleValidator(0.0, 100000000000.0, 5, this));
    ui->lineEdit_y_range_trigle_2->setValidator(new QDoubleValidator(0.0, 100000000000.0, 5, this));
    ui->lineEdit_offset_x->setValidator(new QDoubleValidator(0.0, 100000000000.0,5, this));;
    ui->lineEdit_offset_y->setValidator(new QDoubleValidator(0.0, 100000000000.0,5, this));;
    ui->lineEdit_offset_z->setValidator(new QDoubleValidator(0.0, 100000000000.0,5, this));;
}

void HGenArray::init_data()
{
    ui->lineEdit_circle_num_grid_2->setText("0");
    ui->lineEdit_circle_r_plane_2->setText("0");
    ui->lineEdit_radial_range_2->setText("0");
    ui->lineEdit_x_num_rect_2->setText("0");
    ui->lineEdit_x_num_trigle_2->setText("0");
    ui->lineEdit_x_range_plane_2->setText("0");
    ui->lineEdit_x_range_rect_2->setText("0");
    ui->lineEdit_x_range_trigle_2->setText("0");
    ui->lineEdit_y_num_rect_2->setText("0");
    ui->lineEdit_y_num_trigle_2->setText("0");
    ui->lineEdit_y_range_plane_2->setText("0");
    ui->lineEdit_y_range_rect_2->setText("0");
    ui->lineEdit__circle_r_grid_2->setText("0");
    ui->lineEdit_y_range_trigle_2->setText("0");
    ui->lineEdit_offset_x->setText("0");
    ui->lineEdit_offset_y->setText("0");
    ui->lineEdit_offset_z->setText("0");
    m_path.clear();
    m_offset.clear();
    m_radar_coordinate.clear();
}

void HGenArray::init_array()
{
    ui->m_rectwidget_2->setParent(ui->m_widget_loyout_2);
    ui->m_triangle->setParent(ui->m_widget_loyout_2);
    ui->m_circleplane->setParent(ui->m_widget_loyout_2);
    ui->m_circlegrid->setParent(ui->m_widget_loyout_2);


    ui->radioButton_rect_2->setChecked(true);
    ui->m_triangle->hide();
    ui->m_circlegrid->hide();
    ui->m_circleplane->hide();
    ui->m_rectwidget_2->show();
    ui->m_rectwidget_2->setGeometry(10,10,261,161);

    ui->radioButton_rect_spred->setChecked(true);
}

void HGenArray::on_radioButton_rect_2_clicked()
{
    ui->radioButton_rect_2->show();
    ui->m_triangle->hide();
    ui->m_circlegrid->hide();
    ui->m_circleplane->hide();
    ui->m_triangle->setGeometry(10,10,261,161);
    init_array();
}

void HGenArray::on_radioButton_trigle_2_clicked()
{
    ui->m_triangle->show();
    ui->m_circlegrid->hide();
    ui->m_circleplane->hide();
    ui->m_rectwidget_2->hide();
    ui->m_triangle->setGeometry(10,10,261,161);
    init_data();
}

void HGenArray::on_radioButton_circle_plane_2_clicked()
{
    ui->m_triangle->hide();
    ui->m_circlegrid->hide();
    ui->m_circleplane->show();
    ui->m_rectwidget_2->hide();
    ui->m_circleplane->setGeometry(10,10,261,161);
    init_data();
}

void HGenArray::on_radioButton__circle_grid_2_clicked()
{
    ui->m_triangle->hide();
    ui->m_circlegrid->show();
    ui->m_circleplane->hide();
    ui->m_rectwidget_2->hide();
    ui->m_circlegrid->setGeometry(10,10,261,161);
    init_data();
}

bool HGenArray::check_value()
{
    if(ui->radioButton_rect_2->isChecked())
    {
        return check_rect();
    }
    if(ui->radioButton_trigle_2->isChecked())
    {
        return check_trigle();
    }
    if(ui->radioButton__circle_grid_2->isChecked())
    {
        return check_circle_grid();
    }
    if(ui->radioButton_circle_plane_2->isChecked())
    {
        return check_circle_plane();
    }
    return true;
}

bool HGenArray::check_rect()
{
    double y_rang =ui->lineEdit_y_range_rect_2->text().toDouble();
    double x_rang =ui->lineEdit_x_range_rect_2->text().toDouble();
    int y_num =ui->lineEdit_y_num_rect_2->text().toInt();
    int x_num = ui->lineEdit_x_num_rect_2->text().toInt();
    if(y_rang ==0 || x_rang==0||y_num ==0 ||x_num ==0)
    {
        return input_error();
    }else
    {
        return true;
    }
}

bool HGenArray::check_trigle()
{
    double y_rang =ui->lineEdit_y_range_trigle_2->text().toDouble();
    double x_rang =ui->lineEdit_x_range_trigle_2->text().toDouble();
    int y_num =ui->lineEdit_y_num_trigle_2->text().toInt();
    int x_num = ui->lineEdit_x_num_trigle_2->text().toInt();
    if(y_rang ==0 || x_rang==0||y_num ==0 ||x_num ==0)
    {
        return input_error();
    }else
    {
        return true;
    }
}

bool HGenArray::check_circle_plane()
{
    double x_rang = ui->lineEdit_x_range_plane_2->text().toDouble();
    double y_rang = ui->lineEdit_y_range_plane_2->text().toDouble();
    double      r =  ui->lineEdit_circle_r_plane_2->text().toDouble();
    if(x_rang == 0 || y_rang == 0 || r==0)
    {
        return input_error();
    }
    else
    {
        return true;
    }
}

bool HGenArray::check_circle_grid()
{

    double n = ui->lineEdit_circle_num_grid_2->text().toDouble();
    double r = ui->lineEdit__circle_r_grid_2->text().toDouble();
    int    d = ui->lineEdit_radial_range_2->text().toDouble();
    if(n == 0 || r == 0 || d == 0)
    {
        return input_error();
    }
    else if(r < d)
    {
        QMessageBox::about(this,tr("Error"),tr(" radius must greater than radial distance !"));
        return false;
    }else
        return true;
}

bool HGenArray::input_error()
{
    QMessageBox::about(this,tr("Error"),tr("input type error ,can not equal to zero!")) ;
    return false;
}

bool HGenArray::out_range(QString text,QString information)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.setInformativeText(information);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Ok:
        return true;
        break;

    case QMessageBox::Cancel:
        return false;
        break;
    default:
        return false;
        break;
    }
    return true;
}

void HGenArray::closeEvent(QCloseEvent *e)
{
    destroy();
}

bool HGenArray::creat_array(HArray *array)
{
    double s_b=0;double s_e=0;
    array->get_sb_se(s_b,s_e);
    s_b += ui->lineEdit_offset_y->text().toDouble();
    s_e += ui->lineEdit_offset_y->text().toDouble();
    double up_,down_,left_,right_;
    array->IsScanningOutRange(s_b,s_e,left_,right_);
    QString infor = CVTS::GBKToUnicode::toUnicode("是否继续生成？");
    if(left_ > 0)
    {
        QString text = CVTS::GBKToUnicode::toUnicode("扫描区域左边越界")+ QString::number(left_)+CVTS::GBKToUnicode::toUnicode("毫米");
        if(!out_range(text,infor))
            return false;

    }
    if(right_ > 0)
    {
        QString text = CVTS::GBKToUnicode::toUnicode("扫描区域右边越界")+ QString::number(right_)+CVTS::GBKToUnicode::toUnicode("毫米");
        if(!out_range(text,infor))
            return false;
    }
    m_radar_coordinate = array->EnsureCoordinate();
    array->Creat_Array_Element_File();
    double p_b;double p_e;
    array->get_pb_pe(p_b,p_e);
    p_b += ui->lineEdit_offset_x->text().toDouble();
    p_b += ui->lineEdit_offset_x->text().toDouble();
    array->IsProbeOutRange(array->get_Lx(),up_,down_);
    if(up_>0)
    {
        QString text = CVTS::GBKToUnicode::toUnicode("扫描区域上边越界")+ QString::number(up_)+CVTS::GBKToUnicode::toUnicode("毫米");
        if(!out_range(text,infor))
            return false;
    }
    if(down_>0)
    {
        QString text = CVTS::GBKToUnicode::toUnicode("扫描区域下边越界")+ QString::number(down_)+CVTS::GBKToUnicode::toUnicode("毫米");
        if(!out_range(text,infor))
            return false;
    }
    return true;
}


bool HGenArray::creat_rect_array()
{
    HRectangleArray *rect = new HRectangleArray(m_offset,m_path);
    int m_nx  = ui->lineEdit_x_num_rect_2->text().toInt();
    int m_ny  = ui->lineEdit_y_num_rect_2->text().toInt();
    double m_dx = ui->lineEdit_x_range_rect_2->text().toDouble();
    double m_dy = ui->lineEdit_y_range_rect_2->text().toDouble();
    rect->ArraySize(m_nx,m_ny,m_dx,m_dy);
    return  creat_array(rect);
}

bool HGenArray::creat_trigle_array()
{
    HTriangleArray *trigle = new HTriangleArray(m_offset,m_path);
    int m_nx  = ui->lineEdit_x_num_trigle_2->text().toInt();
    int m_ny  = ui->lineEdit_y_num_trigle_2->text().toInt();
    double m_dx = ui->lineEdit_x_range_trigle_2->text().toDouble();
    double m_dy = ui->lineEdit_y_range_trigle_2->text().toDouble();
    trigle->ArraySize(m_nx,m_ny,m_dx,m_dy);
    return creat_array(trigle);
}

bool HGenArray::creat_circle_plane()
{
    HPlaneCircleArray *plane = new HPlaneCircleArray(m_offset,m_path);
    int    m_dx = ui->lineEdit_x_range_plane_2->text().toDouble();
    double m_dy = ui->lineEdit_y_range_plane_2->text().toDouble();
    double m_r =  ui->lineEdit_circle_r_plane_2->text().toDouble();
    if(ui->radioButton_rect_spred->isChecked())
        plane->ArraySize(m_dx,m_dy,m_r,true);
    else
        plane->ArraySize(m_dx,m_dy,m_r,false);
    return creat_array(plane);
}

bool HGenArray::creat_circle_grid()
{
    HGridCircleArray *grid = new HGridCircleArray(m_offset,m_path);
    int    m_n = ui->lineEdit_circle_num_grid_2->text().toInt();
    double m_r = ui->lineEdit__circle_r_grid_2->text().toDouble();
    double m_d = ui->lineEdit_radial_range_2->text().toDouble();
    grid->ArraySize(m_d,m_n,m_r);
    return creat_array(grid);
}

void HGenArray::data_clear()
{
    m_radar_coordinate.clear();
    m_offset ="";
}

void HGenArray::get_coordinate(std::map<int, QString> &radar_coordinate, QString offset)
{
    radar_coordinate = m_radar_coordinate;
    offset = m_offset;
}


void HGenArray::on_pushButton_ok_clicked()
{
    if(check_value())
    {
        bool ret = true;
        data_clear();
        m_offset = ui->lineEdit_offset_x->text() + "," + ui->lineEdit_offset_y->text() \
                + "," +ui->lineEdit_offset_z->text();
        m_path = QFileDialog::getSaveFileName(this, tr("Save Map File"),
                                              QApplication::applicationDirPath(),
                                              tr("Array(*.array)"));
        if(!m_path.isEmpty())
        {
            if(ui->radioButton_rect_2->isChecked())
            {
                ret =  creat_rect_array();
            }
            if(ui->radioButton_trigle_2->isChecked())
            {
                ret =  creat_trigle_array();
            }
            if(ui->radioButton_circle_plane_2->isChecked())
            {
                ret =  creat_circle_plane();
            }
            if(ui->radioButton__circle_grid_2->isChecked())
            {
                ret =  creat_circle_grid();
            }
            if(ret)
            {
                QMessageBox::about(this,tr("Succeed"),tr("File  Creat succeed!")) ;
            }
        }
        else
            QMessageBox::about(this,tr("Error"),tr("File name is empty !")) ;
    }
}
void HGenArray::on_pushButton_cancle_clicked()
{
    done(-1);
}

