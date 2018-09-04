#include "controlwave.h"
#include "ui_controlwave.h"
#include "TRWaveControl_global.h"
#include "trwavecontrol.h"
#include "_global.h"
#include <QMessageBox>
#include "Windows.h"

ControlWave::ControlWave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlWave)
{
    ui->setupUi(this);
    on_pushButton_default_clicked();
}

ControlWave::~ControlWave()
{
    delete ui;
}

void ControlWave::on_pushButton_exit_clicked()
{
    done(0);
}

void ControlWave::on_pushButton_control_clicked()
{
    if(ui->radioButton_send->isChecked())
    {
        if(ui->lineEdit_col->text().toInt( ) == 0 || ui->lineEdit_row->text().toInt() == 0)
        {
            QString ls_title = CVTS::GBKToUnicode::toUnicode("警告");
            QString ls_com   = CVTS::GBKToUnicode::toUnicode("发射状态,禁止打开多个阵元！");
            QMessageBox mes;
            mes.setText(ls_com);
            mes.setWindowTitle(ls_title);
             mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
            mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
            mes.exec();
            return ;
        }
    }

    TRontrol ls_tr;
    if(ui->lineEdit_row->text().toInt() >40 ||ui->lineEdit_row->text().toInt() <-40 ||\
            ui->lineEdit_col->text().toInt()> 12 || ui->lineEdit_col->text().toInt()< -12 )
    {
        QString ls_title = CVTS::GBKToUnicode::toUnicode("提示");
        QString ls_com   = CVTS::GBKToUnicode::toUnicode("行列值超出范围");
        QMessageBox mes;
        mes.setText(ls_com);
        mes.setWindowTitle(ls_title);
         mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.exec();
    }
    QString ls_str;
    if( ui->radioButton_send->isChecked())
        ls_str  = CVTS::GBKToUnicode::toUnicode("发射状态,");
    else
        ls_str = CVTS::GBKToUnicode::toUnicode("接受状态,");


        TRWaveControl::instance()->AntenaInit(ui->radioButton_send->isChecked());
        ::Sleep(5);
        if(TRWaveControl::instance()->setMagnPhase(ls_tr,ui->lineEdit_row->text().toInt(),ui->lineEdit_col->text().toInt(),\
                                                   ui->radioButton_send->isChecked(),abs(ui->lineEdit_magn_r->text().toDouble()),\
                                                   ui->lineEdit_phase_r->text().toDouble(),abs(ui->lineEdit_magn_s->text().toDouble()),\
                                                   ui->lineEdit_phase_s->text().toDouble()))
        {
            int  row = ls_tr.t_row;
            int  col  = ls_tr.t_col;
            char buf[1024] = {0};
            sprintf(buf,"%d行,%d列,",row,col);
            ls_str += CVTS::GBKToUnicode::toUnicode(buf);
            ls_str += CVTS::GBKToUnicode::toUnicode("控制成功");
        }
        else
        {
            int  row = ls_tr.t_row;
            int  col  = ls_tr.t_col;
            char buf[1024] = {0};
            sprintf(buf,"%d行,%d列,",row,col);
            ls_str += CVTS::GBKToUnicode::toUnicode("控制失败");
        }
        ui->label_control_issuc->setText(ls_str);

}
void ControlWave::on_pushButton_down_clicked()
{
    if(TRWaveControl::instance()->DownPower())
        ui->label_down_issuc->setText(CVTS::GBKToUnicode::toUnicode("下电成功"));
    else
        ui->label_down_issuc->setText(CVTS::GBKToUnicode::toUnicode("下电失败"));
}

void ControlWave::on_pushButton_connecttest_clicked()
{
    if(TRWaveControl::instance()->udpConnectTest())
        ui->label_connect_issuc->setText(CVTS::GBKToUnicode::toUnicode("连接成功"));
    else
        ui->label_connect_issuc->setText(CVTS::GBKToUnicode::toUnicode("连接失败"));
}

void ControlWave::on_pushButton_attaninit_2_clicked()
{
    if(TRWaveControl::instance()->AntenaInit(ui->radioButton_send->isChecked()))
        ui->label_attan_issuc_2->setText(CVTS::GBKToUnicode::toUnicode("初始化成功"));
    else
        ui->label_attan_issuc_2->setText(CVTS::GBKToUnicode::toUnicode("初始化失败"));
}
void ControlWave::on_pushButton_default_clicked()
{
    ui->lineEdit_col->setText("1");
    ui->lineEdit_row->setText("1");
    ui->lineEdit_magn_r->setText("0");
    ui->lineEdit_phase_r->setText("0");
    ui->lineEdit_magn_s->setText("0");
    ui->lineEdit_phase_s->setText("0");
    QString ls_sec = CVTS::GBKToUnicode::toUnicode("是否成功？");

    ui->label_attan_issuc_2->setText(ls_sec);
    ui->label_connect_issuc->setText(ls_sec);
    ui->label_control_issuc->setText(ls_sec);
    ui->label_down_issuc->setText(ls_sec);
    ui->radioButton_recive->setChecked(true);
}
