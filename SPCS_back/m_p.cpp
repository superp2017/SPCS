#include "m_p.h"
#include "ui_m_p.h"
#include "vnadapter.h"
#include "m_setpulse.h"
#include  "m_setdev.h"
#include  <QFile>
#include <QMessageBox>
#include <QFileDialog>


M_P::M_P(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::M_P)
{
    ui->setupUi(this);
    on_pushButton_2_clicked();
}

M_P::~M_P()
{
    delete ui;
}

void M_P::on_pushButton_clicked()
{
    test();
}

void M_P::on_pushButton_4_clicked()
{
    if(!VNAdapter::instance()->connect()) return ;

    VNAdapter::instance()->reset();

    VNAdapter::instance()->set_trace_S12();

    VNAdapter::instance()->set_freq(ui->lineEdit_start->text().toDouble(),\
                                    ui->lineEdit_end->text().toDouble(),\
                                    ui->lineEdit_point->text().toDouble());
    ////ÉèÖÃÂö³å
    M_SetPulse::instance()->dosetting();

    double if_band   = 10000;
    double power     = 15;
    // double sweeptime = 15;
    // M_SetDev::instance()->get_PNA_set(if_band,power,sweeptime);

    VNAdapter::instance()->set_IF_bandwidth(if_band);
    VNAdapter::instance()->set_power(power);
    //VNAdapter::instance()->set_sweep_time(sweeptime);
}

void M_P::test()
{
    //    QString p_path = "C:/Users/607/Desktop/" + ui->lineEdit_3->text() + ".dat";
    //    QFile file(p_path);
    //    if(!file.open(QFile::ReadWrite|QFile::Text)){
    //        qDebug()<< p_path << "open failed!";
    //        return;
    //    }
    //    QTextStream out(&file);


    double time = ui->lineEdit->text().toDouble();
    ::Sleep(time);
    int num = ui->lineEdit_2->text().toInt();
    for(int i = 0;i<num;++i)
    {
        if(m_continue)
        {
            QString S12  =   VNAdapter::instance()->collect_S12();
            QStringList ls_list = S12.split(QRegExp(","));
            double freqsize =ui->lineEdit_point->text().toInt();
            if(ls_list.size() == 2*freqsize)
            {

                for(int k=0;k<freqsize;++k)
                {
                    double real = ls_list.at(2*k).toDouble();
                    double imag = ls_list.at(2*k+1).toDouble();
                    double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                    double phase = VNAdapter::instance()->genPhase(real,imag);
                    //  out<<  db << "," << phase <<endl;
                    qDebug()<<db<<phase;
                }
            }
        }else
        {
            //  file.close();
            break;
        }
            qDebug()<<"-----------------------------------------------------------------";
    }
    // QMessageBox::information(NULL,tr("Message"),tr("OK!"));
    m_continue = true;
}


void M_P::on_pushButton_stop_clicked()
{
    m_continue =false;
}

void M_P::on_pushButton_2_clicked()
{
    m_continue = true;
    ui->lineEdit->setText("0");
    ui->lineEdit_2->setText("10");
    ui->lineEdit_3->setText("111");
    ui->lineEdit_point->setText("1");
    ui->lineEdit_start->setText("10000000000");
    ui->lineEdit_end->setText("10000000000");
    ui->lineEdit_power->setText("15");
}

void M_P::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"./",tr("data (*.dat)"));
    ui->lineEdit_3->setText(fileName);
}

