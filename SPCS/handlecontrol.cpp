#include "handlecontrol.h"
#include "ui_handlecontrol.h"
#include "sweepshelf.h"
#include "trwavecontrol.h"
#include  "tswmatrixs.h"
#include "TAttenuation.h"
#include  "teleswitch.h"
#include "vnadapter.h"
#include <QDoubleValidator>
#include "m_setpulse.h"
#include "twoshorttoid.h"
#include <QFile>
#include "teleswitch.h"
#include "_global.h"
#include "taskcenter_607.h"

HandleControl::HandleControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HandleControl)
{
    ui->setupUi(this);
    init_elec_switch();
    init_multi_switch();
    init_connect();
    init_data();
    this->setWindowTitle("Control");
    this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    //  this->setStyleSheet(QStringLiteral("background-color: rgb(225,225,255);"));
}

HandleControl::~HandleControl()
{
    delete ui;
}
void HandleControl::init_elec_switch()
{
    m_elec_switch[0]  = ui->pushButton_17;
    m_elec_switch[1]  = ui->pushButton_1;
    m_elec_switch[2]  = ui->pushButton_2;
    m_elec_switch[3]  = ui->pushButton_3;
    m_elec_switch[4]  = ui->pushButton_4;
    m_elec_switch[5]  = ui->pushButton_5;
    m_elec_switch[6]  = ui->pushButton_6;
    m_elec_switch[7]  = ui->pushButton_7;
    m_elec_switch[8]  = ui->pushButton_8;
    m_elec_switch[9]  = ui->pushButton_9;
    m_elec_switch[10] = ui->pushButton_10;
    m_elec_switch[11] = ui->pushButton_11;
    m_elec_switch[12] = ui->pushButton_12;
    m_elec_switch[13] = ui->pushButton_13;
    m_elec_switch[14] = ui->pushButton_14;
    m_elec_switch[15] = ui->pushButton_15;
    m_elec_switch[16] = ui->pushButton_16;


    for(int i =0;i<17;++i)
    {
        m_elec_switch_status[i] = false;
    }
    on_pushButton_closeall_clicked();

}

void HandleControl::init_multi_switch()
{
    m_multi_switch[0]   = ui->radioButton;
    m_multi_switch[1]   = ui->radioButton_2;
    m_multi_switch[2]   = ui->radioButton_3;
    m_multi_switch[3]   = ui->radioButton_4;
    m_multi_switch[4]   = ui->radioButton_5;
    m_multi_switch[5]   = ui->radioButton_6;
    m_multi_switch[6]   = ui->radioButton_7;
    m_multi_switch[7]   = ui->radioButton_8;
    m_multi_switch[8]   = ui->radioButton_9;
    m_multi_switch[9]   = ui->radioButton_10;
    m_multi_switch[10]  = ui->radioButton_11;
    m_multi_switch[11]  = ui->radioButton_12;
    m_multi_switch[12]  = ui->radioButton_13;
    m_multi_switch[13]  = ui->radioButton_14;
    m_multi_switch[14]  = ui->radioButton_15;
    m_multi_switch[15]  = ui->radioButton_16;

}

void HandleControl::init_connect()
{
    for(size_t i =0;i<m_multi_switch.size();++i)
    {
        if(m_multi_switch.count(i)>0)
            connect(m_multi_switch[i],SIGNAL(clicked()),this,SLOT(checkout_multi_switch()));
    }

    connect(ui->radioButton_rowcol,SIGNAL(clicked()),this,SLOT(ID_or_RowCol()));
    connect(ui->radioButton_id,SIGNAL(clicked()),this,SLOT(ID_or_RowCol()));
    connect(ui->radioButton_dis,SIGNAL(clicked()),this,SLOT(Dis_or_Pos()));
    connect(ui->radioButton_pos,SIGNAL(clicked()),this,SLOT(Dis_or_Pos()));
    connect(this,SIGNAL(test(bool)),&m_thread,SLOT(T_test(bool)),\
            Qt::QueuedConnection);
    connect(&m_thread,SIGNAL(testend()),this,SLOT(Testend()),\
            Qt::QueuedConnection);
    connect(this,SIGNAL(close_allDEC()),this,SLOT(on_pushButton_closeall_clicked()),
            Qt::QueuedConnection);
    connect(this,SIGNAL(change_status(int)),this,SLOT(changedecstatus(int)),Qt::QueuedConnection);
}

void HandleControl::init_data()
{
    ui->lineEdit_if->setValidator(new QDoubleValidator(0.0, 100000000000.0,5,this));
    ui->lineEdit_power->setValidator(new QDoubleValidator(-20, 100000000000.0,5,this));
    default_wave();
    default_sweepshelf();
    on_pushButton_default_vna_clicked();

    m_cur_dec_num = 1;
    m_isdec_click = false;
    m_wait_times = 0;
    m_isdiffer = false;
    m_switch_time = 0;

    m_iscontinue = true;
}

