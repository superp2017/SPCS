#include "configphase.h"
#include <QStringList>
#include <qmath.h>
#include <QDebug>
#include <QFile>


ConfigPhase::ConfigPhase()
{
    m_DMin_min = 100000;
    m_base_mp = 0;
    m_base_db  =0;
}

Task_Cmp &ConfigPhase::PhaseCalibration(std::vector<int> &p_id,\
                                        Task_S21 &p_s21, \
                                        Radar_Location &p_location, \
                                        SPoint &offset, \
                                        std::map<int,double>  &p_delt_data, \
                                        Task_CAL_S22 &p_cal_s21, \
                                        std::vector<QString> &p_freq_key, \
                                        std::map<QString,std::pair<double,double> > *p_base_mp, \
                                        double pbase_db)
{
    qDebug()<<"PhaseCalibration";
    if(p_id.size() > 0 && p_s21.size() >0 && p_location.size() >0)
    {
        ClearBuffer();
        m_id            = p_id;
        m_s21           = p_s21;
        m_location      = p_location;
        m_s21_cal       = p_cal_s21;
        m_freq_key      = p_freq_key;
        m_base_mp       = p_base_mp;
        m_delt_mag      = p_delt_data;
        m_base_db       = pbase_db;
        m_arrar_offset  = offset;
        //        qDebug()<<m_id.size()<<m_s11.size()<<m_s22.size()<<m_s21.size();
        //        qDebug()<<m_location.size()<<m_proj_path<<m_s21_cal.size();
        //        qDebug()<<m_freq_key.size();
        //      if(m_base_mp)qDebug()<<m_base_mp->size();
        //        qDebug()<<m_delt_mag.size()<<m_base_db;
        //        qDebug()<<m_isadd_s11;
        //        qDebug()<<"ClearBuffer";
        ///计算 原始的幅相及校准幅度Mag
        CalcORGMagnPhase();qDebug()<<"CalcORGMagnPhase()";
        ///计算D的最小值Dmin
        CalcDMin();qDebug()<<"CalcDMin";
        ///计算最终的校准幅度Mag' 和 Phase_d
        CalcMag_Phase_d();qDebug()<<"CalcMag_Phase_d";
        ///根据幅度加权值进行计算
        CalMag_Final();qDebug()<<"CalMag_Final";
        ///计算不同频率下各个阵元相位Phase’
        Calc_Phase_1();qDebug()<<"Calc_Phase_1";
        //////////整合mag`和phase`
        Calc_mp_1();qDebug()<<"Calc_mp_1";
        ///计算所有相位phase’的平均值、标准差、正态分布以及最终校准相位
        Calc_delt_phase();qDebug()<<"Calc_delt_phase";
    }else
    {
        qDebug()<<"ConfigPhase::PhaseCalibration error ,size == 0";
    }
    qDebug()<<"PhaseCalibration m_configpha_result"<<m_configpha_result.size();
    return m_configpha_result;
}



///计算 将所有原始数据的实虚部变为幅相,包括s11*s22 和 S21以及校准幅度Mag
void ConfigPhase::CalcORGMagnPhase()
{
    Task_S21::iterator iter21 = m_s21.begin();
    while(iter21 != m_s21.end())
    {
        QString cur_freq = iter21->first;
        if(cur_freq.isEmpty()) continue;
        std::map<int, QString > ls_map = iter21->second;
        for(size_t i =0;i<m_id.size();++i)
        {
            int id = m_id.at(i);
            if(ls_map.count(id))
            {
                QStringList ls_str_21 = ls_map[id].split(QRegExp(","));
                double ls_magn_s21,ls_phase_s21;
                if(ls_str_21.size()>1)
                {
                    ls_magn_s21   =  genMagn(ls_str_21.at(0).toDouble(),ls_str_21.at(1).toDouble());
                    ls_phase_s21  =  genPhase(ls_str_21.at(0).toDouble(),ls_str_21.at(1).toDouble());
                    m_Data2[cur_freq][id]   = std::pair<double,double>(ls_magn_s21,ls_phase_s21);
                    m_CAL_mag[cur_freq][id] = ls_magn_s21;
                }
            }
        }
        ++iter21;
    }
}

