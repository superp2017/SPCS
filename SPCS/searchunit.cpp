#include "searchunit.h"
#include "ui_searchunit.h"
#include "twoshorttoid.h"
#include <QFileDialog>
#include "projectmanager.h"

SearchUnit::SearchUnit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchUnit)
{
    ui->setupUi(this);
    ui->radioButton_id->setChecked(true);
    ui->lineEdit_id->setEnabled(true);
    ui->lineEdit_col->setEnabled(false);
    ui->lineEdit_row->setEnabled(false);
}

SearchUnit::~SearchUnit()
{
    delete ui;
}

void SearchUnit::on_pushButton_clicked()
{
    int id  = 0;
    if(ui->radioButton_id->isChecked())
    {
        if(ui->lineEdit_id->text().isEmpty()) return;     
        short row = 0;
        short col = 0;
        id = ui->lineEdit_id->text().toInt();
        TwoShortToId::instance()->IdToAddr(id,row,col);
        ui->lineEdit_row->setText(QString("%1").arg(row));
        ui->lineEdit_col->setText(QString("%1").arg(col));
    }else
    {
        if(ui->lineEdit_col->text().isEmpty() || ui->lineEdit_row->text().isEmpty()) return;
        id  =  TwoShortToId::instance()->AddrToId(ui->lineEdit_row->text().toShort(),ui->lineEdit_col->text().toShort());
        QString str_id = QString("%1").arg(id);
        ui->lineEdit_id->setText(str_id);
    }
    emit showUnit(id);
}


void SearchUnit::on_radioButton_id_clicked()
{
    ui->lineEdit_id->setEnabled(true);
    ui->lineEdit_col->setEnabled(false);
    ui->lineEdit_row->setEnabled(false);
}

void SearchUnit::on_radioButton_rowcol_clicked()
{
    ui->lineEdit_id->setEnabled(false);
    ui->lineEdit_col->setEnabled(true);
    ui->lineEdit_row->setEnabled(true);
}

void SearchUnit::on_pushButton_clear_clicked()
{
    emit close_all();
}

void SearchUnit::on_pushButton_2_clicked()
{
    QString path = ProjectManager::instance()->get_path();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),path,tr("ID (*.id)"));
    if(!fileName.isEmpty())
        emit showIDs(fileName);
}