void HandleControl::default_wave()
{
    ui->lineEdit_col->setText("1");
    ui->lineEdit_row->setText("1");
    ui->lineEdit_rec_magn->setText("0");
    ui->lineEdit_rec_phase->setText("0");
    ui->lineEdit_send_man->setText("0");
    ui->lineEdit_send_phase->setText("0");
    ui->lineEdit_id->setText("65537");
    QString ls_sec = CVTS::GBKToUnicode::toUnicode("是否成功？");

    ui->label_isconnect->setText(ls_sec);
    ui->label_isdown->setText(ls_sec);
    ui->label_isinit->setText(ls_sec);
    ui->radioButton_recive->setChecked(true);
    ui->radioButton_rowcol->setChecked(true);

    ID_or_RowCol();
}

void HandleControl::default_sweepshelf()
{
    ui->radioButton_pos->setChecked(true);
    ui->lineEdit_pos->setText("12");
    ui->lineEdit_dis->setText("724");
    ui->comboBox_move_speed->setCurrentIndex(5);
    Dis_or_Pos();
}



void HandleControl::checkout_multi_switch()
{
    for(size_t i =0;i<m_multi_switch.size();++i)
    {
        if(m_multi_switch.count(i)>0)
        {
            if(m_multi_switch[i]->isChecked())
            {
                m_multi_switch[i]->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 0);"));
                TSWMatrixs::instance()->turn_on(CVTS::Matrix(i));
                QString dec = QString("%1").arg(i+1);
                ui->lineEdit_DEC->setText(dec);
            }else
                m_multi_switch[i]->setStyleSheet("");
        }
    }
}


void HandleControl::on_pushButton_closeall_clicked()
{
    if(TEleSwitch::instance())
        TEleSwitch::instance()->turn_off_all();
    for(size_t i =0;i<m_elec_switch.size();++i)
    {
        if(m_elec_switch.count(i)>0)
        {
            m_elec_switch_status[i] = false;
            QString ls_str = CVTS::GBKToUnicode::toUnicode("打开") + QString("%1").arg(i);
            if(i ==0)
                ls_str = CVTS::GBKToUnicode::toUnicode("打开") + QString("%1").arg(17);
            m_elec_switch.at(i)->setText(ls_str);
            m_elec_switch.at(i)->setStyleSheet("");
        }
    }
}

void HandleControl::on_radioButton_close_all_clicked()
{
    for(size_t i =0;i<m_multi_switch.size();++i)
    {
        if(m_multi_switch.count(i)>0)
        {
            m_multi_switch[i]->setStyleSheet("");
        }
    }
    TSWMatrixs::instance()->turn_off_all();
}

void HandleControl::on_pushButton_1_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_1,1);
}

void HandleControl::on_pushButton_2_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_2,2);
}

void HandleControl::on_pushButton_3_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_3,3);
}

void HandleControl::on_pushButton_4_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_4,4);
}

void HandleControl::on_pushButton_5_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_5,5);
}


void HandleControl::on_pushButton_6_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_6,6);
}

void HandleControl::on_pushButton_7_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_7,7);
}

void HandleControl::on_pushButton_8_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_8,8);
}

void HandleControl::on_pushButton_9_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_9,9);
}

void HandleControl::on_pushButton_10_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_10,10);
}

void HandleControl::on_pushButton_11_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_11,11);
}

void HandleControl::on_pushButton_12_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_12,12);
}

void HandleControl::on_pushButton_13_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_13,13);
}

void HandleControl::on_pushButton_14_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_14,14);
}

void HandleControl::on_pushButton_15_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_15,15);
}

void HandleControl::on_pushButton_16_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_16,16);
}

void HandleControl::on_pushButton_17_clicked()
{
    ElecSwitch_setCurrentStatus(ui->pushButton_17,0);
}

void HandleControl::ElecSwitch_setCurrentStatus(QPushButton *button, int id)
{
    if(id >=  CD_NUMS || id <0) return ;
    bool  ret = false;
    QString str;

    if(m_elec_switch_status.count(id)>0)
    {
        ret = m_elec_switch_status[id];
        int ls_id = id;
        if(id ==0)
            ls_id = 17;
        if(!ret)
        {
            str =   CVTS::GBKToUnicode::toUnicode("关闭") +QString("%1").arg(ls_id);
            button->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 0);"));
        }
        else{
            str =   CVTS::GBKToUnicode::toUnicode("打开") +QString("%1").arg(ls_id);
            button->setStyleSheet("");
        }
    }
    button->setText(str);
    m_elec_switch_status[id] = !ret;
    if(ret)
        TEleSwitch::instance()->turn_off(CVTS::CVTS_Decetor(id-1));
    else
        TEleSwitch::instance()->turn_on(CVTS::CVTS_Decetor(id-1));

}

void HandleControl::on_checkBox_pulse_2_clicked()
{
    ui->groupBox_all_enable->setEnabled(ui->checkBox_pulse_2->isChecked());
}


