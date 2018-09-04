#include "caldiffercontrolpane.h"
#include "ui_caldiffercontrolpane.h"
#include <QFileDialog>
#include <QMessageBox>

CalDifferControlPane::CalDifferControlPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalDifferControlPane)
{
    ui->setupUi(this);
}

CalDifferControlPane::~CalDifferControlPane()
{
    delete ui;
}

void CalDifferControlPane::on_pushButton_file1_clicked()
{
    QString path = get_files();
    ui->lineEdit_file_1->setText(path);
}

void CalDifferControlPane::on_pushButton_file2_clicked()
{
    QString path = get_files();
    ui->lineEdit_fille_2->setText(path);
}

void CalDifferControlPane::on_pushButton_cpmpare_clicked()
{
    QString path1 = ui->lineEdit_file_1->text();
    QFile ls_file(path1);
    if(path1.isEmpty() || !ls_file.exists())
    {
        file_not_exist();
        return ;
    }
    QString path2 = ui->lineEdit_fille_2->text();
    QFile ls_file2(path2);
    if(path2.isEmpty() || !ls_file2.exists())
    {
        file_not_exist();
        return ;
    }
    emit  compare(path1,path2);
}


QString CalDifferControlPane::get_files()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),"/Users/607/Desktop",\
                                                    tr("Cal (*.clibs)"));
    return filename;
}

void CalDifferControlPane::file_not_exist()
{
    QMessageBox::information(NULL,tr("ERROR"),tr("File is not exist !"));
}


void CalDifferControlPane::on_pushButton_file3_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),"/Users/607/Desktop",\
                                                    tr("Cal (*.clibs)"));
    ui->lineEdit->setText(filename);

}

void CalDifferControlPane::on_pushButton_clear_clicked()
{
    emit clear_view();
    ui->lineEdit->clear();
    ui->lineEdit_file_1->clear();
    ui->lineEdit_fille_2->clear();
    ui->lineEdit_path_s2p->clear();
}

void CalDifferControlPane::on_pushButton_clicked()
{
    QString path = ui->lineEdit->text();
    QFile ls_file(path);
    if(path.isEmpty()|| !ls_file.exists())
    {
        file_not_exist();
        return ;
    }
    emit add_curve(ui->lineEdit->text());
}

void CalDifferControlPane::on_pushButton_file3_S2P_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),"/Users/607/Desktop",\
                                                    tr("S2P (*.s2p)"));
    ui->lineEdit_path_s2p->setText(filename);
}

void CalDifferControlPane::on_pushButton_add_s2p_clicked()
{
    QString path = ui->lineEdit_path_s2p->text();
    QFile ls_file(path);
    if(path.isEmpty()|| !ls_file.exists())
    {
        file_not_exist();
        return ;
    }
    emit add_s2p(ui->lineEdit_path_s2p->text());
}
