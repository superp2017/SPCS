#include "portchange.h"
#include "ui_portchange.h"
#include "vnadapter.h"
#include "teleswitch.h"
#include "tswmatrixs.h"
#include "portchangethread.h"

PortChange::PortChange(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PortChange)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    for(int i =0;i<16;++i)
    {
        ui->comboBox_elec->addItem(QString("%1").arg(i+1));
    }

    ui->comboBox_start->addItem(QString("Hz"));
    ui->comboBox_start->addItem(QString("kHz"));
    ui->comboBox_start->addItem(QString("MHz"));
    ui->comboBox_start->addItem(QString("GHz"));

    ui->comboBox_end->addItem(QString("Hz"));;
    ui->comboBox_end->addItem(QString("kHz"));;
    ui->comboBox_end->addItem(QString("MHz"));;
    ui->comboBox_end->addItem(QString("GHz"));;

    ui->comboBox_if->addItem(QString("Hz"));
    ui->comboBox_if->addItem(QString("kHz"));
    ui->comboBox_if->addItem(QString("MHz"));
    ui->comboBox_if->addItem(QString("GHz"));
    init_ui();
}

PortChange::~PortChange()
{
    delete ui;
}

void PortChange::init_ui()
{
    ui->lineEdit_phase->setText("0");
    ui->lineEdit_A_phase->setText("0");
    ui->lineEdit_B_phase->setText("1");
    ui->lineEdit_end_freq->setText("11");
    ui->lineEdit_start_freq->setText("9");
    ui->lineEdit_iter->setText("3");
    ui->lineEdit_power->setText("18");
    ui->lineEdit_if->setText("10");
    ui->comboBox_start->setCurrentIndex(3);
    ui->comboBox_end->setCurrentIndex(3);
    ui->comboBox_if->setCurrentIndex(0);
    ui->groupBox_2->setChecked(true);
    ui->comboBox_type->setCurrentIndex(0);

    m_cur_row       = 0;

    int colcount = 500;
    ui->tableWidget_test->setRowCount(colcount);
    ui->tableWidget_test->setColumnCount(colcount);

    ui->tableWidget_compare->setColumnCount(colcount);
    ui->tableWidget_compare->setRowCount(3);
    for(int i=0;i<colcount;++i)
    {
        ui->tableWidget_compare->setColumnWidth(i,90);
        ui->tableWidget_test->setColumnWidth(i,90);
    }

    set_compare_widget();
    ui->tableWidget_test->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_compare->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(this,SIGNAL(test()),PortChangeThread::instance(),SLOT(T_test()),\
            Qt::QueuedConnection);
    connect(PortChangeThread::instance(),SIGNAL(testend()),\
            this,SLOT(update_tableWidget()),\
            Qt::QueuedConnection);
}




void PortChange::init_tablewidget(QTableWidget * tab,int prow,int value)
{
    QString delt =  CVTS::GBKToUnicode::toUnicode("状态");
    QString pmatch = CVTS::GBKToUnicode::toUnicode("0V");
    QString pshort =  CVTS::GBKToUnicode::toUnicode("23V");
    QString calc_Data = CVTS::GBKToUnicode::toUnicode("计算值");
    QString test_Data = CVTS::GBKToUnicode::toUnicode("测得值");
    QString S11     = CVTS::GBKToUnicode::toUnicode("S11");
    QString S21     = CVTS::GBKToUnicode::toUnicode("S21_1");
    QString S21_1     = CVTS::GBKToUnicode::toUnicode("S21`_1");
    int row = prow;
    tab->setItem(row,0,new QTableWidgetItem(delt));
    tab->setItem(row,1,new QTableWidgetItem(QString("%1").arg(value)));
    row++;
    tab->setItem(row,0,new QTableWidgetItem(pmatch));
    tab->setItem(row,1,new QTableWidgetItem(S11));
    row++;
    tab->setItem(row,0,new QTableWidgetItem(pshort));
    tab->setItem(row,1,new QTableWidgetItem(S11));
    row++;
    tab->setItem(row,0,new QTableWidgetItem(calc_Data));
    tab->setItem(row,1,new QTableWidgetItem(S21));
    row++;
    tab->setItem(row,0,new QTableWidgetItem(test_Data));
    tab->setItem(row,1,new QTableWidgetItem(S21_1));
}