void HandleControl::on_checkBox_path0_2_clicked()
{
    ui->groupBox_path0_2->setEnabled(ui->checkBox_path0_2->isChecked());
}

void HandleControl::on_checkBox_path1_2_clicked()
{
    ui->groupBox__path1_2->setEnabled(ui->checkBox_path2_2->isChecked());
}

void HandleControl::on_checkBox_path2_2_clicked()
{
    ui->groupBox_path2_2->setEnabled(ui->checkBox_path2_2->isChecked());
}

void HandleControl::on_checkBox_path3_2_clicked()
{
    ui->groupBox_path3_2->setEnabled(ui->checkBox_path3_2->isChecked());
}

void HandleControl::on_checkBox_path4_2_clicked()
{
    ui->groupBox_path4_2->setEnabled(ui->checkBox_path4_2->isChecked());
}

void HandleControl::on_pushButton_default_vna_clicked()
{
    ui->lineEdit_startfreq->setText("8");
    ui->lineEdit_power->setText("-20");
    ui->lineEdit_if->setText("1");
    ui->lineEdit_stopfreq->setText("12");
    ui->lineEdit_freq_iter->setText("201");
    ui->comboBox__attan->setCurrentIndex(0);
    ui->comboBox_if->setCurrentIndex(1);
    ui->comboBox_start->setCurrentIndex(3);
    ui->comboBox_stop->setCurrentIndex(3);

    ui->checkBox_S11->setChecked(true);
    ui->checkBox_S21->setChecked(true);
    ui->checkBox_S22->setChecked(true);
    ui->checkBox_S12->setChecked(true);

    ui->lineEdit_wait_time->setText("200");
    ui->lineEdit_nums->setText("20");
    ui->groupBox_collect_Data->setChecked(false);
    ui->checkBoxchecke_dec->setChecked(false);
    ui->checkBox_isdiffer->setChecked(true);
    ui->lineEdit_DEC->setText("16");
    ui->comboBox_type->setCurrentIndex(0);
    ui->radioButton_caltest->setChecked(true);
    on_radioButton_caltest_clicked();

}

