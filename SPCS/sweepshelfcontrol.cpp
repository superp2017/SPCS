#include "sweepshelfcontrol.h"
#include "ui_sweepshelfcontrol.h"
#include "sweepshelf.h"
#include "_global.h"
#include <QDoubleValidator>
#include <QIntValidator>
#include <QMessageBox>

SweepShelfControl::SweepShelfControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SweepShelfControl)
{
    ui->setupUi(this);
    ui->comboBox->addItem("SPEED1");
    ui->comboBox->addItem("SPEED2");
    ui->comboBox->addItem("SPEED3");
    ui->comboBox->addItem("SPEED4");
    ui->comboBox->addItem("SPEED5");
    ui->comboBox->addItem("SPEED6");
    QIntValidator *pos = new QIntValidator(-12, 12, this);
    QDoubleValidator *dis = new QDoubleValidator(-750,750,2,this);
    ui->lineEdit_dis->setValidator(dis);
    ui->lineEdit_pos->setValidator(pos);
    ui->radioButton_dis->setChecked(true);
    ui->lineEdit_dis->setEnabled(true);
    ui->lineEdit_pos->setEnabled(false);
    ui->comboBox->setCurrentIndex(5);
   this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

SweepShelfControl::~SweepShelfControl()
{
    delete ui;
}

void SweepShelfControl::on_pushButton_open_clicked()
{
    SweepShelf::instance()->Open_DEV("COM4");
}

void SweepShelfControl::on_pushButton_close_clicked()
{
    SweepShelf::instance()->Close_DEV();
}

void SweepShelfControl::on_pushButton_org_clicked()
{
    SweepShelf::instance()->MOVE_TO_Origin();
}

void SweepShelfControl::on_pushButton_clear_clicked()
{
    SweepShelf::instance()->ClearWarnning();
}

void SweepShelfControl::on_pushButton_exit_clicked()
{
    this->hide();
}

void SweepShelfControl::on_pushButton_move_clicked()
{
    MOVESPEESD  speed = SPEED_1500_;
    if(ui->comboBox->currentIndex() == 0)
        speed = SPEED_0_100;
    if(ui->comboBox->currentIndex() == 1)
        speed = SPEED_100_300;
    if(ui->comboBox->currentIndex() == 2)
        speed = SPEED_300_500;
    if(ui->comboBox->currentIndex() == 3)
        speed = SPEED_500_1000;
    if(ui->comboBox->currentIndex() == 4)
        speed = SPEED_1000_1500;
    if(ui->comboBox->currentIndex() == 5)
        speed = SPEED_1500_;

    double distance = ui->lineEdit_dis->text().toDouble();
    if(ui->radioButton_dis->isChecked())
    {
        if(distance >750 || distance <-750)
        {
            QMessageBox mes;
            QString title = CVTS::GBKToUnicode::toUnicode("¾¯¸æ");
            QString text = CVTS::GBKToUnicode::toUnicode("³¬¹ýÒÆ¶¯·¶Î§£¡");
            mes.setText(text);
            mes.setWindowTitle(title);
            mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
            mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
            mes.exec();
        }else{
            SweepShelf::instance()->SetMoveSpeed(speed);
            ::Sleep(10);
            SweepShelf::instance()->MOVE_TO(distance) ;
        }
    }else
    {
        double pos = ui->lineEdit_pos->text().toInt();
        if(pos>12 || pos<-12) return;

        SweepShelf::instance()->SetMoveSpeed(speed);

        ::Sleep(10);
        pos *= -SWEEPSHELF_DISTANCE;
        qDebug()<<"pos"<<pos;
        if(pos>750) pos =750;
        if(pos<-750) pos = -750;
        SweepShelf::instance()->MOVE_TO(pos);
    }
}

void SweepShelfControl::on_radioButton_dis_clicked()
{
    ui->lineEdit_dis->setEnabled(true);
    ui->lineEdit_pos->setEnabled(false);
}

void SweepShelfControl::on_radioButton_loca_clicked()
{
    ui->lineEdit_pos->setEnabled(true);
    ui->lineEdit_dis->setEnabled(false);
}

void SweepShelfControl::disableMove(bool enable)
{
    ui->pushButton_move->setEnabled(enable);
    ui->pushButton_org->setEnabled(enable);
}


void SweepShelfControl::on_pushButtonquery_clicked()
{
    if(SweepShelf::instance()->IsMoveDone())
    {
        QString ls_title = CVTS::GBKToUnicode::toUnicode("ÌáÊ¾");
        QString ls_com   = CVTS::GBKToUnicode::toUnicode("É¨Ãè¼ÜÒÆ¶¯µ½Î»£¡");
        QMessageBox mes;
        mes.setText(ls_com);
        mes.setWindowTitle(ls_title);
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.exec();
    }
}
