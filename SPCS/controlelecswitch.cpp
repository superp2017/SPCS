#include "controlelecswitch.h"
#include "ui_controlelecswitch.h"
#include "teleswitch.h"


ControlElecSwitch::ControlElecSwitch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlElecSwitch)
{
    ui->setupUi(this);

    for(int i =0;i<17;++i)
    {
        m_button_status[i] = false;
    }
    m_buttons[0] = ui->pushButton_17;
    m_buttons[1] = ui->pushButton_1;
    m_buttons[2] = ui->pushButton2;
    m_buttons[3] = ui->pushButton3;
    m_buttons[4] = ui->pushButton4;
    m_buttons[5] = ui->pushButton5;
    m_buttons[6] = ui->pushButton_6;
    m_buttons[7] = ui->pushButton7;
    m_buttons[8] = ui->pushButton_8;
    m_buttons[9] = ui->pushButton_9;
    m_buttons[10] = ui->pushButton_10;
    m_buttons[11] = ui->pushButton_11;
    m_buttons[12] = ui->pushButton_12;
    m_buttons[13] = ui->pushButton_13;
    m_buttons[14] = ui->pushButton_14;
    m_buttons[15] = ui->pushButton_15;
    m_buttons[16] = ui->pushButton_16;

    StatusChange(false);
    this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

ControlElecSwitch::~ControlElecSwitch()
{
    delete ui;
}


void ControlElecSwitch::on_pushButton_exit_clicked()
{
    this->hide();
}

QString ControlElecSwitch::status(int i,bool &res)
{
    res = m_button_status[i];
    if(!res)
        return CVTS::GBKToUnicode::toUnicode("关闭");
    else
        return CVTS::GBKToUnicode::toUnicode("打开");
}

void ControlElecSwitch::setCurrentStatus(QPushButton *button, int id)
{
    if(id >=  CD_NUMS || id <0) return ;
    bool  ret = false;
    button->setText(status(id,ret));
    m_button_status[id] = !ret;
    if(ret)
    {
        TEleSwitch::instance()->turn_off(CVTS::CVTS_Decetor(id-1));
        button->setStyleSheet("");
    }
    else
    {
        TEleSwitch::instance()->turn_on(CVTS::CVTS_Decetor(id-1));
        button->setStyleSheet(QStringLiteral("background-color: rgb(220, 220, 0);"));
    }
}

void ControlElecSwitch::StatusChange(bool isopen)
{
    QString ls_str;
    if(!isopen)
        ls_str = CVTS::GBKToUnicode::toUnicode("打开");
    else
        ls_str = CVTS::GBKToUnicode::toUnicode("关闭");


    for(int i =0;i<17;++i)
    {
        m_buttons[i]->setStyleSheet("");
        m_button_status[i] = isopen;
    }
}

void ControlElecSwitch::on_pushButton_17_clicked()
{
    setCurrentStatus(ui->pushButton_17,0);
}

void ControlElecSwitch::on_pushButton_1_clicked()
{
    setCurrentStatus(ui->pushButton_1,1);
}

void ControlElecSwitch::on_pushButton2_clicked()
{
    setCurrentStatus(ui->pushButton2,2);
}

void ControlElecSwitch::on_pushButton3_clicked()
{
    setCurrentStatus(ui->pushButton3,3);
}

void ControlElecSwitch::on_pushButton4_clicked()
{
    setCurrentStatus(ui->pushButton4,4);
}

void ControlElecSwitch::on_pushButton5_clicked()
{
    setCurrentStatus(ui->pushButton5,5);
}

void ControlElecSwitch::on_pushButton_6_clicked()
{
    setCurrentStatus(ui->pushButton_6,6);
}

void ControlElecSwitch::on_pushButton7_clicked()
{
    setCurrentStatus(ui->pushButton7,7);
}

void ControlElecSwitch::on_pushButton_8_clicked()
{
    setCurrentStatus(ui->pushButton_8,8);
}

void ControlElecSwitch::on_pushButton_9_clicked()
{
    setCurrentStatus(ui->pushButton_9,9);
}

void ControlElecSwitch::on_pushButton_10_clicked()
{
    setCurrentStatus(ui->pushButton_10,10);
}

void ControlElecSwitch::on_pushButton_11_clicked()
{
    setCurrentStatus(ui->pushButton_11,11);
}

void ControlElecSwitch::on_pushButton_12_clicked()
{
    setCurrentStatus(ui->pushButton_12,12);
}

void ControlElecSwitch::on_pushButton_13_clicked()
{
    setCurrentStatus(ui->pushButton_13,13);
}

void ControlElecSwitch::on_pushButton_14_clicked()
{
    setCurrentStatus(ui->pushButton_14,14);
}

void ControlElecSwitch::on_pushButton_15_clicked()
{
    setCurrentStatus(ui->pushButton_15,15);
}

void ControlElecSwitch::on_pushButton_16_clicked()
{
    setCurrentStatus(ui->pushButton_16,16);
}


void ControlElecSwitch::on_pushButton_close_clicked()
{
    StatusChange(false);
    TEleSwitch::instance()->turn_off_all();
}


