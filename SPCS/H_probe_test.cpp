#include "H_probe_test.h"
#include "ui_H_probe_test.h"
#include "vnadapter.h"
#include <QMessageBox>
#include <QFile>
#include "teleswitch.h"
#include <QFileDialog>
#include  "tswmatrixs.h"
#include <QStandardPaths>
#include <QDateTime>

H_probe_test::H_probe_test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H_probe_test)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    init();
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    connect(this,SIGNAL(test_finshed()),this,SLOT(end_test()));
    connect(this,SIGNAL(cur_pos(int)),this,SLOT(update_cur_pos(int)));
}

H_probe_test::~H_probe_test()
{
    delete ui;
}

void H_probe_test::init()
{
    ui->lineEdit_startfreq->setText("8");
    ui->lineEdit_power->setText("-20");
    ui->lineEdit_if->setText("1");
    ui->lineEdit_stopfreq->setText("12");
    ui->lineEdit_freq_iter->setText("201");
    ui->comboBox_if->setCurrentIndex(1);
    ui->comboBox_start->setCurrentIndex(3);
    ui->comboBox_stop->setCurrentIndex(3);

    ui->checkBox_S11->setChecked(false);
    ui->checkBox_S21->setChecked(false);
    ui->checkBox_S22->setChecked(true);
    ui->checkBox_S12->setChecked(true);
    push_checkbox();
    on_groupBox_4_clicked();
    ui->checkBox_elec_switch->setChecked(true);
    ui->lineEdit_save_path->setText(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)\
                                    +QString("/")+QDateTime::currentDateTime().toString("yyyyMMdd")+QString("/"));
}


