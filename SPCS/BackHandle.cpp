#include "BackHandle.h"
#include "troublecheck.h"
#include "taskcenter_607.h"

BackHandle::BackHandle(QObject *parent) :
    QObject(parent)
{
}

BackHandle::~BackHandle()
{
    clean();
}

void BackHandle::manager()
{              
    dataAnaly_org(m_org_data,m_org);
    dataAnaly_cfg_mp(m_cfg_mp_data,m_cfg_mp);
    dataAnaly_cfg_mp(m_cfg_m_mp_data,m_cfg_m_mp);
    dataAnaly_cfg_final(m_final_cfg,m_cfg_final);

    TestResult::instance()->initData(m_org,m_cfg_mp,m_cfg_m_mp,m_cfg_final,m_id,m_freq);
    RadarAnaly::instance()->load_face(m_org,m_cfg_mp,m_cfg_m_mp,m_cfg_final,m_radars,m_id,m_freq);

}

/////////////
/// \brief BackHandle::DATA_Manage
/// \param p_org_data   初态数据
/// \param p_cfg_mp_data   幅度相位一起配的数据
/// \param p_cfg_m_mp_data 先配幅度后配相位的数据
/// \param p_final_cfg     最终的校准数据
/// \param p_id
/// \param p_freq
/// \param p_radars
/// 工程打开时调用的接口
void BackHandle::DATA_Manage( TDATA &p_org_data, \
                              std::map<int, TDATA> &p_cfg_mp_data, \
                              std::map<int, TDATA> &p_cfg_m_mp_data,
                              Task_Cmp &p_final_cfg,\
                              std::vector<int> &p_id, \
                              std::vector<QString> &p_freq,\
                              std::map<int, Radar *> &p_radars)
{
    clean();
    m_org_data         = p_org_data;
    m_cfg_mp_data      = p_cfg_mp_data;
    m_cfg_m_mp_data    = p_cfg_m_mp_data;
    m_final_cfg        = p_final_cfg;
    m_id               = p_id;
    m_freq             = p_freq;
    m_radars           = p_radars;

    manager();
}


////////////
/// \brief BackHandle::HandleData
/// 测试结束的信号相应槽
void BackHandle::HandleData()
{
    clean();
    m_id            = TaskCenter_607::instance()->get_id();
    m_freq          = TaskCenter_607::instance()->get_freqs();
    m_radars        = TaskCenter_607::instance()->get_radars();
    m_cfg_mp_data   = TaskCenter_607::instance()->get_cfg_mp_data();
    m_cfg_m_mp_data = TaskCenter_607::instance()->get_cfg_m_mp_data();
    m_org_data      = TaskCenter_607::instance()->get_org_data();
    m_final_cfg     = TaskCenter_607::instance()->get_final_cal_Data();

    manager();
}

////////
/// \brief BackHandle::dataAnaly_org
/// \param tData
/// \param p_org
///
void BackHandle::dataAnaly_org(TDATA &tData, H_ORG &p_org)
{
    QString ls_type = S_1_1;
    analy(tData,p_org,ls_type);
    ls_type = S_2_2;
    analy(tData,p_org,ls_type);
    ls_type = S_2_1;
    analy(tData,p_org,ls_type);
    ls_type = TYPE_CFG;
    analy(tData,p_org,ls_type);
    ls_type = TYPE_MP_1;
    analy(tData,p_org,ls_type);
}

////
/// \brief BackHandle::dataAnaly_cfg_mp
/// \param tData
/// \param t_cfg_mp
/// 转化幅度相位一起的数据
void BackHandle::dataAnaly_cfg_mp(std::map<int, TDATA> &tData,H_CFG_MP &t_cfg_mp)
{    
    for(size_t i  = 0;i < tData.size(); ++i)
    {
        dataAnaly_org(tData[i],t_cfg_mp[i]);
    }
}


/////
/// \brief BackHandle::dataAnaly_cfg_final
/// \param tData
/// \param t_cfg_final
/// 转化最终的校准值
void BackHandle::dataAnaly_cfg_final(Task_Cmp &tData,H_CFG_FINAL &t_cfg_final)
{   
    for(size_t i =0; i< m_freq.size(); ++i)
    {
        QString cur_freq = m_freq.at(i);
        QString key ;
        CVTS::DoubleFre_TO_QStringFreq::Double_TO_QString(cur_freq.toDouble(),key);
        for(size_t j =0;j<m_id.size();++j)
        {
            int id = m_id.at(j);
            if(tData.count(cur_freq)>0 && tData[cur_freq].count(id)>0)
            {
                double magn  = tData[cur_freq][id].first;
                double phase = tData[cur_freq][id].second;
                if(phase > 180)
                    phase -= 360;
                else if(phase < -180)
                    phase += 360;
                t_cfg_final[key][id] = std::pair<QString,QString>\
                        (QString::number(magn,'f'),QString::number(phase,'f'));
            }
        }
    }
}