void HandleControl::on_pushButton_vna_reset_clicked()
{
    VNAdapter::s_vna = VNA_AGILENT;
    if(ui->comboBox_type->currentIndex())
        VNAdapter::s_vna = VNA_RS;
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



void HandleControl::on_pushButton_open_clicked()
{
    SweepShelf::instance()->Open_DEV("COM4");
}

void HandleControl::on_pushButton_close_clicked()
{
    SweepShelf::instance()->Close_DEV();
}

void HandleControl::on_pushButton_move_0_clicked()
{
    SweepShelf::instance()->MOVE_TO_Origin();
}

void HandleControl::on_pushButton_query_clicked()
{
    if(SweepShelf::instance()->IsMoveDone())
        ui->label_shelfstatus->setText(CVTS::GBKToUnicode::toUnicode("Yes"));
    else
        ui->label_shelfstatus->setText(CVTS::GBKToUnicode::toUnicode("NO"));
}

void HandleControl::on_pushButton_move_clicked()
{
    ui->label_shelfstatus->setText(CVTS::GBKToUnicode::toUnicode("NO"));
    MOVESPEESD  speed = SPEED_1500_;
    if(ui->comboBox_move_speed->currentIndex() == 0)
        speed = SPEED_0_100;
    if(ui->comboBox_move_speed->currentIndex() == 1)
        speed = SPEED_100_300;
    if(ui->comboBox_move_speed->currentIndex() == 2)
        speed = SPEED_300_500;
    if(ui->comboBox_move_speed->currentIndex() == 3)
        speed = SPEED_500_1000;
    if(ui->comboBox_move_speed->currentIndex() == 4)
        speed = SPEED_1000_1500;
    if(ui->comboBox_move_speed->currentIndex() == 5)
        speed = SPEED_1500_;
    double distance = ui->lineEdit_dis->text().toDouble();
    if(ui->radioButton_dis->isChecked())
    {
        if(distance >724 || distance <-724)
        {
            QMessageBox mes;
            QString title = CVTS::GBKToUnicode::toUnicode("警告");
            QString text = CVTS::GBKToUnicode::toUnicode("超过移动范围！");
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
        if(pos>724) pos =724;
        if(pos<-724) pos = -724;
        SweepShelf::instance()->MOVE_TO(pos);
    }
}

void HandleControl::on_pushButton_ATTAN_apply_clicked()
{
    TAttenuation::instance()->attenuation(CVTS::NI_ANTENNA(ui->comboBox__attan->currentIndex()));
}


void HandleControl::on_pushButton_connect_clicked()
{
    if(TRWaveControl::instance()->udpConnectTest())
        ui->label_isconnect->setText(CVTS::GBKToUnicode::toUnicode("连接成功"));
    else
        ui->label_isconnect->setText(CVTS::GBKToUnicode::toUnicode("连接失败"));
}

void HandleControl::on_pushButton_init_clicked()
{
    if(TRWaveControl::instance()->AntenaInit(ui->radioButton_send->isChecked()))
        ui->label_isinit->setText(CVTS::GBKToUnicode::toUnicode("初始化成功"));
    else
        ui->label_isinit->setText(CVTS::GBKToUnicode::toUnicode("初始化失败"));
}

void HandleControl::on_pushButton_down_clicked()
{
    if(TRWaveControl::instance()->DownPower())
        ui->label_isdown->setText(CVTS::GBKToUnicode::toUnicode("下电成功"));
    else
        ui->label_isdown->setText(CVTS::GBKToUnicode::toUnicode("下电失败"));
}

void HandleControl::on_pushButtonwave_default_clicked()
{
    default_wave();
}


void HandleControl::on_pushButton_wave_control_clicked()
{
    if(ui->radioButton_send->isChecked())
    {
        if(ui->lineEdit_col->text().toInt( ) == 0 || ui->lineEdit_row->text().toInt() == 0)
        {
            QString ls_title = CVTS::GBKToUnicode::toUnicode("警告");
            QString ls_com   = CVTS::GBKToUnicode::toUnicode("发射状态,禁止打开多个阵元！");
            QMessageBox mes;
            mes.setText(ls_com);
            mes.setWindowTitle(ls_title);
            mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
            mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
            mes.exec();
            return ;
        }
    }

    TRontrol ls_tr;
    if(ui->lineEdit_row->text().toInt() >40 ||ui->lineEdit_row->text().toInt() <-40 ||\
            ui->lineEdit_col->text().toInt()> 12 || ui->lineEdit_col->text().toInt()< -12 )
    {
        QString ls_title = CVTS::GBKToUnicode::toUnicode("提示");
        QString ls_com   = CVTS::GBKToUnicode::toUnicode("行列值超出范围");
        QMessageBox mes;
        mes.setText(ls_com);
        mes.setWindowTitle(ls_title);
        mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
        mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
        mes.exec();
    }
    QString ls_str;
    if( ui->radioButton_send->isChecked())
        ls_str  = CVTS::GBKToUnicode::toUnicode("发射状态,");
    else
        ls_str = CVTS::GBKToUnicode::toUnicode("接受状态,");

    TRWaveControl::instance()->AntenaInit(ui->radioButton_send->isChecked());
    ::Sleep(5);

    short ls_row = ui->lineEdit_row->text().toInt();
    short ls_col = ui->lineEdit_col->text().toInt();

    if(!ui->radioButton_rowcol->isChecked())
        TwoShortToId::instance()->IdToAddr(ui->lineEdit_id->text().toInt(),ls_row,ls_col);
    if(TRWaveControl::instance()->setMagnPhase(ls_tr,ls_row,ls_col,\
                                               ui->radioButton_send->isChecked(),abs(ui->lineEdit_rec_magn->text().toDouble()),\
                                               ui->lineEdit_rec_phase->text().toDouble(),abs(ui->lineEdit_send_man->text().toDouble()),\
                                               ui->lineEdit_send_phase->text().toDouble()))
    {
        int  row = ls_tr.t_row;
        int  col  = ls_tr.t_col;
        char buf[1024] = {0};
        sprintf(buf,"%d行,%d列,",row,col);
        ls_str += CVTS::GBKToUnicode::toUnicode(buf);
        ls_str += CVTS::GBKToUnicode::toUnicode("成功");
    }
    else
    {
        int  row = ls_tr.t_row;
        int  col  = ls_tr.t_col;
        char buf[1024] = {0};
        sprintf(buf,"%d行,%d列,",row,col);
        ls_str += CVTS::GBKToUnicode::toUnicode("失败");
    }
    ui->label__iswave_control->setText(ls_str);
}



void HandleControl::ID_or_RowCol()
{
    ui->lineEdit_col->setEnabled(!ui->radioButton_id->isChecked());
    ui->lineEdit_row->setEnabled(!ui->radioButton_id->isChecked());
    ui->lineEdit_id->setEnabled(ui->radioButton_id->isChecked());
}

void HandleControl::Dis_or_Pos()
{
    ui->lineEdit_dis->setEnabled(!ui->radioButton_pos->isChecked());
    ui->lineEdit_pos->setEnabled(ui->radioButton_pos->isChecked());
}



void HandleControl::on_pushButton_paulse_clicked()
{
    M_SetPulse::instance()->showNormal();
}



void HandleControl::on_pushButtonapply_clicked()
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
        VNAdapter::s_vna = VNA_AGILENT;
        if(ui->comboBox_type->currentIndex())
            VNAdapter::s_vna = VNA_RS;

        if(VNAdapter::instance()->connect())
        {
            VNAdapter::instance()->delAll();
            if(ui->checkBox_S11->isChecked())
                VNAdapter::instance()->set_trace_S11();
            if(ui->checkBox_S12->isChecked())
                VNAdapter::instance()->set_trace_S12();
            if(ui->checkBox_S21->isChecked())
                VNAdapter::instance()->set_trace_S21();
            if(ui->checkBox_S22->isChecked())
                VNAdapter::instance()->set_trace_S22();

            VNAdapter::instance()->set_freq(start_freq,stop_freq,ui->lineEdit_freq_iter->text().toInt());

            M_SetPulse::instance()->dosetting();
            VNAdapter::instance()->continue_triger();
            VNAdapter::instance()->set_IF_bandwidth(IF);
            VNAdapter::instance()->set_power(power);
            VNAdapter::instance()->setAveTimes(1);

            VNAdapter::instance()->Internal_trigger();
            VNAdapter::instance()->continue_triger();
        }else
            vna_connect_failed();;
    }
}



