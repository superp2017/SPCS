#include "combinetools.h"
#include "ui_combinetools.h"
#include <QFileDialog>
#include  <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>

CombineTools::CombineTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CombineTools)
{
    ui->setupUi(this);
    init_tablewidget();
    this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

CombineTools::~CombineTools()
{
    delete ui;
}

void CombineTools::init_tablewidget()
{
    QStringList ls_list;
    ls_list << "Files Path";
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setHorizontalHeaderLabels(ls_list);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(0,250);
}



void CombineTools::on_pushButton_combine_clicked()
{
    QString path = ui->lineEdit_savepath->text();
    if(path.isEmpty())
    {

        QString ls_title = "Note";
        QString ls_com   = "Save path is not empty.";
        QMessageBox mes;
        mes.setText(ls_com);
        mes.setWindowTitle(ls_title);
        mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.exec();
        return ;
    }
    QFile ls_file(path);
    std::map<QString,std::map<QString, std::vector<std::pair<QString,QString> > > > m_data;
    std::vector<QString> m_freq;
    for(int i =0;i<ui->tableWidget->rowCount();++i)
    {
        QTableWidgetItem *item =  ui->tableWidget->item(i,0);
        if(item)
        {
            QString filename =  item->text();
            QFile cur_file(filename);
            if(!cur_file.exists()) return;
            if(i ==0)
                m_parse.combine_data(m_data,m_freq,filename,true);
            else
                m_parse.combine_data(m_data,m_freq,filename);

        }
    }


    if(ls_file.exists()) {
        if(!ls_file.remove())
        {
            QMessageBox::information(NULL,tr("Message"),tr("file is open !"));
            return;
        }
    }
    if(!ls_file.open(QFile::ReadWrite|QFile::Text)){
        qDebug()<< path << "open failed!";
        QMessageBox::information(NULL,tr("Message"),tr("file open filed !"));
        return;
    }
    QTextStream out(&ls_file);
    out<<"!Agilent Technologies,N5242A,MY53222239,A.09.80.20"<<endl;
    out<<"!Agilent N5242A: A.09.80.20"<<endl;
    out<<"!Date: "<<QDateTime::currentDateTime().toString("ddd, MMMM d, yyyy hh:mm:ss")<<endl;
    out<<"!Correction: S11(Full 2 Port(1,2))";
    out<<"!S21(Full 2 Port(1,2))"<<endl;
    out<<"!S12(Full 2 Port(1,2))"<<endl;
    out<<"!S22(Full 2 Port(1,2))"<<endl;
    out<<"!S2P File: Measurements: S11, S21, S12, S22:"<<endl;
    out<<"# Hz S  dB   R 50"<<endl;
    std::vector<QString> ls_list;
    ls_list.push_back("S11");
    ls_list.push_back("S21");
    ls_list.push_back("S12");
    ls_list.push_back("S22");


    for(size_t i =0;i<m_freq.size();++i)
    {
        QString cur_freq = m_freq.at(i);
        if(m_data.count(cur_freq) >0)
        {
            out<<cur_freq<<" ";
            for(size_t j =0;j<ls_list.size();++j)
            {
                QString cur_key = ls_list.at(j);
                if(m_data[cur_freq].count(cur_key) >0)
                {
                    std::vector<std::pair<QString,QString> > ls_data =  m_data[cur_freq][cur_key];
                    double ls_db    = 0;
                    double ls_phase = 0;
                    int size = ls_data.size();
                    for(int k=0;k<size;++k)
                    {
                        ls_db    +=   (ls_data.at(k).first).toDouble();
                        ls_phase +=   (ls_data.at(k).second).toDouble();
                    }
                    ls_db    = ls_db/size;
                    ls_phase = ls_phase/size;
                    out<<QString::number(ls_db,'f')<<" "<<QString::number(ls_phase,'f')<<" ";
                }else
                    out<<"0 0 ";
            }
            out<<endl;
        }
    }

    QString ls_title = CVTS::GBKToUnicode::toUnicode("提示");
    QString ls_com   = CVTS::GBKToUnicode::toUnicode("合并成功!");
    QMessageBox mes;
    mes.setText(ls_com);
    mes.setWindowTitle(ls_title);
    mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    mes.exec();
    ls_file.close();
}

void CombineTools::on_pushButton_seclect_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),\
                                                    "/Users/607/Desktop",\
                                                    tr("CalFiles (*.s2p)"));
    if(filename.isEmpty()) return;
    ui->lineEdit_savepath->setText(filename);
}

void CombineTools::on_pushButton_delall_clicked()
{
    int n = ui->tableWidget->rowCount();
    for(int i=0;i<n;++i)
    {
        ui->tableWidget->removeRow(0);
    }
}

void CombineTools::on_pushButton_del_clicked()
{
    if(ui->tableWidget->currentRow()>= 0 && ui->tableWidget->currentItem())
    {
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    }
}

void CombineTools::add_item(QString path)
{
    QFile ls_file(path);
    if(ls_file.exists())
    {
        qDebug()<<path;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setRowHeight(ui->tableWidget->rowCount()-1, 20);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(path));
        //  AllItemAlignment(ui->tableWidget->rowCount()-1);

    }else
    {
        QString ls_title = "Note";
        QString ls_com   = path + "is not exit.";
        QMessageBox mes;
        mes.setText(ls_com);
        mes.setWindowTitle(ls_title);
        mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.exec();
    }

}


void CombineTools::on_pushButton_add_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      "Select one or more .s2p files to open",\
                                                      "/Users/607/Desktop",\
                                                      "Files (*.s2p)");
    for(int i =0;i<files.size();++i)
    {
        add_item(files.at(i));
    }
}