void PortChange::set_compare_widget()
{
    QString calc_dif  =  CVTS::GBKToUnicode::toUnicode("计算差值");
    QString test_dif  = CVTS::GBKToUnicode::toUnicode("测得差值");
    QString dif_p     =  CVTS::GBKToUnicode::toUnicode("差值比较");
    QString s21_1     =  CVTS::GBKToUnicode::toUnicode("ΔS21`");
    QString s21       = CVTS::GBKToUnicode::toUnicode("ΔS21");
    QString s21_1_s21 =  CVTS::GBKToUnicode::toUnicode("ΔS21`-ΔS21");


    if(ui->tableWidget_compare->item(0,0))
        ui->tableWidget_compare->item(0,0)->setText(calc_dif);
    else
        ui->tableWidget_compare->setItem(0,0,new QTableWidgetItem(calc_dif));

    if( ui->tableWidget_compare->item(0,1))
        ui->tableWidget_compare->item(0,1)->setText(s21_1);
    else
        ui->tableWidget_compare->setItem(0,1,new QTableWidgetItem(s21_1));

    if( ui->tableWidget_compare->item(1,0))
        ui->tableWidget_compare->item(1,0)->setText(test_dif);
    else
        ui->tableWidget_compare->setItem(1,0,new QTableWidgetItem(test_dif));

    if( ui->tableWidget_compare->item(1,1))
        ui->tableWidget_compare->item(1,1)->setText(s21);
    else
        ui->tableWidget_compare->setItem(1,1,new QTableWidgetItem(s21));

    if( ui->tableWidget_compare->item(2,0))
        ui->tableWidget_compare->item(2,0)->setText(dif_p);
    else
        ui->tableWidget_compare->setItem(2,0,new QTableWidgetItem(dif_p));

    if( ui->tableWidget_compare->item(2,1))
        ui->tableWidget_compare->item(2,1)->setText(s21_1_s21);
    else
        ui->tableWidget_compare->setItem(2,1,new QTableWidgetItem(s21_1_s21));
}


/*!
 * \brief PortChange::update_tableWidget
 * 根据测试和计算的数据更新界面
 */
