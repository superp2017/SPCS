#include "m_set_times.h"
#include "ui_m_set_times.h"
#include "_global.h"
#include <QMessageBox>
#include <QFile>
#include "taskcenter_607.h"
#include <QDoubleValidator>
#include "tarray.h"
#include "mainwindow.h"
#include "m_setfreqdlg.h"

M_Set_Times::M_Set_Times(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::M_Set_Times)
{
    ui->setupUi(this);
    ui->lineEdit_elesw->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    ui->lineEdit_multe->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    ui->lineEdit_sweepshelf->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    ui->lineEdit_vna->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    ui->lineEdit_wave->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    init();
       this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

M_Set_Times::~M_Set_Times()
{
    delete ui;
}

void M_Set_Times::init()
{
    ui->lineEdit_elesw->setText("100");
    ui->lineEdit_multe->setText("30");
    ui->lineEdit_sweepshelf->setText("100");
    ui->lineEdit_vna->setText("0");
    ui->lineEdit_wave->setText("100");
    QString str = QApplication::applicationDirPath() + DATA_PATH+ "/607.map" ;
    ui->lineEdit_map->setText(str);
    QString array = QApplication::applicationDirPath() + DATA_PATH+ "/Array607.array" ;
    ui->lineEdit_array->setText(array);
    ui->spinBox_mp_nums->setMaximum(10);
    ui->spinBox_m_mp_nums->setMaximum(10);
    ui->spinBox_mp_nums->setValue(1);
    ui->spinBox_m_mp_nums->setValue(2);
    ui->lineEdit_base_delt_db->setText("-0.5");

}

void M_Set_Times::reload_param(QString wave, QString mule, \
                               QString eles, QString sweep,\
                               QString mp_time,QString m_mp_times)
{
    ui->lineEdit_wave->setText(wave);
    ui->lineEdit_multe->setText(mule);
    ui->lineEdit_elesw->setText(eles);
    ui->lineEdit_sweepshelf->setText(sweep);
    ui->spinBox_mp_nums->setValue(mp_time.toInt());
    ui->spinBox_m_mp_nums->setValue(m_mp_times.toInt());
}

void M_Set_Times::get_param(QString &wave,QString &mule, \
                            QString &eles, QString &sweep,\
                            QString &cfgmp_times,\
                            QString &m_mp_time,\
                            QString &pdelt_base_db)
{
    wave = ui->lineEdit_wave->text();
    mule = ui->lineEdit_multe->text();
    eles = ui->lineEdit_elesw->text();
    sweep= ui->lineEdit_sweepshelf->text();
    cfgmp_times = QString("%1").arg(ui->spinBox_mp_nums->value());
    m_mp_time   = QString("%1").arg(ui->spinBox_m_mp_nums->value());
    pdelt_base_db = ui->lineEdit_base_delt_db->text();
}

void M_Set_Times::on_pushButton_default_clicked()
{
    init();
}

void M_Set_Times::on_pushButtonload_clicked()
{
    QString str = QApplication::applicationDirPath() + DATA_PATH ;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), str,\
                                                    tr("MapFiles (*.map)"));
    QFile ls_file(fileName);
    if(!ls_file.exists())
    {
        QString ls_title = CVTS::GBKToUnicode::toUnicode("提示");
        QString ls_com   = CVTS::GBKToUnicode::toUnicode("映射文件不存在,请先生成阵面映射文件！");
        QMessageBox mes;
        mes.setText(ls_com);
        mes.setWindowTitle(ls_title);
        mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.exec();
        return ;
    }
    ui->lineEdit_map->setText(fileName);
}

void M_Set_Times::on_pushButtonload_2_clicked()
{
    QString str = QApplication::applicationDirPath() + DATA_PATH ;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), str,\
                                                    tr("ArrayFiles (*.array)"));
    QFile ls_file(fileName);
    if(!ls_file.exists())
    {
        QString ls_title = CVTS::GBKToUnicode::toUnicode("提示");
        QString ls_com   = CVTS::GBKToUnicode::toUnicode("阵面文件不存在,请先生成阵面文件！");
        QMessageBox mes;
        mes.setText(ls_com);
        mes.setWindowTitle(ls_title);
        mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.exec();
        return ;
    }
    ui->lineEdit_array->setText(fileName);
}


void M_Set_Times::on_pushButton_ok_clicked()
{
    QString fileName_map  = ui->lineEdit_map->text();
    QFile ls_file_map(fileName_map);
    if(!ls_file_map.exists())
    {
        QString ls_title = CVTS::GBKToUnicode::toUnicode("提示");
        QString ls_com   = CVTS::GBKToUnicode::toUnicode("映射文件不存在,请先生成阵面映射文件！");
        QMessageBox mes;
        mes.setText(ls_com);
        mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.setWindowTitle(ls_title);
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.exec();
        done(-1);
    }
    QString fileName_array  = ui->lineEdit_array->text();
    QFile ls_file_array(fileName_array);
    if(!ls_file_array.exists())
    {
        QString ls_title = CVTS::GBKToUnicode::toUnicode("提示");
        QString ls_com   = CVTS::GBKToUnicode::toUnicode("阵面文件不存在,请先生成阵面文件！");
        QMessageBox mes;
        mes.setText(ls_com);
        mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.setWindowTitle(ls_title);
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.exec();
        done(-1);
    }
    if(!TaskCenter_607::instance()->init_map(fileName_map))
    {
        done(-1);
        qDebug()<<"TaskCenter_607 init_map error";
    }
    if(!TaskCenter_607::instance()->init_array(fileName_array))
    {
        done(-1);
        qDebug()<<"TaskCenter_607 init_array error";
    }
    TaskCenter_607::instance()->init_times(ui->lineEdit_sweepshelf->text().toDouble()\
                                           ,ui->lineEdit_multe->text().toDouble()\
                                           ,ui->lineEdit_elesw->text().toDouble()\
                                           ,ui->lineEdit_wave->text().toDouble()\
                                           ,ui->lineEdit_vna->text().toDouble(),\
                                           ui->spinBox_mp_nums->value(),\
                                           ui->spinBox_m_mp_nums->value(),\
                                           ui->lineEdit_base_delt_db->text().toDouble(),\
                                           ui->checkBox_disturb->isChecked());
    TArray::instance()->init_data(TaskCenter_607::instance()->get_radars(),TaskCenter_607::instance()->get_id());

    TaskCenter_607::instance()->init_freq(M_SetFreqdlg::instance()->get_freq());

    ::Sleep(100);
    QString str = ProjectManager::instance()->get_path() + PARAM_PATH ;
    ls_file_map.copy(str+"/"+ProjectManager::instance()->get_name()+".map");
    ls_file_array.copy(str+"/"+ProjectManager::instance()->get_name()+".array");
    done(123);
}