///计算D的最小值Dmin

void ConfigPhase::CalcDMin()
{
    for(size_t i = 0;i <m_id.size();++i)
    {
        int id = m_id.at(i);
        if(m_location.count(id)>0)
        {
            CVTS::SPoint ls_pos  = m_location[id].first;
            double X0   = ls_pos.x;
            double Y0   = ls_pos.y;
            double Z0   = ls_pos.z;
            int ls_M = m_location[id].second.first;
            int ls_N = m_location[id].second.second;
            double X1=(ls_N-8)*105-52.5;
            double ls_d = sqrt((X1-X0+m_arrar_offset.x)*(X1-X0+m_arrar_offset.x)+\
                               (ls_M*63-Y0+m_arrar_offset.y)*(ls_M*63-Y0+m_arrar_offset.y)+\
                               (2900-Z0+m_arrar_offset.z)*(2900-Z0+m_arrar_offset.z));
            m_DMin[id] = ls_d;
            if(ls_d < m_DMin_min)
                m_DMin_min = ls_d;
        }
    }
}

///计算最终的校准幅度Mag‘ 和 Phase_d
void ConfigPhase::CalcMag_Phase_d()
{
    std::map<QString,std::map<int,double> >::iterator iter =  m_CAL_mag.begin();
    while(iter != m_CAL_mag.end())
    {
        QString cur_freq = iter->first;
        if(cur_freq.isEmpty()) continue;
        double lamda = SPEEDOFLIGHT/cur_freq.toDouble() *1000;
        for(size_t i =0;i< m_id.size();++i)
        {
            int id = m_id.at(i);
            if(m_DMin.count(id)>0)
            {
                double ls_d = m_DMin[id] - m_DMin_min;
                double ls_M  = lamda/(4*M_PI*m_DMin[id]);
                if(m_CAL_mag[cur_freq].count(id)>0)
                {
                    double ls_magn =  m_CAL_mag[cur_freq][id] / ls_M;
                    m_Phase_d[cur_freq][id] = (ls_d -((int)(ls_d/lamda))*lamda)*360/lamda;


                    if(m_location.count(id)>0)
                    {
                        int pro =  m_location[id].second.second;
                        int dec = m_location[id].second.first;
                        if(m_s21_cal.count(dec)>0&&m_s21_cal[dec].count(pro)>0)
                        {
                            QString ls_cur_freq = cur_freq;
                            if(m_s21_cal[dec][pro].count(cur_freq)==0)
                                check_differ(ls_cur_freq);
                            ls_magn = ls_magn/(m_s21_cal[dec][pro][ls_cur_freq].first);
                            // qDebug()<<"cfg m_s21_cal db"<<SPCS_dB::dB(m_s21_cal[dec][pro][ls_cur_freq].first);
                        }else qDebug()<<"m_s21_cal has no key"<<pro<<dec;
                    }else qDebug()<<"m_location has no id"<<id;

                    if(ls_magn <= 0)
                        m_mag_1[cur_freq][id] = 0;
                    else
                        m_mag_1[cur_freq][id] = 20*log10(ls_magn);
                    //  qDebug()<<cur_freq<<m_mag_1[cur_freq][id];
                }
            }
        }
        ++iter;
    }
}


