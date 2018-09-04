#include "m_dampingdlg.h"
#include "ui_m_dampingdlg.h"
#include "TAttenuation.h"


M_Dampingdlg::M_Dampingdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::M_Dampingdlg)
{
    ui->setupUi(this);
}

M_Dampingdlg::~M_Dampingdlg()
{
    delete ui;
}

void M_Dampingdlg::reset()
{
    ui->comboBox->setCurrentIndex(0);
}

void M_Dampingdlg::init()
{
    ui->comboBox->addItem("0");
    ui->comboBox->addItem("10");
    ui->comboBox->addItem("20");
    ui->comboBox->addItem("30");
    ui->comboBox->addItem("40");
    ui->comboBox->addItem("50");
    ui->comboBox->addItem("60");
    ui->comboBox->addItem("70");
    m_map_damping[AN_ZERO] = 0;
    m_map_damping[AN_10]   = 1;
    m_map_damping[AN_20]   = 2;
    m_map_damping[AN_30]   = 3;
    m_map_damping[AN_40]   = 4;
    m_map_damping[AN_50]   = 5;
    m_map_damping[AN_60]   = 6;
    m_map_damping[AN_70]   = 7;
    reset();
}

int M_Dampingdlg::get_dampling()
{
    return ui->comboBox->currentIndex();
}

void M_Dampingdlg::attenuation(NI_ANTENNA na)
{
    if(m_map_damping.count(na)>0)
    {
        int index = m_map_damping[na];
        ui->comboBox->setCurrentIndex(index);
    }
}

void M_Dampingdlg::on_pushButton_clicked()
{
    TAttenuation::instance()->attenuation(NI_ANTENNA(ui->comboBox->currentIndex()));
    done(123);
}

void M_Dampingdlg::on_pushButton_2_clicked()
{
    done(-1);
}
