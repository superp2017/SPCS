#include "m_selectgallerydlg.h"
#include "ui_m_selectgallerydlg.h"
#include  "tswmatrixs.h"

M_SelectGallerydlg::M_SelectGallerydlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::M_SelectGallerydlg)
{
    ui->setupUi(this);

}

M_SelectGallerydlg::~M_SelectGallerydlg()
{
    delete ui;
}

void M_SelectGallerydlg::init()
{
    m_radio.clear();
    m_radio.push_back(ui->radioButton_port1);
    m_radio.push_back(ui->radioButton_port2);
    m_radio.push_back(ui->radioButton_port3);
    m_radio.push_back(ui->radioButton_port4);
    m_radio.push_back(ui->radioButton_port5);
    m_radio.push_back(ui->radioButton_port6);
    m_radio.push_back(ui->radioButton_port7);
    m_radio.push_back(ui->radioButton_port8);
    m_radio.push_back(ui->radioButton_port9);
    m_radio.push_back(ui->radioButton_port10);
    m_radio.push_back(ui->radioButton_port11);
    m_radio.push_back(ui->radioButton_port12);
    m_radio.push_back(ui->radioButton_port13);
    m_radio.push_back(ui->radioButton_port14);
    m_radio.push_back(ui->radioButton_port15);
    m_radio.push_back(ui->radioButton_port16);
    reset();
    this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}


int &M_SelectGallerydlg::get_port()
{
    return m_checked;
}

void M_SelectGallerydlg::close_all()
{
    reset();
}

void M_SelectGallerydlg::open_port(int index)
{
    if(index > 0)
    {
        m_radio.at(index-1)->setChecked(true);
    }
    if(!index) ui->radioButton_closeall->setChecked(true);
}


void M_SelectGallerydlg::reset()
{
    open_port(0);
    m_checked = 0;
    TSWMatrixs::instance()->turn_off_all();

}

int M_SelectGallerydlg::CheckStatus()
{
    if(ui->radioButton_closeall->isChecked())
        return 0;
    for(size_t i =0;i<m_radio.size();++i)
    {
        if(m_radio.at(i)->isChecked())
        {
            return i+1;
        }
    }
    return 0;
}

void M_SelectGallerydlg::on_pushButton_ok_clicked()
{
    int ret = CheckStatus();
    m_checked = ret;
    //  TSWMatrixs::instance()->turn_off_all();
    if(ret)
        TSWMatrixs::instance()->turn_on(CVTS::Matrix(ret-1));
    else
        TSWMatrixs::instance()->turn_off_all();
    //   done(123);
}

void M_SelectGallerydlg::on_pushButton_cancel_clicked()
{
    done(-1);
}