///////////////////计算幅度 dB值最大值,最终值往最大值靠近
void ConfigPhase::CalMag_Final()
{
    std::map<QString,std::map<int,double> >::iterator iter =  m_mag_1.begin();
    while(iter != m_mag_1.end())
    {
        std::map<int,double> ls_vec = iter->second;
        QString cur_freq = iter->first;
        double base_magn =0 ;
        if(m_base_mp)
        {
            if(m_base_mp->count(cur_freq)>0)
            {
                base_magn = m_base_mp->at(cur_freq).first;
            }else
                base_magn = 0;
        }else
        {   //////算出权值为0的id对应的mag`的最小值
            std::vector<double> ls_data;
            for(size_t i =0;i< m_id.size();++i)
            {
                int id = m_id.at(i);
                if(m_delt_mag.count(id)>0 && ls_vec.count(id) >0)
                {
                    if(m_delt_mag[id] >= m_base_db)
                    {
                        ls_data.push_back(ls_vec[id]);
                    }
                }else
                    qDebug()<<"m_delt_mag.count(id)>0 && ls_vec.count(id) >0";
            }

            for(size_t j =0;j<ls_data.size();++j)
            {
                base_magn += ls_data.at(j);
            }

            qDebug()<<"base_magn sum"<<base_magn<<"ls_data"<<ls_data.size();

            if(ls_data.size()>0)
                base_magn = base_magn/(ls_data.size()*1.0);
            /////////////////2014/7/4 暂时不需要减1dB,因为有人为干预
            ///    base_magn -=1;

            m_cur_base_mp[cur_freq].first = base_magn;
        }
        qDebug()<<"ls_base_magn" <<base_magn;
        /////////////算出最终的配幅值
        for(size_t i =0;i< m_id.size();++i)
        {
            int id = m_id.at(i);

            if(m_delt_mag.count(id)>0&& ls_vec.count(id) >0)
            {
                double ls_magn = m_delt_mag[id] - (ls_vec[id] - base_magn );
                if(!m_base_mp)
                {
                    if(ls_magn>0)
                        ls_magn =0;
                }
                m_CAL_mag_final[cur_freq][id] = ls_magn;
            }else qDebug()<<"_delt_mag.count(id)>0&& ls_vec.count(id) >0";
        }
        /// qDebug()<<"m_CAL_mag_final"<<cur_freq<<m_CAL_mag_final[cur_freq].size();
        ++iter;
    }
    ///qDebug()<<"m_CAL_mag_final"<<m_CAL_mag_final.size();
}

///计算不同频率下各个阵元相位Phase’
void ConfigPhase::Calc_Phase_1()
{
   qDebug()<<"Calc_Phase_1 m_Data2 "<<m_Data2.size();
    Task_Cmp::iterator iter =  m_Data2.begin();
    while(iter!= m_Data2.end())
    {
        QString cur_freq = iter->first;
        if(cur_freq.isEmpty()) continue;
        for(size_t i = 0;i<m_id.size();++i)
        {
            int id = m_id.at(i);
            if( m_Data2[cur_freq].count(id)>0 && m_Phase_d[cur_freq].count(id) >0)
            {
                /////////////////////////////////////////
                /// \brief phase
                ///mp 6.9
                double phase=  m_Data2[cur_freq][id].second;
                if(m_location.count(id)>0)
                {
                    int pro =  m_location[id].second.second;
                    int dec =  m_location[id].second.first;
                    //////////////////////
                    //////////////2014.7.3
                    if(m_s21_cal.count(dec)>0&&m_s21_cal[dec].count(pro)>0)
                    {
                        QString ls_cur_freq = cur_freq;
                        if(m_s21_cal[dec][pro].count(cur_freq)==0)
                        {
                            check_differ(ls_cur_freq);
                        }
                        double ls_cal_s21_phase =  m_s21_cal[dec][pro][ls_cur_freq].second;
                        // qDebug()<<"cfg m_s21_cal phase"<<m_s21_cal[dec][pro][ls_cur_freq].second;
                        ///////////////////////
                        //////////////
                        ///2014/06/27 11:33

                        ////  phase = phase   - ls_cal_s21_phase ;

                        phase = phase   - ls_cal_s21_phase ;

                    }else
                        qDebug()<<"Calc_Phase_1 m_s21_cal has no key"<<pro<<dec;
                }else
                    qDebug()<<"Calc_Phase_1 m_location has no id"<<id;

                //////////////////////////////////
                /// \brief ls_phase_1
                ////////
                ///     +  -   2014/6/26 10:41
#if 0
                double ls_phase_1 = phase - m_Phase_d[cur_freq][id];
#endif
#if 1
                double ls_phase_1 = phase  + m_Phase_d[cur_freq][id];
#endif
                ls_phase_1 = ls_phase_1 - 360*((int)(ls_phase_1/360));
                if(ls_phase_1 >180)  ls_phase_1 -= 360;
                if(ls_phase_1 <-180) ls_phase_1 += 360;
                m_Phase_1[cur_freq][id] = ls_phase_1;
            }
        }
        ++iter;
    }
}