void PortChange::update_tableWidget()
{
    if(m_test_data.count(m_changePhase)>0)
    {
        CHAGE ch = m_test_data[m_changePhase];
        int col = 2;
        init_tablewidget(ui->tableWidget_test,ch.t_cur_row,m_changePhase);
        QStringList ls_list;
        QString type =  CVTS::GBKToUnicode::toUnicode("类型");
        QString Sdatatype = CVTS::GBKToUnicode::toUnicode("测量量或\n设定值");

        ls_list.append(type);
        ls_list.append(Sdatatype);


        for(size_t i =0;i<ch.t_freq.size();++i)
        {
            int row = ch.t_cur_row;
            QString cur_freq = ch.t_freq.at(i);
            if(ch.t_s11_match.count(cur_freq)>0&&ch.t_s11_short.count(cur_freq)>0)
            {
                QString freq_str;
                CVTS::DoubleFre_TO_QStringFreq::Double_TO_QString(cur_freq.toDouble(),freq_str);

                QString ms = freq_str +  CVTS::GBKToUnicode::toUnicode("\n幅度dB");
                QString ps = freq_str +  CVTS::GBKToUnicode::toUnicode("\n相位°");
                ls_list.append(ms);
                ls_list.append(ps);

                if(ui->tableWidget_test->item(row,col+1))
                    ui->tableWidget_test->item(row,col+1)->setText(QString::number(m_changePhase*cur_freq.toDouble()/1000000000,'f',2));
                else
                    ui->tableWidget_test->setItem(row,col+1,new QTableWidgetItem(QString::number(m_changePhase*cur_freq.toDouble()/1000000000,'f',2)));
                ++row;

                std::pair<double,double> la_pair_match = ch.t_s11_match[cur_freq];
                std::pair<double,double> la_pair_short = ch.t_s11_short[cur_freq];

                if(ui->tableWidget_test->item(row,col))
                    ui->tableWidget_test->item(row,col)->setText(QString::number(la_pair_match.first,'f',2));
                else
                    ui->tableWidget_test->setItem(row,col,new QTableWidgetItem(QString::number(la_pair_match.first,'f',2)));

                if(ui->tableWidget_test->item(row,col+1))
                    ui->tableWidget_test->item(row,col+1)->setText(QString::number(la_pair_match.second,'f',2));
                else
                    ui->tableWidget_test->setItem(row,col+1,new QTableWidgetItem(QString::number(la_pair_match.second,'f',2)));
                ++row;
                if(ui->tableWidget_test->item(row,col))
                    ui->tableWidget_test->item(row,col)->setText(QString::number(la_pair_short.first,'f',2));
                else
                    ui->tableWidget_test->setItem(row,col,new QTableWidgetItem(QString::number(la_pair_short.first,'f',2)));

                if(ui->tableWidget_test->item(row,col+1))
                    ui->tableWidget_test->item(row,col+1)->setText(QString::number(la_pair_short.second,'f',2));
                else
                    ui->tableWidget_test->setItem(row,col+1,new QTableWidgetItem(QString::number(la_pair_short.second,'f',2)));
                ++row;
            }

            if(ch.t_s21_calc.count(cur_freq)>0)
            {
                std::pair<double,double> la_pair =  ch.t_s21_calc[cur_freq];


                if(ui->tableWidget_test->item(row,col))
                    ui->tableWidget_test->item(row,col)->setText(QString::number(la_pair.first,'f',2));
                else
                    ui->tableWidget_test->setItem(row,col,new QTableWidgetItem(QString::number(la_pair.first,'f',2)));

                if(ui->tableWidget_test->item(row,col+1))
                    ui->tableWidget_test->item(row,col+1)->setText(QString::number(la_pair.second,'f',2));
                else
                    ui->tableWidget_test->setItem(row,col+1,new QTableWidgetItem(QString::number(la_pair.second,'f',2)));
                ++row;
            }

            if(ch.t_s21_test.count(cur_freq)>0)
            {
                std::pair<double,double> la_pair = ch.t_s21_test[cur_freq];
                if(ui->tableWidget_test->item(row,col))
                    ui->tableWidget_test->item(row,col)->setText(QString::number(la_pair.first,'f',2));
                else
                    ui->tableWidget_test->setItem(row,col, new QTableWidgetItem(QString::number(la_pair.first,'f',2)));

                if(ui->tableWidget_test->item(row,col+1))
                    ui->tableWidget_test->item(row,col+1)->setText(QString::number(la_pair.second,'f',2));
                else
                    ui->tableWidget_test->setItem(row,col+1,new QTableWidgetItem(QString::number(la_pair.second,'f',2)));
                ++row;
            }
            col += 2;
        }
        ui->tableWidget_test->setHorizontalHeaderLabels(ls_list);
        ui->tableWidget_compare->setHorizontalHeaderLabels(ls_list);
    }
}

/*!
 * \brief PortChange::on_pushButton_compare_clicked
 *  比较
 */
void PortChange::on_pushButton_compare_clicked()
{
    int A = ui->lineEdit_A_phase->text().toInt();
    int B = ui->lineEdit_B_phase->text().toInt();
    if(m_test_data.count(A)>0&&m_test_data.count(B)>0)
    {
        CHAGE Adata = m_test_data[A];
        CHAGE Bdata = m_test_data[B];

        int col = 2;
        for(size_t i =0;i<Adata.t_freq.size();++i)
        {
            int row = 0;
            QString cur_freq = Adata.t_freq.at(i);
            double magn_calc,phase_calc,magn_test,phase_test =0;
            if(Adata.t_s21_calc.count(cur_freq) > 0 &&Bdata.t_s21_calc.count(cur_freq)>0)
            {
                magn_calc = (Adata.t_s21_calc[cur_freq].first - Bdata.t_s21_calc[cur_freq].first)/2;
                phase_calc = (Adata.t_s21_calc[cur_freq].second - Bdata.t_s21_calc[cur_freq].second)/2;
                if(ui->tableWidget_compare->item(row,col))
                    ui->tableWidget_compare->item(row,col)->setText(QString::number(magn_calc,'f',2));
                else
                    ui->tableWidget_compare->setItem(row,col,new QTableWidgetItem(QString::number(magn_calc,'f',2)));

                if(ui->tableWidget_compare->item(row,col+1))
                    ui->tableWidget_compare->item(row,col+1)->setText(QString::number(phase_calc,'f',2));
                else
                    ui->tableWidget_compare->setItem(row,col+1,new QTableWidgetItem(QString::number(phase_calc,'f',2)));
                row++;
            }
            if(Adata.t_s21_test.count(cur_freq) > 0 &&Adata.t_s21_test.count(cur_freq) >0)
            {
                magn_test = Adata.t_s21_test[cur_freq].first - Bdata.t_s21_test[cur_freq].first;
                phase_test = Adata.t_s21_test[cur_freq].second - Bdata.t_s21_test[cur_freq].second;

                if(ui->tableWidget_compare->item(row,col))
                    ui->tableWidget_compare->item(row,col)->setText(QString::number(magn_test,'f',2));
                else
                    ui->tableWidget_compare->setItem(row,col,new QTableWidgetItem(QString::number(magn_test,'f',2)));

                if(ui->tableWidget_compare->item(row,col+1))
                    ui->tableWidget_compare->item(row,col+1)->setText(QString::number(phase_test,'f',2));
                else
                    ui->tableWidget_compare->setItem(row,col+1,new QTableWidgetItem(QString::number(phase_test,'f',2)));
                row++;
            }
            double delt_magn = magn_calc - magn_test;
            double delt_phase = phase_calc - phase_test;

            if(ui->tableWidget_compare->item(row,col))
                ui->tableWidget_compare->item(row,col)->setText(QString::number(delt_magn,'f',2));
            else
                ui->tableWidget_compare->setItem(row,col,new QTableWidgetItem(QString::number(delt_magn,'f',2)));

            if(ui->tableWidget_compare->item(row,col+1))
                ui->tableWidget_compare->item(row,col+1)->setText(QString::number(delt_phase,'f',2));
            else
                ui->tableWidget_compare->setItem(row,col+1,new QTableWidgetItem(QString::number(delt_phase,'f',2)));
            col += 2;
        }
    }
}