void HandleControl::on_pushButton_seclect_clicked()
{
    QString  p_path = QFileDialog::getExistingDirectory(this,tr("Collect Data"),\
                                                        "/Users/607/Desktop");

    if(p_path.isEmpty()) return;
    ui->lineEdit_savepath->setText(p_path);
}

void HandleControl::calc_freq()
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

void HandleControl::vna_connect_failed()
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


void HandleControl::cal_test()
{
    QFile  m_collect_file(m_collect_path);
    if(m_collect_file.exists()) m_collect_file.remove();

    if(!m_collect_file.open(QFile::ReadWrite|QFile::Text)){
        qDebug()<< m_collect_path << "open failed!";
        QMessageBox::information(NULL,tr("Message"),tr("file is not exist"));
        return;
    }

    QFile  m_cal_file(m_cal_path);
    if(m_cal_file.exists()) m_cal_file.remove();
    if(!m_cal_file.open(QFile::ReadWrite|QFile::Text)){
        qDebug()<< m_cal_path << "open failed!";
        QMessageBox::information(NULL,tr("Message"),tr("file is not exist"));
        return ;
    }

    Task_CAL_S21         ls_cur_s21;
    Task_CAL_S21         ls_lib_Cal_s21;
    std::vector<QString> m_freq_key;

    if(m_isdiffer)
    {
        QString mach = QString("/Calibration/CUR/match_port");
        m_parse.load_cal_data(QApplication::applicationDirPath(),mach);
        ls_lib_Cal_s21  = m_parse.get_cal_s21();
        m_freq_key      = m_parse.get_ferq_key();
    }

    QTextStream out(&m_collect_file);
    QTextStream out_cal(&m_cal_file);

    out <<"frequecy,";
    bool iss11 = ui->checkBox_S11->isChecked();
    bool iss21 = ui->checkBox_S21->isChecked();
    bool iss12 = ui->checkBox_S12->isChecked();
    bool iss22 = ui->checkBox_S22->isChecked();
    if(iss11) out<<"S11,";
    if(iss21) out<<"S21,";
    if(iss12) out<<"S12,";
    if(iss22) out<<"S22";
    out<<endl;
    QString S11,S12,S21,S22;
    QStringList ls_list_S11,ls_list_S12,ls_list_S21,ls_list_S22;
    double freqsize = m_freq.size();
    bool ret = true;


    if(iss11)
    {
        S11  =   VNAdapter::instance()->collect_S11();
        ls_list_S11 = S11.split(QRegExp(","));
        ret &=(ls_list_S11.size() == 2*freqsize);
    }

    if(iss22)
    {
        S22  =   VNAdapter::instance()->collect_S22();
        ls_list_S22 = S22.split(QRegExp(","));
        ret &=(ls_list_S22.size() == 2*freqsize);
    }


    if(iss21)
    {
        S21  =   VNAdapter::instance()->collect_S21();
        ls_list_S21 = S21.split(QRegExp(","));
        ret &=(ls_list_S21.size() == 2*freqsize);
    }

    if(iss12)
    {
        S12  =   VNAdapter::instance()->collect_S12();
        ls_list_S12 = S12.split(QRegExp(","));
        ret &=(ls_list_S12.size() == 2*freqsize);
    }

    if(ret)
    {
        for(int k=0;k<freqsize;++k)
        {
            out<<m_freq.at(k)<<",";
            if(iss11)
            {
                double real = ls_list_S11.at(2*k).toDouble();
                double imag = ls_list_S11.at(2*k+1).toDouble();
                double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                double phase = VNAdapter::instance()->genPhase(real,imag);
                out<<  db << "," << phase<<",";
            }
            if(iss21)
            {
                double real = ls_list_S21.at(2*k).toDouble();
                double imag = ls_list_S21.at(2*k+1).toDouble();
                double magn = VNAdapter::instance()->genLinMag(real,imag);
                double db = SPCS_dB::dB (magn);
                double phase = VNAdapter::instance()->genPhase(real,imag);
                out<< db << "," << phase<<",";
                ls_cur_s21[ui->lineEdit_DEC->text().toInt()][m_freq.at(k)] = \
                        std::pair<double,double>(db,phase);
            }
            if(iss12)
            {
                double real = ls_list_S12.at(2*k).toDouble();
                double imag = ls_list_S12.at(2*k+1).toDouble();
                double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                double phase = VNAdapter::instance()->genPhase(real,imag);
                out<<  db << "," << phase<<",";
            }
            if(iss22)
            {
                double real = ls_list_S22.at(2*k).toDouble();
                double imag = ls_list_S22.at(2*k+1).toDouble();
                double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                double phase = VNAdapter::instance()->genPhase(real,imag);
                out<<  db << "," << phase<<",";
            }
            out<<endl;
        }
    }

    if(!m_iscontinue) return;

    if(m_isdiffer)
    {
        out_cal<<"ElecSwitch :"<<ui->lineEdit_DEC->text().toInt()<<endl;
        out_cal<<"frequecy,dB,Phase"<<endl;
        for(size_t k = 0;k< m_freq.size();++k)
        {
            QString cur_freq = m_freq.at(k);
            if(ls_cur_s21.count(m_cur_dec_num)>0&&ls_lib_Cal_s21.count(m_cur_dec_num)>0)
            {
                if(ls_cur_s21[m_cur_dec_num].count(cur_freq) >0)
                {
                    QString lib_freq = cur_freq;
                    if(ls_lib_Cal_s21[m_cur_dec_num].count(cur_freq) == 0)
                        TaskCenter_607::instance()->check_differ(lib_freq,m_freq_key);
                    double db = ls_cur_s21[m_cur_dec_num][cur_freq].first - SPCS_dB::dB(ls_lib_Cal_s21[m_cur_dec_num][lib_freq].first);
                    double phase = ls_cur_s21[m_cur_dec_num][cur_freq].second - ls_lib_Cal_s21[m_cur_dec_num][lib_freq].second;
                    out_cal<<cur_freq<<","<<db<<","<<phase<<endl;
                }
            }
        }
    }


    if(m_cal_file.isOpen())
        m_cal_file.close();

    if(m_collect_file.isOpen())
        m_collect_file.close();
  //  emit close_allDEC();
}

