#include "m_testinitdlg.h"
#include "ui_m_testinitdlg.h"
#include "m_setpulse.h"
#include "m_setdev.h"
#include "handlecontrol.h"

M_TestInitDlg::M_TestInitDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::M_TestInitDlg)
{
    ui->setupUi(this);
    connect(ui->radioButton_receive,SIGNAL(clicked()),this,SLOT(enablePulse()));
    connect(ui->radioButton_send,SIGNAL(clicked()),this,SLOT(enablePulse()));
   this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));

}

M_TestInitDlg::~M_TestInitDlg()
{
    delete ui;
}

void M_TestInitDlg::reset()
{
    init_workstatue();
    init_test_job();
}

void M_TestInitDlg::init()
{
    reset();
}

void M_TestInitDlg::get_param(TEST_TYPE &type, WORK_STATUS &status, QString &caltable)
{
    if(ui->radioButton_filed_test->isChecked())
    {
        if(ui->radioButton_magn->isChecked())
        {
            type = FILED_MAGN;

        }else if(ui->radioButton_phase->isChecked())
        {
            type = FILED_PHASE;
        }else
        {
            type = FILED_MAGN_PHASE;
        }

    }else
    {
        type = CONFIG_PHASE;
    }

    if(ui->radioButton_receive->isChecked())
    {
        status = RECEIVE;
    }else
    {
        status = SEND;
    }
    caltable = ui->lineEdit_cfg_table->text();
}


void M_TestInitDlg::set_test_type(TEST_TYPE type)
{
    if(type == FILED_MAGN)
    {
        ui->radioButton_filed_test->setChecked(true);
        ui->radioButton_magn->setChecked(true);
    }
    if(type == FILED_PHASE)
    {
        ui->radioButton_filed_test->setChecked(true);
        ui->radioButton_phase->setChecked(true);
    }
    if(type == FILED_MAGN_PHASE)
    {
        ui->radioButton_filed_test->setChecked(true);
        ui->radioButton_magn_phase->setChecked(true);
    }
    if(type == CONFIG_PHASE)
        ui->radioButton_phase_test->setChecked(true);
}

void M_TestInitDlg::set_work_status(WORK_STATUS status)
{
    if(status == SEND)
        ui->radioButton_send->setChecked(true);
    else
        ui->radioButton_receive->setChecked(true);
    enablePulse();
}

void M_TestInitDlg::set_cfg_table(QString table)
{
    ui->lineEdit_cfg_table->setText(table);
}

void M_TestInitDlg::on_m_OK_clicked()
{
    done(0);
}

void M_TestInitDlg::on_n_cancel_clicked()
{
    done(-1);
}

void M_TestInitDlg::on_radioButton_filed_test_clicked()
{
   // ui->groupBox_magn_range->hide();
   // ui->groupBox_filed->show();
   // ui->groupBox_filed->setGeometry(93,20,101,81);
    ui->groupBox_filed->setEnabled(true);

}

void M_TestInitDlg::on_radioButton_phase_test_clicked()
{
     ui->groupBox_filed->setEnabled(false);
//    ui->groupBox_filed->hide();
//    ui->groupBox_magn_range->show();
//    ui->groupBox_magn_range->setParent(ui->groupBox_2);
//    ui->groupBox_magn_range->setGeometry(93,20,101,81) ;
}

void M_TestInitDlg::init_test_job()
{
    ui->radioButton_filed_test->setChecked(true);
    ui->radioButton_magn_phase->setChecked(true);
    ui->radioButton_phase_test->setChecked(true);
    on_radioButton_phase_test_clicked();
}

void M_TestInitDlg::init_workstatue()
{
    ui->radioButton_receive->setChecked(true);
}

void M_TestInitDlg::enablePulse()
{
    connect(this,SIGNAL(Pulse(bool)),M_SetPulse::instance(),SLOT(enablePulse(bool)));
    connect(this,SIGNAL(Pulse(bool)),M_SetDev::instance(),SLOT(sendstatus(bool)));
    emit Pulse(ui->radioButton_send->isChecked());
}


void M_TestInitDlg::on_pushButton_manu_test_clicked()
{
    HandleControl::instance()->showNormal();
    done(0);
}

void M_TestInitDlg::on_pushButton_select_cfg_table_clicked()
{
    QString str = QApplication::applicationDirPath() + DATA_PATH ;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Cal File"), str,\
                                                    tr("CalTable (*.cal)"));
    QFile ls_file(fileName);
    if(!ls_file.exists())
    {
        QString ls_title = CVTS::GBKToUnicode::toUnicode("提示");
        QString ls_com   = CVTS::GBKToUnicode::toUnicode("校准文件不存在.");
        QMessageBox mes;
        mes.setText(ls_com);
        mes.setWindowTitle(ls_title);
        mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.exec();
        return ;
    }
    ui->lineEdit_cfg_table->setText(fileName);
}