/*!
 * \brief PortChange::on_pushButton_clicked
 * 点击测试按钮，进行测试
 */
void PortChange::on_pushButton_clicked()
{
    VNAdapter::s_vna = VNA_AGILENT;
    if(ui->comboBox_type->currentIndex())
        VNAdapter::s_vna = VNA_RS;
    if(!VNAdapter::instance()->connect())
    {
        QMessageBox::information(this,"Failed","PNA Connect failed !");
        return ;
    }
    calc_freq();

    m_cur_elec    = ui->comboBox_elec->currentIndex() +1;
    m_changePhase = ui->lineEdit_phase->text().toInt();
    m_power       =  ui->lineEdit_power->text().toDouble();
    m_if          = ui->lineEdit_if->text().toDouble()* pow(1000.0,ui->comboBox_if->currentIndex()) ;
    m_changeVNA   = ui->groupBox_2->isChecked();
    m_work_status = (ui->comboBox_status->currentIndex() ==0) ? RECEIVE:SEND;
    if(m_cur_row ==0 && m_test_data.size() ==0)
    {
        m_test_data[m_changePhase].t_cur_row = 0;
        m_test_data[m_changePhase].t_freq = m_freqs;
    }
    else
    {
        if(m_test_data.count(m_changePhase)==0)
        {
            m_cur_row += 6;
            m_test_data[m_changePhase].t_freq = m_freqs;
            m_test_data[m_changePhase].t_cur_row = m_cur_row ;
        }

    }
    ui->groupBox_2->setChecked(false);
    emit test();
}



/*!
 * \brief PortChange::testS11
 * 测试S11和S21
 */
