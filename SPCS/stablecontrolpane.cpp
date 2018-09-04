#include "stablecontrolpane.h"
#include "ui_stablecontrolpane.h"
#include <QFileDialog>

StableControlPane::StableControlPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StableControlPane)
{
    ui->setupUi(this);
    ui->comboBox_freq_S->addItem("S21");
    ui->comboBox_freq_S->addItem("S11");
    ui->comboBox_freq_S->addItem("S22");
    ui->comboBox_freq_S->addItem("S12");
    connect(ui->comboBox_freq,SIGNAL(currentIndexChanged(int)),\
            this,SLOT(query_data()));
    connect(ui->comboBox_freq_S,SIGNAL(currentIndexChanged(int)),\
            this,SLOT(query_data()));
    connect(ui->checkBox_to_1,SIGNAL(clicked())\
            ,this,SLOT(query_data()),Qt::QueuedConnection);
    connect(ui->pushButton_query,SIGNAL(clicked()),\
            this,SLOT(query_data()));

}

StableControlPane::~StableControlPane()
{
    delete ui;
}

void StableControlPane::clear_combox()
{
    ui->comboBox_freq->clear();
    ui->checkBox_to_1->setChecked(false);
}

void StableControlPane::on_pushButton_load_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),"/Users/607/Desktop",\
                                                    tr("Stable Data (*.stable)"));
    if(filename.isEmpty()) return;
    ui->lineEdit_path->setText(filename);
    emit loaddata(filename);
}

void StableControlPane::query_data()
{
   emit query(ui->comboBox_freq->currentText(),ui->comboBox_freq_S->currentText()\
              ,ui->checkBox_to_1->isChecked());
}


void StableControlPane::add_item(QString freq)
{
    ui->comboBox_freq->addItem(freq);
}