void ConfigPhase::Calc_mp_1()
{
    std::map<QString,std::map<int,double> >::iterator iter = m_Phase_1.begin();
    while(iter != m_Phase_1.end())
    {
        QString cur_freq = iter->first;
        if(m_mag_1.count(cur_freq)>0)
        {
            for(size_t i = 0;i<m_id.size();++i)
            {
                int id = m_id.at(i);
                if((iter->second).count(id)>0&&m_mag_1[cur_freq].count(id)>0)
                {
                    m_cfg_mp_1[cur_freq][id] =\
                            std::pair<double,double>(m_mag_1[cur_freq][id],(iter->second)[id]);
                }
            }
        }
        ++iter;
    }
}

///计算所有相位phase’的平均值、标准差、正态分布以及最终校准相位
void ConfigPhase::Calc_delt_phase()
{    
    qDebug()<<"m_Phase_1"<<m_Phase_1.size();
    std::map<QString,std::map<int,double> >::iterator iter = m_Phase_1.begin();
    while(iter != m_Phase_1.end())
    {
        double ave_phase   = 0;
        double ls_std      = 0;
        double MAX_density = -1000;
        QString cur_freq = iter->first;
        if(cur_freq.isEmpty()) continue;
        ///计算平均值
        for(size_t i = 0;i<m_id.size();++i)
        {
            int id = m_id.at(i);
            if(m_Phase_1[cur_freq].count(id)>0)
                ave_phase += m_Phase_1[cur_freq][m_id.at(i)];
        }
        ave_phase = ave_phase/m_id.size();
        ///计算标准差
        for(size_t i = 0;i<m_id.size();++i)
        {
            int id = m_id.at(i);
            if(m_Phase_1[cur_freq].count(id)>0)
            {
                double phase0 = m_Phase_1[cur_freq][id];
                ls_std += (phase0- ave_phase)*(phase0- ave_phase);
            }
        }
        ls_std = sqrt(ls_std/m_id.size());
        std::map<double,double> ls_map;
        ///计算正态分布
        for(size_t i = 0;i<m_id.size();++i)
        {
            int id = m_id.at(i);
            if(m_Phase_1[cur_freq].count(id)>0)
            {
                double ls_des = Calc_Density(m_Phase_1[cur_freq][id],ls_std,ave_phase);
                ls_map[ls_des] = m_Phase_1[cur_freq][id];
                if(ls_des >MAX_density)
                    MAX_density = ls_des;
            }else
                qDebug()<<"m_Phase_1[cur_freq].count(id) =0";

        }
        double phase_mid = ls_map[MAX_density];
        if(m_base_mp)
        {
            if(m_base_mp->count(cur_freq)>0)
                phase_mid =  m_base_mp->at(cur_freq).second;
        }

        m_cur_base_mp[cur_freq].second = phase_mid;

        // qDebug()<<"freq = "<<iter->first<<"phase_mid"<<phase_mid;

        ///计算delt_phase
        for(size_t i = 0;i<m_id.size();++i)
        {
            int id = m_id.at(i);
            if(m_Phase_1[cur_freq].count(id)>0)
            {
                double Delt_Phase = m_Phase_1[cur_freq][id] - phase_mid;
                // Delt_Phase =  Search_phase(Delt_Phase);
                if(m_CAL_mag_final[cur_freq].count(id)>0)
                    m_configpha_result[cur_freq][id] = std::pair<double,double>(m_CAL_mag_final[cur_freq][id],Delt_Phase);
                else  qDebug()<<"m_CAL_mag_final[cur_freq].count(id) =0";
            }else
                qDebug()<<"m_Phase_1[cur_freq].count(id)=0";
        }
        ++iter;
    }
}
///计算相位的概率密度(正态分布)
double ConfigPhase::Calc_Density(double phase,double std,double ave)
{
    return 1/(std*sqrt(2*M_PI)) * pow(M_E,(-(phase-ave)/(2*std*std)));
}