void PortChange::testS11()
{
    TEleSwitch::instance()->turn_off_all();
    TSWMatrixs::instance()->turn_on(CVTS::Matrix(m_cur_elec-1));
    ::Sleep(100);
    int freq_size =  m_freqs.size();
    if(VNAdapter::instance()->connect())
    {
        if(m_changeVNA)
        {
            VNAdapter::instance()->delAll();
            VNAdapter::instance()->continue_triger();
            VNAdapter::instance()->set_trace_S11();

            VNAdapter::instance()->set_S21_TRACE(m_work_status = SEND);

            VNAdapter::instance()->set_power(m_power);
            VNAdapter::instance()->set_IF_bandwidth(m_if);
            VNAdapter::instance()->set_freq(m_freqs.at(0).toDouble(),\
                                            m_freqs.at(freq_size-1).toDouble(),
                                            freq_size);
        }
        QString s11_mach = VNAdapter::instance()->collect_S11();
        QStringList list_s11_mach = s11_mach.split(QRegExp(","));

        if(list_s11_mach.size() != freq_size*2)
        {
            s11_mach = VNAdapter::instance()->collect_S11();
            list_s11_mach = s11_mach.split(QRegExp(","));
        }

        QString s21 = VNAdapter::instance()->collectSendData(m_work_status = SEND);
        QStringList list_s21 = s21.split(QRegExp(","));

        if(list_s21.size() != freq_size*2)
        {
            s21 = VNAdapter::instance()->collectSendData(m_work_status = SEND);
            list_s21 = s21.split(QRegExp(","));
        }


        TEleSwitch::instance()->turn_on(CVTS::CVTS_Decetor(m_cur_elec-1));

        QString s11_short = VNAdapter::instance()->collect_S11();
        QStringList list_s11_short = s11_short.split(QRegExp(","));



        if(list_s11_short.size() != freq_size*2)
        {
            s11_short = VNAdapter::instance()->collect_S11();
            list_s11_short = s11_short.split(QRegExp(","));
        }


        if(list_s11_short.size() == freq_size*2 &&list_s11_mach.size() == freq_size*2 )
        {
            for(int l = 0; l <freq_size;++l)
            {
                ///处理 S11
                QString cur_freq = m_freqs.at(l);
                double real_11_m = list_s11_mach.at(2*l).toDouble();
                double imag_11_m = list_s11_mach.at(2*l+1).toDouble();
                double real_11_s = list_s11_short.at(2*l).toDouble();
                double imag_11_s = list_s11_short.at(2*l+1).toDouble();
                double real_21   = list_s21.at(2*l).toDouble();
                double imag_21   = list_s21.at(2*l+1).toDouble();

                double db_11_m      = SPCS_dB::dB(VNAdapter::instance()->genLinMag(real_11_m,imag_11_m));
                double phase_11_m   = VNAdapter::instance()->genPhase(real_11_m,imag_11_m);
                double db_11_s      = SPCS_dB::dB(VNAdapter::instance()->genLinMag(real_11_s,imag_11_s));
                double phase_11_s   = VNAdapter::instance()->genPhase(real_11_s,imag_11_s);
                double db_21        = SPCS_dB::dB(VNAdapter::instance()->genLinMag(real_21,imag_21));
                double phase_21     = VNAdapter::instance()->genPhase(real_21,imag_21);

                double s21_r        = real_11_m - real_11_s;
                double s21_s        = imag_11_m - imag_11_s;
                double db_21_calc   = SPCS_dB::dB(VNAdapter::instance()->genLinMag(s21_r,s21_s));
                double phase_21_Calc= VNAdapter::instance()->genPhase(s21_r,s21_s);


                m_test_data[m_changePhase].t_s11_match[cur_freq] = \
                        std::pair<double,double>(db_11_m,phase_11_m);
                m_test_data[m_changePhase].t_s11_short[cur_freq] =\
                        std::pair<double,double>(db_11_s,phase_11_s);
                m_test_data[m_changePhase].t_s21_test[cur_freq] =\
                        std::pair<double,double>(db_21,phase_21);
                m_test_data[m_changePhase].t_s21_calc[cur_freq] =\
                        std::pair<double,double>(db_21_calc,phase_21_Calc);

            }
        }
    }
}



/*!
 * \brief PortChange::calc_freq
 * 计算频率
 */
void PortChange::calc_freq()
{
    m_freqs.clear();
    double end_ = ui->lineEdit_end_freq->text().toDouble();
    double start_ = ui->lineEdit_start_freq->text().toDouble();

    if(end_ == start_ || ui->lineEdit_iter->text().toInt() == 1)
    {
        QString fre_cur = QString::number(end_*pow(1000.0,ui->comboBox_end->currentIndex()),'f',0);
        m_freqs.push_back(fre_cur);
    }else
    {

        if(end_<start_)
        {
            QMessageBox::information(this,tr("Error"),tr("Input error !"));
            return ;
        }
        if(end_> start_)
        {
            double step = (end_*pow(1000.0,ui->comboBox_end->currentIndex())\
                           - start_*pow(1000.0,ui->comboBox_start->currentIndex()))/(ui->lineEdit_iter->text().toInt()-1);
            for(int i=0; i<ui->lineEdit_iter->text().toInt(); i++)
            {
                QString fre_cur =QString::number(start_*pow(1000.0,ui->comboBox_start->currentIndex()) + step * i,'f',0);
                m_freqs.push_back(fre_cur);
            }
        }
    }

}

void PortChange::on_pushButton_clear_clicked()
{
    ui->tableWidget_test->clear();
    ui->tableWidget_compare->clear();
    m_test_data.clear();
    m_freqs.clear();
    m_cur_row = 0;
    set_compare_widget();
}