void HandleControl::stable_test()
{
    QFile  m_0_file(m_0_path);
    if(m_0_file.exists()) m_0_file.remove();
    if(!m_0_file.open(QFile::ReadWrite|QFile::Text)){
        qDebug()<< m_0_path << "open failed!";
        QMessageBox::information(NULL,tr("Message"),tr("file open failed !"));
        return;
    }
    QFile   m_23_file(m_23_path);
    if(m_23_file.exists()) m_23_file.remove();

    if(m_isdec_click)
    {
        if(!m_23_file.open(QFile::ReadWrite|QFile::Text)){
            qDebug()<< m_23_path << "open failed!";
            QMessageBox::information(NULL,tr("Message"),tr("file open failed !"));
        }
    }

    QTextStream out_0(&m_0_file);
    QTextStream out_23(&m_23_file);
    VNAdapter::instance()->connect();
    out_0 <<"frequecy,";
    bool iss11 = ui->checkBox_S11->isChecked();
    bool iss21 = ui->checkBox_S21->isChecked();
    bool iss12 = ui->checkBox_S12->isChecked();
    bool iss22 = ui->checkBox_S22->isChecked();
    if(iss11) out_0<<"S11,";
    if(iss21) out_0<<"S21,";
    if(iss12) out_0<<"S12,";
    if(iss22) out_0<<"S22";
    out_0<<endl;

    if(m_isdec_click)
    {
        out_23 <<"frequecy,";
        if(iss11) out_23<<"S11,";
        if(iss21) out_23<<"S21,";
        if(iss12) out_23<<"S12,";
        if(iss22) out_23<<"S22";
        out_23<<endl;
    }


    QString S11,S12,S21,S22;
    QStringList ls_list_S11,ls_list_S12,ls_list_S21,ls_list_S22;
    double freqsize = m_freq.size();
    bool ret = true;

    for(int m =0 ;m<m_collect_nums;++m)
    {
        ////////////////////////////////////////
        /////////////0V
        if(!m_iscontinue) return;
        if(m_isdec_click)
        {
            emit close_allDEC();
            ::Sleep(m_wait_times);
        }
        if(iss11)
        {
            S11  =   VNAdapter::instance()->collect_S11();
            ls_list_S11 = S11.split(QRegExp(","));
            ret &=(ls_list_S11.size() == 2*freqsize);
        }
        if(iss22)
        {
            S22  =   VNAdapter::instance()->collect_S22();
            ls_list_S22 = S22.split(QRegExp(","));
            ret &=(ls_list_S22.size() == 2*freqsize);
        }

        if(iss21)
        {
            S21  =   VNAdapter::instance()->collect_S21();
            ls_list_S21 = S21.split(QRegExp(","));
            ret &=(ls_list_S21.size() == 2*freqsize);
        }
        if(iss12)
        {
            S12  =   VNAdapter::instance()->collect_S12();
            ls_list_S12 = S12.split(QRegExp(","));
            ret &=(ls_list_S12.size() == 2*freqsize);
        }

        if(ret)
        {
            for(int k=0;k<freqsize;++k)
            {
                out_0<<m_freq.at(k)<<",";
                if(iss11)
                {
                    double real = ls_list_S11.at(2*k).toDouble();
                    double imag = ls_list_S11.at(2*k+1).toDouble();
                    double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                    double phase = VNAdapter::instance()->genPhase(real,imag);
                    out_0<<  db << "," << phase<<",";
                }
                if(iss21)
                {
                    double real = ls_list_S21.at(2*k).toDouble();
                    double imag = ls_list_S21.at(2*k+1).toDouble();
                    double magn = VNAdapter::instance()->genLinMag(real,imag);
                    double db = SPCS_dB::dB (magn);
                    double phase = VNAdapter::instance()->genPhase(real,imag);
                    out_0<< db << "," << phase<<",";
                }
                if(iss12)
                {
                    double real = ls_list_S12.at(2*k).toDouble();
                    double imag = ls_list_S12.at(2*k+1).toDouble();
                    double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                    double phase = VNAdapter::instance()->genPhase(real,imag);
                    out_0<<  db << "," << phase<<",";
                }
                if(iss22)
                {
                    double real = ls_list_S22.at(2*k).toDouble();
                    double imag = ls_list_S22.at(2*k+1).toDouble();
                    double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                    double phase = VNAdapter::instance()->genPhase(real,imag);
                    out_0<<  db << "," << phase<<",";
                }
                out_0<<endl;
            }
        }

        //////////////////////////////////////////
        /////////23V
        if(!m_iscontinue) return;
        if(m_isdec_click)
        {
            ::Sleep(m_switch_time);

            TEleSwitch::instance()->turn_on(CVTS_Decetor(m_cur_dec_num-1));
            m_elec_switch_status[m_cur_dec_num] = true;

            emit change_status(m_cur_dec_num);

            ::Sleep(m_wait_times);

            if(iss11)
            {
                S11  =   VNAdapter::instance()->collect_S11();
                ls_list_S11 = S11.split(QRegExp(","));
                ret &=(ls_list_S11.size() == 2*freqsize);
            }
            if(iss22)
            {
                S22  =   VNAdapter::instance()->collect_S22();
                ls_list_S22 = S22.split(QRegExp(","));
                ret &=(ls_list_S22.size() == 2*freqsize);
            }

            if(iss21)
            {
                S21  =   VNAdapter::instance()->collect_S21();
                ls_list_S21 = S21.split(QRegExp(","));
                ret &=(ls_list_S21.size() == 2*freqsize);
            }

            if(iss12)
            {
                S12  =   VNAdapter::instance()->collect_S12();
                ls_list_S12 = S12.split(QRegExp(","));
                ret &=(ls_list_S12.size() == 2*freqsize);
            }

            if(ret)
            {
                for(int k=0;k<freqsize;++k)
                {
                    out_23<<m_freq.at(k)<<",";
                    if(iss11)
                    {
                        double real = ls_list_S11.at(2*k).toDouble();
                        double imag = ls_list_S11.at(2*k+1).toDouble();
                        double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                        double phase = VNAdapter::instance()->genPhase(real,imag);
                        out_23<<  db << "," << phase<<",";
                    }
                    if(iss21)
                    {
                        double real = ls_list_S21.at(2*k).toDouble();
                        double imag = ls_list_S21.at(2*k+1).toDouble();
                        double magn = VNAdapter::instance()->genLinMag(real,imag);
                        double db = SPCS_dB::dB (magn);
                        double phase = VNAdapter::instance()->genPhase(real,imag);
                        out_23<< db << "," << phase<<",";
                    }
                    if(iss12)
                    {
                        double real = ls_list_S12.at(2*k).toDouble();
                        double imag = ls_list_S12.at(2*k+1).toDouble();
                        double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                        double phase = VNAdapter::instance()->genPhase(real,imag);
                        out_23<<  db << "," << phase<<",";
                    }
                    if(iss22)
                    {
                        double real = ls_list_S22.at(2*k).toDouble();
                        double imag = ls_list_S22.at(2*k+1).toDouble();
                        double db = SPCS_dB::dB (VNAdapter::instance()->genLinMag(real,imag));
                        double phase = VNAdapter::instance()->genPhase(real,imag);
                        out_23<<  db << "," << phase<<",";
                    }
                    out_23<<endl;
                }
            }

        }

    }

    if(m_0_file.isOpen())
        m_0_file.close();

    if(m_23_file.isOpen())
        m_23_file.close();
   // emit close_allDEC();
}

