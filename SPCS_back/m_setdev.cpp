#include "m_setdev.h"
#include "ui_m_setdev.h"
#include "TAttenuation.h"
#include "m_setpulse.h"
#include "vnadapter.h"
#include <QListWidgetItem>
#include <QVector>

M_SetDev::M_SetDev(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::M_SetDev),
    m_powerate("./config/power_calibration.s2p"),
    m_table_widget(0,2)
{
    m_table_widget.setWindowTitle("power calibration");
    ui->setupUi(this);

    ui->comboBox_freq->addItem("Hz");
    ui->comboBox_freq->addItem("kHz");
    ui->comboBox_freq->addItem("MHz");
    ui->comboBox_freq->addItem("GHz");
    ui->lineEdit_width->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    ui->lineEdit_power->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    ui->lineEdit_sweep_time->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));

    ui->comboBox_attan->addItem("0");
    ui->comboBox_attan->addItem("10");
    ui->comboBox_attan->addItem("20");
    ui->comboBox_attan->addItem("30");
    ui->comboBox_attan->addItem("40");
    ui->comboBox_attan->addItem("50");
    ui->comboBox_attan->addItem("60");
    ui->comboBox_attan->addItem("70");
    init();

    std::map<QString,QString> &ls_map = m_powerate.get_freq_map();

    int row = 0;
    std::map<QString,QString>::iterator iter = ls_map.begin();
    m_table_widget.setFixedHeight(640);
    m_table_widget.setFixedWidth(250);
    m_table_widget.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    m_table_widget.setEditTriggers(QAbstractItemView::NoEditTriggers);
    while(iter != ls_map.end())
    {
        m_table_widget.insertRow(row);
        row++;
        iter++;
    }
    update_table();
       this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

void M_SetDev::init()
{
    ui->lineEdit_power->setText("18");
    ui->m_port_power->setText(QString::number(19 + m_powerate.get_avg(),'f',2));
    ui->lineEdit_sweep_time->setText("25");
    ui->lineEdit_width->setText("10");
    ui->comboBox_freq->setCurrentIndex(0);
    ui->comboBox_attan->setCurrentIndex(0);
    m_attan = 0;


}

void M_SetDev::update_table()
{
    m_table_widget.clear();
    QStringList ls_list;
    ls_list.append("frequency");
    ls_list.append("power");
    m_table_widget.setHorizontalHeaderLabels(ls_list);
    QVector<QString> &ls_vec = m_powerate.get_freqs();
    std::map<QString, QString> &ls_map = m_powerate.get_freq_map();

    int row = 0;
    QVector<QString>::iterator iter = ls_vec.begin();

    while(iter != ls_vec.end())
    {
        m_table_widget.setItem(row,0, new QTableWidgetItem(*iter));
        m_table_widget.setItem(row,1, new QTableWidgetItem(\
                                   QString::number(ls_map[*iter].toDouble() + ui->lineEdit_power->text().toDouble(),'f',2)));
        row++;
        iter++;
    }
}


M_SetDev::~M_SetDev()
{
    delete ui;
}

void M_SetDev::on_pushButton_default_clicked()
{
    init();
}

void M_SetDev::on_pushButto_OK_clicked()
{
    VNAdapter::s_vna = VNA_AGILENT;
    if(ui->comboBox_type->currentIndex())
        VNAdapter::s_vna = VNA_RS;
    TAttenuation::instance()->attenuation(NI_ANTENNA(ui->comboBox_attan->currentIndex()));
    m_attan = ui->comboBox_attan->currentIndex();
    m_table_widget.hide();
    done(123);
}

void M_SetDev::on_pushButto_apply_clicked()
{
    VNAdapter::s_vna = VNA_AGILENT;
    if(ui->comboBox_type->currentIndex())
        VNAdapter::s_vna = VNA_RS;

    TAttenuation::instance()->attenuation(NI_ANTENNA(ui->comboBox_attan->currentIndex()));
    m_attan = ui->comboBox_attan->currentIndex();
}

void M_SetDev::on_pushButton_pulse_clicked()
{
    M_SetPulse::instance()->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    M_SetPulse::instance()->showNormal();
}


void M_SetDev::get_PNA_set(QString &IF, QString &power, QString &sweeptime)
{
    IF        = QString::number(ui->lineEdit_width->text().toDouble() * pow(1000.0,ui->comboBox_freq->currentIndex()),'f');
    power     = ui->lineEdit_power->text();
    sweeptime = ui->lineEdit_sweep_time->text();
}

void M_SetDev::set_parame(QString IF, QString power, QString sweeptime, QString an)
{
    QString cur;
    int index;
    CVTS::COMBOX_INDEX_RREQ::GET_Combox_Index_Freq(IF,cur,index);
    ui->lineEdit_width->setText(cur);
    ui->comboBox_freq->setCurrentIndex(index);

    ui->lineEdit_power->setText(power);
    ui->lineEdit_sweep_time->setText(sweeptime);
    ui->comboBox_attan->setCurrentIndex(an.toInt());
}

void M_SetDev::sendstatus(bool isent)
{
    if(isent)
    {
        ui->lineEdit_power->setText("15");
        ui->lineEdit_width->setText("200");
        ui->comboBox_attan->setCurrentIndex(0);
        ui->comboBox_freq->setCurrentIndex(1);
        TAttenuation::instance()->attenuation(NI_ANTENNA(0));
    }
    else
    {
        ui->lineEdit_power->setText("20");
        ui->comboBox_attan->setCurrentIndex(0);
        ui->lineEdit_width->setText("10");
        TAttenuation::instance()->attenuation(NI_ANTENNA(0));
    }
}


void M_SetDev::on_toolButton_clicked()
{
    update_table();
    m_table_widget.showNormal();
}

void M_SetDev::on_lineEdit_power_editingFinished()
{
    double value = ui->lineEdit_power->text().toDouble() + m_powerate.get_avg();
    ui->m_port_power->setText(QString::number(value,'f',2));
    update_table();
}

void M_SetDev::on_lineEdit_power_textChanged(const QString &arg1)
{
    double value = arg1.toDouble() + m_powerate.get_avg();
    ui->m_port_power->setText(QString::number(value,'f',2));
    update_table();
}