void BackHandle::analy(TDATA &tData,H_ORG &p_org,QString type)
{
    if(type == S_1_1 || type == S_2_2  ||type == S_2_1 )
    {
        Task_Res    ls_res;
        if(type == S_1_1)
            ls_res  =  tData.t_task_s11_open;
        if(type == S_2_2)
            ls_res  =  tData.t_task_s22_open;
        if(type == S_2_1)
            ls_res  =  tData.t_task_s21;

        for(size_t i =0; i< m_freq.size(); ++i)
        {
            QString cur_freq = m_freq.at(i);
            QString key ;
            CVTS::DoubleFre_TO_QStringFreq::Double_TO_QString(cur_freq.toDouble(),key);
            for(size_t j =0;j<m_id.size();++j)
            {
                int id =m_id.at(j);
                if(ls_res.count(cur_freq)>0 &&ls_res[cur_freq].count(id)>0)
                {
                    QString ls_s = ls_res[cur_freq][id];
                    double magn = getMagn(ls_s);
                    double phase = getPhase(ls_s);
                    if(phase > 180)
                        phase -= 360;
                    else if(phase < -180)
                        phase += 360;
                    p_org[type][key][id] = std::pair<QString,QString>(QString::number(magn,'f'),QString::number(phase,'f'));
                }
            }
        }
    }

    if(type == TYPE_CFG || type == TYPE_MP_1)
    {
        Task_Cmp ls_cmp;
        if(type == TYPE_CFG)
            ls_cmp = tData.t_cfg_magnphase;
        if(type == TYPE_MP_1)
            ls_cmp = tData.t_cfg_mp_1;

        for(size_t i =0; i< m_freq.size(); ++i)
        {
            QString cur_freq = m_freq.at(i);
            QString key ;
            CVTS::DoubleFre_TO_QStringFreq::Double_TO_QString(cur_freq.toDouble(),key);
            for(size_t j =0;j<m_id.size();++j)
            {
                int id = m_id.at(j);
                if(ls_cmp.count(cur_freq)>0 &&ls_cmp[cur_freq].count(id)>0)
                {
                    double magn  = ls_cmp[cur_freq][id].first;
                    double phase = ls_cmp[cur_freq][id].second;
                    if(phase > 180)
                        phase -= 360;
                    else if(phase < -180)
                        phase += 360;
                    p_org[type][key][id] = std::pair<QString,QString>(QString::number(magn,'f'),QString::number(phase,'f'));
                }
            }
        }
    }

}

double BackHandle::getMagn(QString pStr)
{
    QStringList list = pStr.split(QRegExp(","));
    if(list.size() != 2)
    {
        return 0;
    }
    return genMagn(list.at(0).toDouble(), list.at(1).toDouble());
}

double BackHandle::getPhase(QString pStr)
{
    QStringList list = pStr.split(QRegExp(","));
    if(list.size() != 2)
    {
        return 0;
    }
    return genPhase(list.at(0).toDouble(), list.at(1).toDouble());
}

double BackHandle::genMagn(double real, double imag)
{
    // return 10 * log10((real * real + imag * imag)/50) + 30;
    return sqrt(real*real + imag*imag);
}

double BackHandle::genPhase(double real, double imag)
{
    return qAtan2(imag, real) / M_PI * 180;
}


void BackHandle::clean()
{
    m_id.clear();
    m_freq.clear();
    m_radars.clear();
    m_cfg_mp_data.clear();
    m_cfg_m_mp_data.clear();
    m_final_cfg.clear();
    m_org_data.t_cfg_magnphase.clear();
    m_org_data.t_cfg_mp_1.clear();

    m_org_data.t_task_s21.clear();

    m_org_data.t_task_s11_open.clear();
    m_org_data.t_task_s22_open.clear();
    m_org_data.t_task_s11_close.clear();
    m_org_data.t_task_s22_close.clear();

    m_org.clear();
    m_cfg_mp.clear();
    m_cfg_m_mp.clear();
    m_cfg_final.clear();
}
