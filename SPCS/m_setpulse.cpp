#include "m_setpulse.h"
#include "ui_m_setpulse.h"
#include "vnadapter.h"

M_SetPulse::M_SetPulse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::M_SetPulse)
{
    ui->setupUi(this);
    default_setting();
    this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

M_SetPulse::~M_SetPulse()
{
    delete ui;
}

void M_SetPulse::on_pushButton_default_2_clicked()
{
    default_setting();
}


void M_SetPulse::default_setting()
{
    ui->checkBox_pulse_2->setChecked(false);
    ui->checkBox_path0_2->setChecked(true);
    ui->checkBox_path1_2->setChecked(true);
    ui->checkBox_path2_2->setChecked(true);
    ui->checkBox_path3_2->setChecked(true);
    ui->checkBox_path4_2->setChecked(true);

    ui->checkBox_path0_2->setEnabled(false);
    //    ui->groupBox_path0_2->setEnabled(false);

    ui->lineEdit_0_delay_2->setText("2.5");
    ui->lineEdit_0_width_2->setText("0");
    ui->lineEdit_1_delay_2->setText("0.05");
    ui->lineEdit_1_width_2->setText("9.97");
    ui->lineEdit_2_delay_2->setText("0.12");
    ui->lineEdit_2_width_2->setText("10");
    ui->lineEdit_3_delay_2->setText("0.05");
    ui->lineEdit_3_width_2->setText("9.97");
    ui->lineEdit_4_delay_2->setText("0.06");
    ui->lineEdit_4_width_2->setText("10.17");
    ui->lineEdit_period_2->setText("100");
}


void M_SetPulse::enablePulse(bool enable)
{
    ui->checkBox_pulse_2->setChecked(enable);
}


void M_SetPulse::on_pushButton_ok_2_clicked()
{
    dosetting();
    this->hide();
}


void M_SetPulse::dosetting()
{
    VNAdapter::instance()->setPulse(ui->checkBox_pulse_2->isChecked(),ui->lineEdit_period_2->text().toDouble(),\
                                    ui->checkBox_path0_2->isChecked(),ui->checkBox_path1_2->isChecked(),\
                                    ui->checkBox_path2_2->isChecked(),ui->checkBox_path3_2->isChecked(),\
                                    ui->checkBox_path4_2->isChecked(),ui->lineEdit_0_delay_2->text().toDouble(),\
                                    ui->lineEdit_0_width_2->text().toDouble(),ui->lineEdit_1_delay_2->text().toDouble(),\
                                    ui->lineEdit_1_width_2->text().toDouble(),ui->lineEdit_2_delay_2->text().toDouble(),\
                                    ui->lineEdit_2_width_2->text().toDouble(),ui->lineEdit_3_delay_2->text().toDouble(),\
                                    ui->lineEdit_3_width_2->text().toDouble(),ui->lineEdit_4_delay_2->text().toDouble(),\
                                    ui->lineEdit_4_width_2->text().toDouble());
}

void M_SetPulse::get_param(bool &isenable, QString &period, bool &pulse0, QString &pulse0_wi, QString &pulse0_de, bool &pulse1, QString &pulse1_wi, QString &pulse1_de, bool &pulse2, QString &pulse2_wi, QString &pulse2_de, bool &pulse3, QString &pulse3_wi, QString &pulse3_de, bool &pulse4, QString &pulse4_wi, QString &pulse4_de)
{
    isenable = ui->checkBox_pulse_2->isChecked();
    period   =ui->lineEdit_period_2->text();

    pulse0   = ui->checkBox_path0_2->isChecked();
    pulse0_wi= ui->lineEdit_0_width_2->text();
    pulse0_de= ui->lineEdit_0_delay_2->text();

    pulse1   = ui->checkBox_path1_2->isChecked();
    pulse1_wi= ui->lineEdit_1_width_2->text();
    pulse1_de= ui->lineEdit_1_delay_2->text();

    pulse2   = ui->checkBox_path2_2->isChecked();
    pulse2_wi= ui->lineEdit_2_width_2->text();
    pulse2_de= ui->lineEdit_2_delay_2->text();

    pulse3   = ui->checkBox_path3_2->isChecked();
    pulse3_wi= ui->lineEdit_3_width_2->text();
    pulse3_de= ui->lineEdit_3_delay_2->text();

    pulse4   = ui->checkBox_path4_2->isChecked();
    pulse4_wi= ui->lineEdit_4_width_2->text();
    pulse4_de= ui->lineEdit_4_delay_2->text();

}

void M_SetPulse::Relad_Parame(bool isenable, QString period, bool pulse0, QString pulse0_wi, QString pulse0_de, bool pulse1, QString pulse1_wi, QString pulse1_de, bool pulse2, QString pulse2_wi, QString pulse2_de, bool pulse3, QString pulse3_wi, QString pulse3_de, bool pulse4, QString pulse4_wi, QString pulse4_de)
{

    ui->checkBox_pulse_2->setChecked(isenable);
    ui->lineEdit_period_2->setText(period);

    ui->checkBox_path0_2->setChecked(pulse0);
    ui->lineEdit_0_width_2->setText(pulse0_wi);
    ui->lineEdit_0_delay_2->setText(pulse0_de);

    ui->checkBox_path1_2->setChecked(pulse1);
    ui->lineEdit_1_width_2->setText(pulse1_wi);
    ui->lineEdit_1_delay_2->setText(pulse1_de);

    ui->checkBox_path2_2->setChecked(pulse2);
    ui->lineEdit_2_width_2->setText(pulse2_wi);
    ui->lineEdit_2_delay_2->setText(pulse2_de);

    ui->checkBox_path3_2->setChecked(pulse3);
    ui->lineEdit_3_width_2->setText(pulse3_wi);
    ui->lineEdit_3_delay_2->setText(pulse3_de);

    ui->checkBox_path4_2->setChecked(pulse4);
    ui->lineEdit_4_width_2->setText(pulse4_wi);
    ui->lineEdit_4_delay_2->setText(pulse4_de);
}

void M_SetPulse::on_checkBox_path1_2_clicked()
{
    ui->groupBox__path1_2->setEnabled(ui->checkBox_path1_2->isChecked());
}

void M_SetPulse::on_checkBox_path2_2_clicked()
{
    ui->groupBox_path2_2->setEnabled(ui->checkBox_path2_2->isChecked());
}

void M_SetPulse::on_checkBox_path3_2_clicked()
{
    ui->groupBox_path3_2->setEnabled(ui->checkBox_path3_2->isChecked());
}

void M_SetPulse::on_checkBox_path4_2_clicked()
{
    ui->groupBox_path4_2->setEnabled(ui->checkBox_path4_2->isChecked());
}

void M_SetPulse::on_checkBox_pulse_2_clicked()
{
    ui->groupBox_all_2->setEnabled(ui->checkBox_pulse_2->isChecked());
}



void M_SetPulse::on_pushButtonapply_clicked()
{
    dosetting();
}