void H_probe_test::on_pushButton_vna_reset_clicked()
{
    if(VNAdapter::instance()->connect())
    {
        QMessageBox msgBox;
        QString text = CVTS::GBKToUnicode::toUnicode("将重置矢网.");
        msgBox.setText(text);
        QString note =  CVTS::GBKToUnicode::toUnicode("是否继续？");
        msgBox.setInformativeText(note);
        msgBox.setStandardButtons(QMessageBox::Ok |QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            VNAdapter::instance()->reset();
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
    }
    else
    {
        QString ls_title = CVTS::GBKToUnicode::toUnicode("警告");
        QString ls_com   = CVTS::GBKToUnicode::toUnicode("矢网连接失败！");
        QMessageBox mes;
        mes.setText(ls_com);
        mes.setWindowTitle(ls_title);
        mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.exec();
    }
}

void H_probe_test::on_pushButtonapply_clicked()
{
    double start_freq = ui->lineEdit_startfreq->text().toDouble()\
            * pow(1000.0,ui->comboBox_start->currentIndex());
    double stop_freq = ui->lineEdit_stopfreq->text().toDouble()\
            * pow(1000.0,ui->comboBox_stop->currentIndex());
    double IF = ui->lineEdit_if->text().toDouble() * pow(1000.0,ui->comboBox_if->currentIndex());
    double power = ui->lineEdit_power->text().toDouble();
    if(start_freq > stop_freq)
    {
        QString ls_title = CVTS::GBKToUnicode::toUnicode("警告");
        QString ls_com   = CVTS::GBKToUnicode::toUnicode("开始频率大于结束频率");
        QMessageBox mes;
        mes.setText(ls_com);
        mes.setWindowTitle(ls_title);
        mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.exec();
    }else
    {
        if(VNAdapter::instance()->connect())
        {
            VNAdapter::instance()->delAll();

            m_s11  = ui->checkBox_S11->isChecked();
            m_s22  = ui->checkBox_S22->isChecked();
            m_s21  = ui->checkBox_S21->isChecked();
            m_s12  = ui->checkBox_S12->isChecked();

            if(m_s11)
                VNAdapter::instance()->set_trace_S11();
            if(m_s12)
                VNAdapter::instance()->set_trace_S12();
            if(m_s21)
                VNAdapter::instance()->set_trace_S21();
            if(m_s22)
                VNAdapter::instance()->set_trace_S22();


            VNAdapter::instance()->set_freq(start_freq,stop_freq,ui->lineEdit_freq_iter->text().toInt());

            VNAdapter::instance()->continue_triger();
            VNAdapter::instance()->set_IF_bandwidth(IF);
            VNAdapter::instance()->set_power(power);

            //            VNAdapter::instance()->Internal_trigger();
            //            VNAdapter::instance()->continue_triger();
        }else
        {
            QString ls_title = CVTS::GBKToUnicode::toUnicode("警告");
            QString ls_com   = CVTS::GBKToUnicode::toUnicode("矢网连接失败！");
            QMessageBox mes;
            mes.setText(ls_com);
            mes.setWindowTitle(ls_title);
            mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
            mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
            mes.exec();
        }
    }
}

void H_probe_test::on_pushButton_manual_clicked()
{
    if(VNAdapter::instance()->connect())
        VNAdapter::instance()->continue_triger();
}

void H_probe_test::on_pushButton_interal_clicked()
{
    if(VNAdapter::instance()->connect())
        VNAdapter::instance()->Internal_trigger();
}



void H_probe_test::on_pushButton_update_trace_clicked()
{
    VNAdapter::instance()->connect();
    VNAdapter::instance()->delAll();
    if(ui->checkBox_S11->isChecked())
    {
        VNAdapter::instance()->set_trace_S11();
    }
    if(ui->checkBox_S22->isChecked())
    {
        VNAdapter::instance()->set_trace_S22();
    }
    if(ui->checkBox_S12->isChecked())
    {
        VNAdapter::instance()->set_trace_S12();
    }
    if(ui->checkBox_S21->isChecked())
    {
        VNAdapter::instance()->set_trace_S21();
    }
}

void H_probe_test::on_pushButton_select_path_clicked()
{
    QString  p_path = QFileDialog::getExistingDirectory(this,tr("Collect Data"),\
                                                        "/Users/607/Desktop");

    if(p_path.isEmpty()) return;
    ui->lineEdit_save_path->setText(p_path);
}



void H_probe_test::calc_freq()
{
    m_freq.clear();
    //////计算频点
    double end_   = ui->lineEdit_stopfreq ->text().toDouble();
    double start_ = ui->lineEdit_startfreq->text().toDouble();
    if(end_ == start_)
    {
        QString fre_cur = QString::number(ui->lineEdit_startfreq->text().toDouble()\
                                          *pow(1000.0,ui->comboBox_start->currentIndex()),'f',0);
        m_freq.push_back(fre_cur);
    }else
    {
        double step   = (end_*pow(1000.0,ui->comboBox_stop->currentIndex())\
                         - start_*pow(1000.0,ui->comboBox_start->currentIndex()))/(ui->lineEdit_freq_iter->text().toInt()-1);
        for(int i=0; i<ui->lineEdit_freq_iter->text().toInt(); i++)
        {
            QString fre_cur =QString::number(ui->lineEdit_startfreq->text().toDouble()\
                                             *pow(1000.0,ui->comboBox_start->currentIndex()) + step * i,'f',0);
            m_freq.push_back(fre_cur);
        }

    }
}

void H_probe_test::on_pushButton_test_clicked()
{
    if(ui->lineEdit_save_path->text().isEmpty() ||\
            ui->lineEdit_collect_time->text().isEmpty()\
            ||ui->lineEdit_dec_sleep_time->text().isEmpty()\
            ||ui->lineEdit__wait_time->text().isEmpty())
    {
        QMessageBox::information(NULL,tr("Message"),tr("Input error !"));
        return ;
    }

    calc_freq();
    m_wait_times   = ui->lineEdit__wait_time->text().toDouble();
    m_collect_nums = ui->lineEdit_collect_time->text().toInt();
    m_sleep_time   = ui->lineEdit_dec_sleep_time->text().toDouble();
    m_switch_time  = ui->lineEdit_switch_time->text().toDouble();
    m_is_ele_switch = ui->checkBox_elec_switch->isChecked();
    if(!VNAdapter::instance()->connect())
    {
        QString ls_title = CVTS::GBKToUnicode::toUnicode("警告");
        QString ls_com   = CVTS::GBKToUnicode::toUnicode("矢网连接失败！");
        QMessageBox mes;
        mes.setText(ls_com);
        mes.setWindowTitle(ls_title);
        mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.exec();
        return ;
    }

    VNAdapter::instance()->continue_triger();

    m_save_path = ui->lineEdit_save_path->text();

    m_s11   = ui->checkBox_S11->isChecked();
    m_s22   = ui->checkBox_S22->isChecked();
    m_s21   = ui->checkBox_S21->isChecked();
    m_s12   = ui->checkBox_S12->isChecked();

    QDir dir;
    dir.mkpath(m_save_path);

    getCheckStatus();
    ui->progressBar->setRange(0,m_collect_nums*m_checkbox.size());
    ::Sleep(50);

    emit begin_test();
}

void H_probe_test::test()
{
    for(int i =0;i<m_collect_nums;++i)
    {
        TEleSwitch::instance()->turn_off_all();
        for(int j =0;j<m_checkbox.size();++j)
        {
            emit cur_pos(i*m_checkbox.size()+j+1);
            if(!m_elec[j]) continue;
            TEleSwitch::instance()->turn_off_all();
            TSWMatrixs::instance()->turn_on(CVTS::Matrix(j));

            ::Sleep(m_sleep_time);
            if(1)
            {
                QString off_path = m_save_path+QString("/port%1_off.txt").arg(j+1);
                QFile file_off(off_path);
                QTextStream out_off(&file_off);

                if(!file_off.open(QFile::Append|QFile::Text))
                {
                    qDebug()<< off_path << "open failed!";
                }

                collect_data(out_off);

                if(file_off.isOpen())
                    file_off.close();
            }

            if(m_is_ele_switch)
            {
                QString on_path = m_save_path+QString("/port%1_on.txt").arg(j+1);
                QFile file_on(on_path);
                QTextStream out_on(&file_on);
                if(!file_on.open(QFile::Append|QFile::Text))
                {
                    qDebug()<< on_path << "open failed!";
                }

                ////////////////////////////////////////////////////////////////////////
                ::Sleep(m_switch_time);
                TEleSwitch::instance()->turn_on(CVTS_Decetor(j));
                ::Sleep(m_sleep_time);
                ////////////////////////////////////////////////////////////////////////

                collect_data(out_on);
                if(file_on.isOpen())
                    file_on.close();
            }
        }
        if(i!= m_collect_nums-1)
        {
            TEleSwitch::instance()->turn_off_all();
            ::Sleep(m_wait_times);
        }
    }
    emit test_finshed();
    emit cur_pos(m_collect_nums*m_checkbox.size());
    qDebug()<<"test finshed";
}


void H_probe_test::collect_data(QTextStream &out)
{
    QString S11,S12,S22,S21;
    QStringList ls_list_S11,ls_list_S22,ls_list_S12,ls_list_S21;
    double freqsize = m_freq.size();

    if(m_s11)
    {
        S11  =   VNAdapter::instance()->collect_S11();
        ls_list_S11 = S11.split(QRegExp(","));
    }
    if(m_s22)
    {
        S22  =   VNAdapter::instance()->collect_S22();
        ls_list_S22 = S22.split(QRegExp(","));
    }
    if(m_s12)
    {
        S12  =   VNAdapter::instance()->collect_S12();
        ls_list_S12 = S12.split(QRegExp(","));
    }
    if(m_s21)
    {
        S21  =   VNAdapter::instance()->collect_S21();
        ls_list_S21 = S21.split(QRegExp(","));
    }

    if(ls_list_S22.size()  == freqsize*2 &&\
            ls_list_S22.size() == freqsize*2&&\
            ls_list_S22.size() == freqsize*2&&\
            ls_list_S22.size() == freqsize*2)
    {
        for(int k=0;k<freqsize;++k)
        {
            out<<m_freq.at(k);
            if(m_s11)
            {
                double real = ls_list_S11.at(2*k).toDouble();
                double imag = ls_list_S11.at(2*k+1).toDouble();
                double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                double phase = VNAdapter::instance()->genPhase(real,imag);
                out<<","<<db << "," << phase;
            }
            if(m_s22)
            {
                double real = ls_list_S22.at(2*k).toDouble();
                double imag = ls_list_S22.at(2*k+1).toDouble();
                double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                double phase = VNAdapter::instance()->genPhase(real,imag);
                out<<","<<db << "," << phase;
            }
            if(m_s12)
            {
                double real = ls_list_S12.at(2*k).toDouble();
                double imag = ls_list_S12.at(2*k+1).toDouble();
                double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                double phase = VNAdapter::instance()->genPhase(real,imag);
                out<<","<<db << "," << phase;
            }
            if(m_s21)
            {
                double real = ls_list_S21.at(2*k).toDouble();
                double imag = ls_list_S21.at(2*k+1).toDouble();
                double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                double phase = VNAdapter::instance()->genPhase(real,imag);
                out<<","<<  db << "," << phase;
            }
            out<<endl;
        }
    }
}

void H_probe_test::collect_S22(QTextStream &out)
{
    QString S22  =   VNAdapter::instance()->collect_S22();
    QStringList ls_list_S22 = S22.split(QRegExp(","));

    double freqsize = m_freq.size();
    if(ls_list_S22.size() == freqsize*2)
    {
        for(int k=0;k<freqsize;++k)
        {
            out<<m_freq.at(k)<<",";

            double real = ls_list_S22.at(2*k).toDouble();
            double imag = ls_list_S22.at(2*k+1).toDouble();
            double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
            double phase = VNAdapter::instance()->genPhase(real,imag);
            out<<  db << "," << phase<<","<<endl;
        }
    }
}

void H_probe_test::end_test()
{
    QString title = GBKToUnicode::toUnicode("提示");
    QMessageBox  mes;
    mes.setWindowIcon(QIcon(".\\image\\607logo-6464.png"));
    //  mes.setParent(NULL);
    mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    QString context  =GBKToUnicode::toUnicode("测试完成！");
    mes.setText(context);
    mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    mes.setWindowTitle(title);
    mes.exec();
}

void H_probe_test::update_cur_pos(int value)
{
    ui->progressBar->setValue(value);
}


void H_probe_test::on_groupBox_4_clicked()
{
    for(int i =0;i<m_checkbox.size();++i)
    {
        m_checkbox[i]->setChecked(ui->groupBox_4->isChecked());
    }
}

void H_probe_test::push_checkbox()
{
    m_checkbox.push_back(ui->checkBox_ele_1);
    m_checkbox.push_back(ui->checkBox_ele_2);
    m_checkbox.push_back(ui->checkBox_ele_3);
    m_checkbox.push_back(ui->checkBox_ele_4);
    m_checkbox.push_back(ui->checkBox_ele_5);
    m_checkbox.push_back(ui->checkBox_ele_6);
    m_checkbox.push_back(ui->checkBox_ele_7);
    m_checkbox.push_back(ui->checkBox_ele_8);
    m_checkbox.push_back(ui->checkBox_ele_9);
    m_checkbox.push_back(ui->checkBox_ele_10);
    m_checkbox.push_back(ui->checkBox_ele_11);
    m_checkbox.push_back(ui->checkBox_ele_12);
    m_checkbox.push_back(ui->checkBox_ele_13);
    m_checkbox.push_back(ui->checkBox_ele_14);
    m_checkbox.push_back(ui->checkBox_ele_15);
    m_checkbox.push_back(ui->checkBox_ele_16);
}

void H_probe_test::getCheckStatus()
{
    for(int i =0;i<m_checkbox.size();++i)
    {
        m_elec[i]= m_checkbox[i]->isChecked();
    }
}
