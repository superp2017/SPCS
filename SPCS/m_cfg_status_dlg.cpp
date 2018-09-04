#include "m_cfg_status_dlg.h"
#include "ui_m_cfg_status_dlg.h"
#include <QMessageBox>
#include <QDebug>

m_cfg_status_dlg::m_cfg_status_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::m_cfg_status_dlg)
{
    ui->setupUi(this);
    m_nums = 0;
    m_step = 0;
    m_values = 0;
    m_cur_add_db = 0;
    ui->lineEdit_db->setText("0.01");
    ui->lineEdit_phase->setText("1");
    ui->lineEdit_db_db_nums->setText("10");
    ui->lineEdit_db_ray_db->setText("5");
    ui->lineEdit_dev_db->setText("-1");
    ui->lineEdit_phase_num->setText("10");
    ui->lineEdit_phase_ray->setText("5");
    ui->radioButton_rate->setChecked(true);
    ui->lineEdit_dev_db->setEnabled(false);
    connect(this,SIGNAL(note(double,QString)),this,SLOT(note_success(double,QString)),Qt::QueuedConnection);
    connect(this,SIGNAL(note_2(double,QString)),this,SLOT(note_cur_rate(double,QString)),Qt::QueuedConnection);
    connect(this,SIGNAL(calc(bool)),&m_thread,SLOT(CALC(bool)),Qt::QueuedConnection);
    connect(ui->comboBox_db,SIGNAL(currentIndexChanged(int)),this,SLOT(update_rate()));
    this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

m_cfg_status_dlg::~m_cfg_status_dlg()
{
    delete ui;
}

std::map<QString,std::pair<double,double> > & m_cfg_status_dlg::get_base_mp()
{
    return   m_base_data;
}

void m_cfg_status_dlg::init_data(Task_Cmp &p_cmp,Task_Cmp &p_cmp_1, std::vector<QString> pfreqs, \
                                 std::map<int,double>  &p_delt_data, double &p_delt_db, \
                                 std::map<QString,std::pair<double,double> > &p_base_mp , \
                                 std::vector<int> &p_id)
{  
    m_base_data.clear();
    m_cal_data.clear();
    m_delt_data.clear();
    m_cal_mp_1.clear();
    m_base_data = p_base_mp;
    m_cal_mp_1  = p_cmp_1;
    m_cal_data  = p_cmp;
    m_delt_data = p_delt_data;
    m_add_db    = p_delt_db;
    m_id        = p_id;
    m_freqs     = pfreqs;
    m_cur_add_db = m_add_db;
    for(size_t i =0;i<pfreqs.size();++i)
    {
        QString cur_freq = pfreqs.at(i);
        ui->comboBox_db->addItem(cur_freq);
        ui->comboBox_phase->addItem(cur_freq);
    }


    calc_ave();
    calc_delt_rate(m_add_db);
    ui->lineEdit_delt_db->setText(QString::number(m_add_db,'f',2));
}

/*!
 * \brief m_cfg_status_dlg::calc_magn
 * 迭代计算幅度值
 */
void m_cfg_status_dlg::calc_magn()
{
    if(m_cal_data.count(m_cur_freq)>0)
    {
        std::map<int, std::pair<double, double> >  ls_map = m_cal_data[m_cur_freq];
        double  rate = 1;
        for(int i =0;i<m_nums;++i)
        {
            if(check_status(true,rate))
            {
                emit  note(rate,m_cur_freq);
                break;
            }

            std::map<int, std::pair<double, double> >::iterator iter = ls_map.begin();
            while(iter != ls_map.end())
            {
                int id = iter->first;
                m_cal_data[m_cur_freq][id].first += m_values;

                if(m_cal_data[m_cur_freq][id].first < -31.5)
                    m_cal_data[m_cur_freq][id].first = -31.5;
                ++iter;
            }
            if(m_base_data.count(m_cur_freq)>0)
            {
                m_base_data[m_cur_freq].first += m_values;
            }
        }
        rate = 1;
        if(!check_status(true,rate))
        {
            emit note_2(rate,m_cur_freq);
        }else
        {
            emit note(rate,m_cur_freq);
        }
    }
}




/*!
 * \brief m_cfg_status_dlg::calc_phase
 * 迭代计算校准值得相位
 */
void m_cfg_status_dlg::calc_phase()
{
    if(m_cal_data.count(m_cur_freq)>0)
    {
        std::map<int, std::pair<double, double> >  ls_map = m_cal_data[m_cur_freq];

        double  rate = 1;
        for(int i =0;i<m_nums;++i)
        {
            if(check_status(false,rate))
            {
                emit note(rate,m_cur_freq);
                break;
            }
            std::map<int, std::pair<double, double> >::iterator iter = ls_map.begin();
            while(iter != ls_map.end())
            {
                int id = iter->first;
                m_cal_data[m_cur_freq][id].second -= m_values;
                if(m_cal_data[m_cur_freq][id].second < -180)
                    m_cal_data[m_cur_freq][id].second += 360;
                if(m_cal_data[m_cur_freq][id].second >180)
                    m_cal_data[m_cur_freq][id].second -= 360;
                ++iter;
            }
            if(m_base_data.count(m_cur_freq)>0)
            {
                m_base_data[m_cur_freq].second += m_values;
                if(m_base_data[m_cur_freq].second >180)
                    m_base_data[m_cur_freq].second -= 360;
                if(m_base_data[m_cur_freq].second <-180)
                    m_base_data[m_cur_freq].second += 360;
            }
        }
        rate = 1;
        if(!check_status(false,rate))
        {
            emit  note_2(rate,m_cur_freq);
        }else
        {
            emit note(rate,m_cur_freq);
        }
    }
}

void m_cfg_status_dlg::on_pushButton_ok_clicked()
{
    done(0);
}


/*!
 * \brief m_cfg_status_dlg::calc_ave
 * 计算校准值平均值
 */
void m_cfg_status_dlg::calc_ave()
{
    Task_Cmp::iterator iter = m_cal_data.begin();
    while(iter != m_cal_data.end())
    {
        std::map<int, std::pair<double, double> > ls_map    = iter->second;
        std::map<int, std::pair<double, double> >::iterator iter2 = ls_map.begin();
        double max = -100;
        double min = 100;
        double sum = 0;
        while(iter2!= ls_map.end())
        {
            double db  = iter2->second.first;
            if(db > max) max = db;
            if(db < min) min = db;
            sum +=db;
            ++iter2;
        }

        m_cal_minmax[iter->first] = std::pair<double,double> (min,max);
        m_cal_ave[iter->first] = sum*1.0/(int)(ls_map.size());
        ++iter;
    }
    update_rate();
}

void m_cfg_status_dlg::on_pushButton_calc_db_clicked()
{
    if(ui->lineEdit_db->text().isEmpty() ||\
            ui->lineEdit_db_db_nums->text().isEmpty()||\
            ui->lineEdit_db_ray_db->text().isEmpty())
        note_empty();
    else
    {
        m_nums      = ui->lineEdit_db_db_nums->text().toInt();
        m_cur_freq  = ui->comboBox_db->currentText();
        m_values    = ui->lineEdit_db->text().toDouble();

        double  rate = 1;
        if(check_status(true,rate))
        {
            note_success(rate,ui->comboBox_db->currentText());
            return;
        }
        if(ui->radioButton_rate->isChecked())
        {
            emit  calc(true);
        }else{
            calc_valuse(m_cur_freq);
        }
    }
}



/*!
 * \brief m_cfg_status_dlg::calc_valuse
 * \param pfreq
 * 量级计算
 */
void m_cfg_status_dlg::calc_valuse(QString &pfreq)
{
    if(m_cal_data.count(pfreq)>0)
    {
        double  rate = 1;
        if(check_status(true,rate))
        {
            emit  note(rate,m_cur_freq);
            return ;
        }
        double value =  ui->lineEdit_dev_db->text().toDouble();
        reCalc_cal(pfreq,value);
        rate = 1;
        if(!check_status(true,rate))
        {
            emit note_2(rate,m_cur_freq);
        }else
        {
            emit note(rate,m_cur_freq);
        }
    }
}


void m_cfg_status_dlg::on_pushButton_calc_phase_clicked()
{
    if(ui->lineEdit_phase->text().isEmpty()||\
            ui->lineEdit_phase_num->text().isEmpty()||\
            ui->lineEdit_phase_ray->text().isEmpty())
        note_empty();
    else
    {
        m_nums = ui->lineEdit_phase_num->text().toInt();
        m_cur_freq = ui->comboBox_phase->currentText();

        m_values = ui->lineEdit_phase->text().toDouble();
        double  rate = 1;
        if(check_status(false,rate))
        {
            note_success(rate,ui->comboBox_phase->currentText());
            return;
        }
        emit  calc(false);
    }
}




bool m_cfg_status_dlg::check_status(double ismagn,double &rate)
{
    double ray  = 0;
    QString freq;
    if(ismagn)
    {
        ray   = ui->lineEdit_db_ray_db->text().toDouble();
        freq  = ui->comboBox_db->currentText();
        int num=0;
        int size=0;
        if(m_cal_data.count(freq)>0)
        {
            std::map<int, std::pair<double, double> >  ls_map = m_cal_data[freq];
            std::map<int, std::pair<double, double> >::iterator iter = ls_map.begin();
            size = ls_map.size();
            while(iter != ls_map.end())
            {
                if( iter->second.first>0)
                    num++;
                ++iter;
            }
        }
        double cur_ray = num/(size*1.0);
        rate = cur_ray;
        if(cur_ray*100 <= ray)
        {
            return true;
        }
        return false;

    }else
    {
        ray   = ui->lineEdit_phase_ray->text().toDouble();
        freq  = ui->comboBox_phase->currentText();
        int num  = 0;
        int size = 0;
        if(m_cal_data.count(freq)>0)
        {
            std::map<int, std::pair<double, double> >  ls_map = m_cal_data[freq];
            std::map<int, std::pair<double, double> >::iterator iter = ls_map.begin();
            size = ls_map.size();
            while(iter != ls_map.end())
            {
                double phase = iter->second.second;
                if(phase<0)
                    phase += 360;
                if(phase>=300)
                    num++;
                ++iter;
            }
        }
        double cur_ray = num/(size*1.0);
        rate = cur_ray;
        if(cur_ray*100 <= ray)
        {
            return true;
        }
        return false;
    }
    return false;
}


void m_cfg_status_dlg::on_radioButton_rate_clicked()
{
    ui->lineEdit_db->setEnabled(true);
    ui->lineEdit_db_db_nums->setEnabled(true);
    ui->lineEdit_db_ray_db->setEnabled(true);
    ui->lineEdit_dev_db->setEnabled(false);

}


void m_cfg_status_dlg::on_radioButton_value_clicked()
{
    ui->lineEdit_db->setEnabled(false);
    ui->lineEdit_db_db_nums->setEnabled(false);
    ui->lineEdit_db_ray_db->setEnabled(false);
    ui->lineEdit_dev_db->setEnabled(true);
}

/*!
 * \ 点击重新计算按钮
 * \brief m_cfg_status_dlg::on_pushButton_recalc_clicked
 */
void m_cfg_status_dlg::on_pushButton_recalc_clicked()
{
    if(ui->lineEdit_delt_db->text().isEmpty()) return;
    double cur_db = ui->lineEdit_delt_db->text().toDouble();

    if(cur_db == m_cur_add_db)
    {
        qDebug()<<"cur_db == m_cur_add_db";
        return ;
    }

    ///减去之前的基准值
    for(size_t i =0;i<m_freqs.size();++i)
    {
        QString freq = m_freqs.at(i);
        if(m_cal_mp_1.count(freq)>0)
        {
            double old_base = calc_base(freq,m_cur_add_db);
            reCalc_cal(freq,-old_base);
        }
    }

    ///根据新的加权值重新计算新的基准值
    for(size_t i =0;i<m_freqs.size();++i)
    {
        QString freq = m_freqs.at(i);
        double old_base = calc_base(freq,cur_db);
        reCalc_cal(freq,old_base);
    }
    m_cur_add_db = cur_db;
    calc_delt_rate(cur_db);
    calc_ave();
}

/*!
 * \brief m_cfg_status_dlg::reCalc_cal
 * \param cur_freq
 * 根据给定的不同的加权值范围 重新计算校准值和基准值
 *  \param value
 */
void m_cfg_status_dlg::reCalc_cal(QString cur_freq, double value)
{
    ////计算校准值
    if(m_cal_data.count(cur_freq))
    {
        for(size_t i =0;i<m_id.size();++i)
        {
            int id = m_id.at(i);
            if(m_cal_data[cur_freq].count(id)>0)
            {
                m_cal_data[cur_freq][id].first  += value;

                if(m_cal_data[cur_freq][id].first < -31.5)
                    m_cal_data[cur_freq][id].first = -31.5;
            }
        }
    }
    //////计算基准值
    if(m_base_data.count(cur_freq)>0)
    {
        m_base_data[m_cur_freq].first = m_base_data[m_cur_freq].first+ value;
    }
}


/*!
 * \brief m_cfg_status_dlg::calc_base
 * \param db
 * \return
 * 根据给定的不同的加权值范围 重新计算基准值
 */
double m_cfg_status_dlg::calc_base(QString cur_freq,double db)
{
    if(m_cal_mp_1.count(cur_freq)>0)
    {
        std::map<int, std::pair<double, double> > ls_pair = m_cal_mp_1[cur_freq] ;
        double base_magn = 0;
        std::vector<double> ls_data;
        for(size_t i =0;i< m_id.size();++i)
        {
            int id = m_id.at(i);
            if(m_delt_data.count(id)>0 && ls_pair.count(id) >0)
            {
                if(m_delt_data[id] >= db)
                {
                    ls_data.push_back(ls_pair[id].first);
                }
            }else
                qDebug()<<"m_cfg_status_dlg::calc_base m_delt_mag.count(id)>0 && ls_vec.count(id) >0";
        }

        for(size_t j =0;j<ls_data.size();++j)
        {
            base_magn += ls_data.at(j);
        }

        if(ls_data.size()>0)
            base_magn = base_magn/(ls_data.size()*1.0);

        else
            qDebug()<<"ls_data.size()==0";
        qDebug()<<"ls_data.size()"<<ls_data.size();
        return base_magn;
    }else
        qDebug()<<"m_cal_mp_1.count(cur_freq)>0)";
    return 0;
}

/*!
 * \brief m_cfg_status_dlg::calc_delt_rate
 * \param value
 *   计算当前加权值的比例
 * \return
 */
void m_cfg_status_dlg::calc_delt_rate(double value)
{
    double sum = 0;
    double rate =0;
    for(size_t i =0;i< m_id.size();++i)
    {
        int id = m_id.at(i);
        if(m_delt_data.count(id)>0)
        {
            if(m_delt_data[id] >= value)
            {
                sum++;
            }
        }
    }
    rate = sum*1.0/(int)m_delt_data.size() *100;
    update_add_delt_rate(value,rate);
}

void m_cfg_status_dlg::update_add_delt_rate(double value,double rate)
{
    QString text = CVTS::GBKToUnicode::toUnicode("当前加权值为:")+\
            QString::number(value,'f',3) + \
            CVTS::GBKToUnicode::toUnicode(",大于等于此加权值的比例为:")+\
            QString::number(rate,'f',3)+QString("%");
    ui->label_add_delt->setText(text);
}


void m_cfg_status_dlg::update_rate()
{
    QString freq = ui->comboBox_db->currentText();
    if(m_cal_minmax.count(freq)>0&&m_cal_ave.count(freq)>0)
    {
        QString text = CVTS::GBKToUnicode::toUnicode("频率:")+freq + \
                CVTS::GBKToUnicode::toUnicode(",最小值:")+\
                QString::number(m_cal_minmax[freq].first,'f',3)+\
                CVTS::GBKToUnicode::toUnicode(",最大值:")+\
                QString::number(m_cal_minmax[freq].second,'f',3)+\
                CVTS::GBKToUnicode::toUnicode("平均值:")+\
                QString::number(m_cal_ave[freq],'f',3);
        ui->label_15->setText(text);
    }else
    {
        QString text = CVTS::GBKToUnicode::toUnicode("频率:")+freq + \
                CVTS::GBKToUnicode::toUnicode(",最小值:")+\
                QString::number(0,'f',3)+\
                CVTS::GBKToUnicode::toUnicode(",最大值:")+\
                QString::number(0,'f',3)+\
                CVTS::GBKToUnicode::toUnicode("平均值:")+\
                QString::number(0,'f',3);
        ui->label_15->setText(text);
    }

}


void m_cfg_status_dlg::note_empty()
{
    QMessageBox mes;
    QString title = CVTS::GBKToUnicode::toUnicode("提示");
    QString text = CVTS::GBKToUnicode::toUnicode("信息填写不完整");
    mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    mes.setWindowTitle(title);
    mes.setText(text);
    mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    mes.exec();
}

void m_cfg_status_dlg::note_success(double rate,QString freq)
{
    QMessageBox mes;
    QString title = CVTS::GBKToUnicode::toUnicode("提示");
    QString info =  CVTS::GBKToUnicode::toUnicode("当前频率为：")+freq+CVTS::GBKToUnicode::toUnicode(",\n比率为：")+ \
            QString::number(rate*100,'f',2) +CVTS::GBKToUnicode::toUnicode("%");
    mes.setInformativeText(info);
    QString text = CVTS::GBKToUnicode::toUnicode("已经满足条件");
    mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    mes.setWindowTitle(title);
    mes.setText(text);
    mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    mes.exec();
}

void m_cfg_status_dlg::note_cur_rate(double rate, QString freq)
{
    QMessageBox mes;
    QString title = CVTS::GBKToUnicode::toUnicode("提示");
    QString info =  CVTS::GBKToUnicode::toUnicode("当前频率为：")+freq+CVTS::GBKToUnicode::toUnicode(",\n比率为：")+ \
            QString::number(rate*100,'f',2) + CVTS::GBKToUnicode::toUnicode("%");
    mes.setInformativeText(info);
    QString text = CVTS::GBKToUnicode::toUnicode("暂未满足条件");
    mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    mes.setWindowTitle(title);
    mes.setText(text);
    mes.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    mes.exec();
}