double ConfigPhase::Search_phase(double phase)
{
    double ls_phase_1 = phase;
    if(ls_phase_1 >180) ls_phase_1 -= 360;
    if(ls_phase_1 <-180) ls_phase_1 += 360;
    for(double i = -180;i<180;)
    {
        if( ls_phase_1 == i )
            return i;
        if(ls_phase_1 > i && ls_phase_1 <(i+5.625))
        {
            if(abs(ls_phase_1-i)< abs(ls_phase_1-i-5.625))
                return i;
            else
                return i+5.625;
        }
        i += 5.625;
    }
    return ls_phase_1;
}


void ConfigPhase::ClearBuffer()
{
    m_id.clear();
    m_s21.clear();
    m_location.clear();
    m_Data2.clear();
    m_configpha_result.clear();
    m_cfg_mp_1.clear();

    m_DMin.clear();
    m_CAL_mag.clear();
    m_CAL_mag_final.clear();
    m_Phase_d.clear();
    m_Phase_1.clear();
    m_mag_1.clear();

    m_Ave_std_Phase_1.clear();
    m_delt_mag.clear();
    m_s21_cal.clear();
    m_freq_key.clear();
}

std::map<QString, std::map<int, double> > &ConfigPhase::get_Phase1()
{
    return m_Phase_1;
}

///////行列转化成ID
int ConfigPhase::gen_id(short row, short col)
{
    char *c_id = (char*)malloc(4);
    memset(c_id,0,4);
    memcpy(c_id,&col,2);
    memcpy(c_id+2,&row,2);
    int id = *((int*)c_id);
    delete c_id;
    c_id = 0;
    return id;
}

double ConfigPhase::genMagn(double real, double imag)
{
    return sqrt(real*real+imag*imag);
}

double ConfigPhase::genPhase(double real, double imag)
{
    return qAtan2(imag, real) / M_PI * 180;
}

void ConfigPhase::check_differ(QString &curfreq)
{
    for(size_t i =0;i<m_freq_key.size();++i)
    {
        double ls_freq = m_freq_key.at(i).toDouble();
        double ls_next = m_freq_key.at(i+1).toDouble();
        double cur = curfreq.toDouble();
        
        if((i+1)<m_freq_key.size())
        {
            if(ls_freq<= cur && ls_next >=cur)
            {
                if(ls_freq == cur)
                {
                    curfreq = m_freq_key.at(i);
                    return;
                }
                if(cur == ls_next)
                {
                    curfreq = m_freq_key.at(i+1);
                    return;
                }
                
                if(abs(ls_freq-cur)<abs(ls_next-cur))
                {
                    curfreq = m_freq_key.at(i);
                    return ;
                }
                else
                {
                    curfreq = m_freq_key.at(i+1);
                    return ;
                }
            }
        }else
        {
            curfreq = m_freq_key.at(i);
            return ;
        }
    }
}


void ConfigPhase::IdToAddr(int id, short &row, short &col)
{
    char *c_id = (char*)&id;
    row = *((short*)c_id+1);
    col = *((short*)c_id);
}
