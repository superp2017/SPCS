#include "formcombine.h"
#include "ui_formcombine.h"
#include "cparsefile.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QFileDialog>

FormCombine::FormCombine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCombine)
{
    ui->setupUi(this);
}

FormCombine::~FormCombine()
{
    delete ui;
}

QString FormCombine::get_file()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/",
                                                    tr("Images (*.s2p)"));
    return fileName;
}

void FormCombine::on_pushButton_6_clicked()
{
    std::map<QString,std::map<QString,std::vector<std::pair<QString,QString> > > > pdata;
    std::vector<QString> m_freq_key;
    CParsefile m_parse;
    QString path = ui->lineEdit->text();
    QFile ls_file(path);
    if(!path.isEmpty() && ls_file.exists())
    {
        m_parse.Combine(pdata,m_freq_key,path,true);
    }
    path = ui->lineEdit_2->text();
     QFile ls_file2(path);
     if(!path.isEmpty() && ls_file2.exists())
     {
         m_parse.Combine(pdata,m_freq_key,path,false);
     }

     path = ui->lineEdit_3->text();
      QFile ls_file3(path);
     if(!path.isEmpty() && ls_file3.exists())
     {
         m_parse.Combine(pdata,m_freq_key,path,false);
     }

     path = ui->lineEdit_4->text();
     QFile ls_file4(path);
     if(!path.isEmpty() && ls_file4.exists())
     {
         m_parse.Combine(pdata,m_freq_key,path,false);
     }

     path = ui->lineEdit_5->text();
     QFile ls_file5(path);
     if(!path.isEmpty() && ls_file5.exists())
     {
         m_parse.Combine(pdata,m_freq_key,path,false);
     }

    std::vector<QString> m_list;
    m_list.push_back("S11");
    m_list.push_back("S21");
    m_list.push_back("S12");
    m_list.push_back("S22");
    QString name = ui->lineEdit_6->text();
    QFile  cur_file(name);
    if(!cur_file.open(QFile::ReadWrite|QFile::Text)){
        qDebug()<< name << "open failed!";
        return;
    }
    QTextStream out(&cur_file);

    out<<"!Agilent Technologies,N5242A,MY53222239,A.09.80.20"<<endl;
    out<<"!Agilent N5242A: A.09.80.20"<<endl;
    out<<"!Date: Thursday, May 15, 2014 12:19:11"<<endl;
    out<<"!Correction: S11(Full 2 Port(1,2))"<<endl;
    out<<"!S21(Full 2 Port(1,2))"<<endl;
    out<<"!S12(Full 2 Port(1,2))"<<endl;
    out<<"!S22(Full 2 Port(1,2))"<<endl;
    out<<"!S2P File: Measurements: S11, S21, S12, S22:"<<endl;
    out<<" # Hz S  dB   R 50"<<endl;

    for(size_t i =0;i<m_freq_key.size();++i)
    {
        QString  cur_freq = m_freq_key.at(i);
        if(pdata.count(cur_freq)>0)
        {
           out<<cur_freq<<" ";
            for(size_t j =0;j<m_list.size();++j)
            {
                QString key = m_list.at(j);
                if(pdata[cur_freq].count(key)>0)
                {
                   std::vector<std::pair<QString,QString> > ls_vec = pdata[cur_freq][key];
                   double   ls_db=0;
                   double   ls_phase = 0;
                   int size =ls_vec.size();
                   for(int k =0;k<size;++k)
                   {
                        ls_db += (ls_vec.at(k).first).toDouble();
                        ls_phase += (ls_vec.at(k).second).toDouble();
                   }
                    ls_db    = ls_db/size;
                    ls_phase = ls_phase/size;

                    out<<QString::number(ls_db,'f')<<" "<<QString::number(ls_phase,'f')<<" ";
                }else
                 out<<"0 0 ";
            }

        }
         out<<endl;

    }
     cur_file.close();
}

void FormCombine::on_pushButton_7_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "/",
                               tr("Images (*.s2p)"));
    ui->lineEdit_6->setText(fileName);
}

void FormCombine::on_pushButton_clicked()
{
    ui->lineEdit->setText(get_file());
}

void FormCombine::on_pushButton_2_clicked()
{
     ui->lineEdit_2->setText(get_file());
}

void FormCombine::on_pushButton_3_clicked()
{
     ui->lineEdit_3->setText(get_file());
}

void FormCombine::on_pushButton_4_clicked()
{
     ui->lineEdit_4->setText(get_file());
}

void FormCombine::on_pushButton_5_clicked()
{
     ui->lineEdit_5->setText(get_file());
}