void HandleControl::get_comm_test_parame()
{
    if(ui->lineEdit_savepath->text().isEmpty() ||\
            ui->lineEdit_DEC->text().isEmpty())
    {
        QMessageBox::information(NULL,tr("Message"),tr("Input error !"));
        return ;
    }

    calc_freq();
    m_wait_times   = ui->lineEdit_wait_time->text().toDouble();
    m_isdiffer     = ui->checkBox_isdiffer->isChecked() ;
    m_cur_dec_num  = ui->lineEdit_DEC->text().toInt();
    if(m_cur_dec_num >16 || m_cur_dec_num < 1)
        return ;
    m_isdec_click  = ui->checkBoxchecke_dec->isChecked();
    m_collect_nums = ui->lineEdit_nums->text().toInt();

    m_multi_switch[m_cur_dec_num-1]->setChecked(true);
    checkout_multi_switch();

    VNAdapter::s_vna = VNA_AGILENT;
    if(ui->comboBox_type->currentIndex())
        VNAdapter::s_vna = VNA_RS;
    if(!VNAdapter::instance()->connect())
    {
        vna_connect_failed();
        return ;
    }

    VNAdapter::instance()->continue_triger();


    m_collect_path = ui->lineEdit_savepath->text() \
            +QString("/")+ QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss")+\
            QString("_collect_port%1.dat").arg(m_cur_dec_num);


    m_cal_path  = ui->lineEdit_savepath->text() \
            +QString("/")+ QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss")\
            +QString("_cal_port%1.clibs").arg(m_cur_dec_num);

    ::Sleep(50);
    emit test(true);
}

