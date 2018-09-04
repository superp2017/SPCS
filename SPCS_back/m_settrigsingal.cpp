#include "m_settrigsingal.h"
#include "ui_m_settrigsingal.h"
#include "vnadapter.h"


M_SetTrigSingal::M_SetTrigSingal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::M_SetTrigSingal)
{
    ui->setupUi(this);
    default_setting();
}

M_SetTrigSingal::~M_SetTrigSingal()
{
    delete ui;
}

void M_SetTrigSingal::on_pushButton_default_clicked()
{
    default_setting();
}

void M_SetTrigSingal::on_checkBox_path1_clicked()
{
    ui->groupBox__path1->setEnabled(ui->checkBox_path1->isChecked());
}

void M_SetTrigSingal::on_checkBox_path3_clicked()
{
    ui->groupBox_path3->setEnabled(ui->checkBox_path3->isChecked());
}

void M_SetTrigSingal::on_checkBox_path4_clicked()
{
    ui->groupBox_path4->setEnabled(ui->checkBox_path4->isChecked());
}

void M_SetTrigSingal::on_checkBox_path2_clicked()
{
    ui->groupBox_path2->setEnabled(ui->checkBox_path2->isChecked());
}

void M_SetTrigSingal::on_checkBox_pulse_clicked()
{
    ui->groupBox_all->setEnabled(ui->checkBox_pulse->isChecked());
}

void M_SetTrigSingal::default_setting()
{
    ui->checkBox_pulse->setChecked(false);
    ui->checkBox_path0->setChecked(true);
    ui->checkBox_path1->setChecked(true);
    ui->checkBox_path2->setChecked(true);
    ui->checkBox_path3->setChecked(true);
    ui->checkBox_path4->setChecked(true);

    ui->checkBox_path0->setEnabled(false);
    ui->groupBox_path0->setEnabled(false);

    ui->lineEdit_0_delay->setText("0.0004");
    ui->lineEdit_0_width->setText("0.001");
    ui->lineEdit_1_delay->setText("0.008");
    ui->lineEdit_1_width->setText("0.01");
    ui->lineEdit_2_delay->setText("0.008");
    ui->lineEdit_2_width->setText("0.01");
    ui->lineEdit_3_delay->setText("0.008");
    ui->lineEdit_3_width->setText("0.01");
    ui->lineEdit_4_delay->setText("0.008");
    ui->lineEdit_4_width->setText("0.01");
    ui->lineEdit_period->setText("1");
}

void M_SetTrigSingal::on_pushButton_ok_clicked()
{
    dosetting();
}

void M_SetTrigSingal::enablePulse(bool enable)
{
    ui->checkBox_pulse->setChecked(enable);
}

void M_SetTrigSingal::dosetting()
{
    VNAdapter::instance()->setPulse(ui->checkBox_pulse->isChecked(),ui->lineEdit_period->text().toDouble(),\
                                    ui->checkBox_path0->isChecked(),ui->checkBox_path1->isChecked(),\
                                    ui->checkBox_path2->isChecked(),ui->checkBox_path3->isChecked(),\
                                    ui->checkBox_path4->isChecked(),ui->lineEdit_0_delay->text().toDouble(),\
                                    ui->lineEdit_0_width->text().toDouble(),ui->lineEdit_1_delay->text().toDouble(),\
                                    ui->lineEdit_1_width->text().toDouble(),ui->lineEdit_2_delay->text().toDouble(),\
                                    ui->lineEdit_2_delay->text().toDouble(),ui->lineEdit_3_delay->text().toDouble(),\
                                    ui->lineEdit_3_width->text().toDouble(),ui->lineEdit_4_delay->text().toDouble(),\
                                    ui->lineEdit_4_width->text().toDouble());
}
