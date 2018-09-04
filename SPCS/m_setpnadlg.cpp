#include "m_setpnadlg.h"
#include "ui_m_setpnadlg.h"
#include <QDoubleValidator>
#include "m_setpulse.h"

M_SetPNAdlg::M_SetPNAdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::M_SetPNAdlg)
{
    ui->setupUi(this);
    connect(ui->radioButton_continuous,SIGNAL(clicked()),this,SIGNAL(range()));
    connect(ui->radioButton_single,SIGNAL(clicked()),this,SIGNAL(single()));
    reset();
}

M_SetPNAdlg::~M_SetPNAdlg()
{
    delete ui;
}

void M_SetPNAdlg::reset()
{
    m_pna.clear();
    ui->lineEdit_width->setText("1");
    ui->lineEdit_power->setText("10");
    ui->lineEdit_continu_time->setText("0");
    ui->lineEdit_space_time->setText("0");
    ui->radioButton_continuous->setChecked(true);
    ui->comboBox->setCurrentIndex(1);
}

QString &M_SetPNAdlg::get_param(VNA_SWEEP_TYPE &t_type)
{
    if(ui->radioButton_single->isChecked())
        t_type = SINGLE_POINT;
    else
        t_type = CONTINUOUS_POINT;
    fill_param();
    return m_pna;
}

void M_SetPNAdlg::set_sweep_type(VNA_SWEEP_TYPE type)
{
    if(type == SINGLE_POINT)
        ui->radioButton_single->setChecked(true);
    else
        ui->radioButton_continuous->setChecked(true);
    fill_param();
}

void M_SetPNAdlg::set_freq_bandwidth(QString width)
{
    QString cur;
    int index;
    CVTS::COMBOX_INDEX_RREQ::GET_Combox_Index_Freq(width,cur,index);
    ui->lineEdit_width->setText(cur);
    ui->comboBox->setCurrentIndex(index);
    fill_param();
}

void M_SetPNAdlg::set_send_power(QString db)
{
    ui->lineEdit_power->setText(db);
    fill_param();
}

void M_SetPNAdlg::set_collect_continue_time(QString time)
{
    ui->lineEdit_continu_time->setText(time);
    fill_param();
}

void M_SetPNAdlg::set_collect_step_time(double time)
{
    QString times = QString::number(time,'f',2);
    ui->lineEdit_space_time->setText(times);
    fill_param();
}

void M_SetPNAdlg::range_click()
{
    ui->radioButton_continuous->setChecked(true);
}

void M_SetPNAdlg::single_clicK()
{
    ui->radioButton_single->setChecked(true);
}

void M_SetPNAdlg::init()
{
    ui->comboBox->addItem("Hz");
    ui->comboBox->addItem("KHz");
    ui->comboBox->addItem("MHz");
    ui->comboBox->addItem("GHz");
    ui->lineEdit_width->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    ui->lineEdit_power->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    ui->lineEdit_continu_time->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    ui->lineEdit_space_time->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    reset();
    fill_param();
}

void M_SetPNAdlg::on_pushButton_clicked()
{
    fill_param();
    done(123);
}

void M_SetPNAdlg::fill_param()
{
    m_pna.clear();
    double wid = ui->lineEdit_width->text().toDouble()*pow(1000.0,ui->comboBox->currentIndex());
    m_pna = QString::number(wid,'f',0)+\
            ","+ui->lineEdit_power->text()+","+ui->lineEdit_continu_time->text()+","+\
            ui->lineEdit_space_time->text();
}

void M_SetPNAdlg::on_pushButton_adv_clicked()
{
    M_SetPulse::instance()->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    M_SetPulse::instance()->showNormal();
}