void HandleControl::get_stable_test_parame()
{
    if(ui->lineEdit_savepath->text().isEmpty() ||\
            ui->lineEdit_DEC->text().isEmpty()||\
            ui->lineEdit_nums->text().isEmpty())
    {
        QMessageBox::information(NULL,tr("Message"),tr("Input error !"));
        return ;
    }
    calc_freq();
    m_wait_times   = ui->lineEdit_wait_time->text().toDouble();
    m_isdiffer     = ui->checkBox_isdiffer->isChecked() ;
    m_cur_dec_num  = ui->lineEdit_DEC->text().toInt();
    if(m_cur_dec_num>16 || m_cur_dec_num < 1) return ;
    m_isdec_click  = ui->checkBoxchecke_dec->isChecked();
    m_collect_nums = ui->lineEdit_nums->text().toInt();
    m_switch_time  = ui->lineEdit_switch_times->text().toDouble();

    m_iscontinue = true;
    on_pushButton_closeall_clicked();
    m_multi_switch[m_cur_dec_num-1]->setChecked(true);
    checkout_multi_switch();

    VNAdapter::s_vna = VNA_AGILENT;
    if(ui->comboBox_type->currentIndex())
        VNAdapter::s_vna = VNA_RS;

    if(!VNAdapter::instance()->connect())
    {
        vna_connect_failed();
        return ;
    }
    VNAdapter::instance()->continue_triger();

    QString cur_time = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh");
    m_0_path = ui->lineEdit_savepath->text() + QString("/")+ \
            cur_time+QString("_")+ \
            QString("_0V_port%1.stable").arg(m_cur_dec_num);

    m_23_path  = ui->lineEdit_savepath->text() +QString("/")+ \
            cur_time+ QString("_")+ \
            QString("_23V_port%1.stable").arg(m_cur_dec_num);
    ::Sleep(50);
    emit test(false);

}



void HandleControl::on_pushButton_collect_clicked()
{
    if(ui->radioButton_stable->isChecked())
    {
        get_stable_test_parame();
    }else
    {
        get_comm_test_parame();
    }
}



void HandleControl::changedecstatus(int dec)
{
    m_elec_switch[dec]->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 0);"));
}



void HandleControl::on_pushButton_update_trace_clicked()
{
    VNAdapter::s_vna = VNA_AGILENT;
    if(ui->comboBox_type->currentIndex())
        VNAdapter::s_vna = VNA_RS;

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


void HandleControl::on_pushButton_stop_test_clicked()
{
    m_iscontinue = false;
}

void HandleControl::Testend()
{
    ::Sleep(50);
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


void HandleControl::on_pushButton_reconnect_clicked()
{

}

void HandleControl::on_radioButton_stable_clicked()
{
    ui->lineEdit_nums->setEnabled(true);
    ui->lineEdit_wait_time->setEnabled(true);
    ui->checkBoxchecke_dec->setEnabled(true);
    ui->checkBox_isdiffer->setChecked(false);
    ui->checkBox_isdiffer->setEnabled(false);
    ui->lineEdit_switch_times->setEnabled(true);
}



void HandleControl::on_radioButton_caltest_clicked()
{
    ui->lineEdit_nums->setEnabled(false);
    ui->lineEdit_wait_time->setEnabled(false);
    ui->checkBoxchecke_dec->setEnabled(false);
    ui->checkBox_isdiffer->setChecked(false);
    ui->checkBox_isdiffer->setEnabled(true);
    ui->lineEdit_switch_times->setEnabled(false);
}

void HandleControl::on_pushButton_manual_clicked()
{
    if(VNAdapter::instance()->connect())
        VNAdapter::instance()->continue_triger();
}

void HandleControl::on_pushButton_interal_clicked()
{
    if(VNAdapter::instance()->connect())
        VNAdapter::instance()->Internal_trigger();
}
