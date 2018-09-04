#include "taskcenter_607.h"
#include "buziwidget.h"
#include "outputview.h"
#include "sweepshelf.h"
#include "vnadapter.h"
#include "teleswitch.h"
#include "tswmatrixs.h"
#include "tmonitor.h"
#include "projectmanager.h"
#include "TAttenuation.h"
#include "BackHandle.h"
#include "twoshorttoid.h"
#include "m_setpulse.h"
#include "trwavecontrol.h"
#include <QDebug>
#include "m_setdev.h"
#include "tarray.h"
#include <complex>
#include <qmath.h>
#include "controlelecswitch.h"
#include "env_config.h"
#include "tmini_1to2.h"



TaskCenter_607::TaskCenter_607(QObject *parent) :
    QObject(parent)
{
    init_data();
}

TaskCenter_607::~TaskCenter_607()
{
}



void TaskCenter_607::init_connect()
{
    connect(this, SIGNAL(push_radar_data(int,double,double,double)), \
            TMonitor::instance(), SLOT(UpdateData(int,double,double,double)),\
            Qt::QueuedConnection);
    connect(this,SIGNAL(EnableReturn(bool)),TMonitor::instance(),SLOT(enableReturn(bool))\
            ,Qt::QueuedConnection);

    connect(this,SIGNAL(appendbuf(const char*)),OutputView::instance(),SIGNAL(append_sig(const char*)),\
            Qt::QueuedConnection);

    connect(this,SIGNAL(appendBuf(QString)),OutputView::instance(),SIGNAL(append_sig(QString)),\
            Qt::QueuedConnection);
    connect(this,SIGNAL(Wave_control(int,double,double,bool,TRontrol*)),\
            TRWaveControl::instance(),SLOT(setMagnPhase_ID(int, double , double, bool,TRontrol*)),\
            Qt::QueuedConnection);
    connect(this,SIGNAL(DOWN_WAVE()),TRWaveControl::instance(),SLOT(DownPower()),\
            Qt::QueuedConnection);
    connect(this,SIGNAL(INIT_WAVE(bool)),TRWaveControl::instance(),SLOT(AntenaInit(bool)),\
            Qt::QueuedConnection);

    connect(this,SIGNAL(SHOWUNIT(int)),TArray::instance(),SLOT(update_radars(int)),\
            Qt::QueuedConnection);
    connect(this,SIGNAL(RESETARRAYFACE()),TArray::instance(),SLOT(resetView()),\
            Qt::QueuedConnection);
}

void TaskCenter_607::dis_connect()
{
    disconnect(this, SIGNAL(push_radar_data(int,double,double,double)), \
               TMonitor::instance(), SLOT(UpdateData(int,double,double,double)));
    disconnect(this,SIGNAL(EnableReturn(bool)),TMonitor::instance(),SLOT(enableReturn(bool)));

    disconnect(this,SIGNAL(appendbuf(const char*)),OutputView::instance(),SIGNAL(append_sig(const char*)));

    disconnect(this,SIGNAL(appendBuf(QString)),OutputView::instance(),SIGNAL(append_sig(QString)));
    disconnect(this,SIGNAL(Wave_control(int,double,double,bool,TRontrol*)),\
               TRWaveControl::instance(),SLOT(setMagnPhase_ID(int, double , double, bool,TRontrol*)));

    disconnect(this,SIGNAL(DOWN_WAVE()),TRWaveControl::instance(),SLOT(DownPower()));
    disconnect(this,SIGNAL(INIT_WAVE(bool)),TRWaveControl::instance(),SLOT(AntenaInit(bool)));

    disconnect(this,SIGNAL(SHOWUNIT(int)),TArray::instance(),SLOT(update_radars(int)));
    disconnect(this,SIGNAL(RESETARRAYFACE()),TArray::instance(),SLOT(resetView()));
}

void TaskCenter_607::init_data()
{
    m_sweepshelf_time = 100 ;
    m_elesw_time      = 500;
    m_multisw_time    = 100;
    m_wave_time       = 50;
    m_pnacollect_time = 20;

    m_test_type       = FILED_MAGN_PHASE;
    m_work_status     = SEND;
    m_cfg_mp_times    =  0;
    m_cfg_m_mp_times  =  0;

    m_isstop          = false;

    m_iscontinus_test = true;
    m_isshow =          false;
    m_status_continus = false;

    m_base_delt_db = 0.5;
}

void TaskCenter_607::init_cfg_table(QString path)
{
    m_temp_cal_data.clear();
    m_temp_cal_data = m_DataManage.ReadFromFile_cmp(path);
}

void TaskCenter_607::init_freq(std::vector<QString> &p_freqs)
{
    m_freqs = p_freqs;
}

//////////////
/// \brief TaskCenter_607::init_map
/// \param map_file
/// \return
/// 初始化映射文件
bool TaskCenter_607::init_map(const QString &map_file)
{
    init_connect();
    clear_buf();

    QFile file(map_file);
    if(!file.exists())
    {
        qDebug()<<map_file<<"not exist!";
        return false;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    if(!file.atEnd())
    {
        QByteArray line = file.readLine().trimmed();
        QStringList list = QString(line).split(QRegExp(QChar(' ')));
        if(list.size() < 7) return false;
        m_task_global.min_d = list.at(0).toInt();
        m_task_global.max_d = list.at(1).toInt();
        m_task_global.min_p = list.at(2).toInt();
        m_task_global.max_p = list.at(3).toInt();
        m_task_global.count = list.at(4).toInt();
        m_map_width = list.at(5).toInt();
        m_map_height = list.at(6).toInt();
        m_task_global.map_vec.clear();
    }

    std::set<int> ls_P;
    std::set<int> ls_D;
    while (!file.atEnd()) {
        QByteArray line = file.readLine().trimmed();
        QStringList list = QString(line).split(QRegExp(QChar(',')));
        if(list.size() != 2) return false ;
        QStringList list_first = list.at(0).trimmed().split(QRegExp(QChar(' ')));
        if(list_first.size() != 3) return  false;
        int ls_first  = list_first.at(0).toInt();
        int ls_second = list_first.at(1).toInt();
        ls_P.insert(ls_first);
        ls_D.insert(ls_second);
        m_PD[ls_first].push_back(ls_second);
        std::pair<int,int> ls_pair_location(ls_first,ls_second);
        QStringList list_second = list.at(1).trimmed().split(QRegExp(QChar(' ')));
        if(list_second.size() % 4 != 0) return  false;
        int n = list_second.size() / 4;
        CVTS::SPoint spt;
        for(int i=0; i<n; i++)
        {
            int T = list_second.at(4 * i + 0).toInt();
            m_ID.push_back(T);
            m_task_map[ls_first][ls_second].push_back(T);
            spt.x = list_second.at(4 * i + 1).toDouble();
            spt.y = list_second.at(4 * i + 2).toDouble();
            spt.z = list_second.at(4 * i + 3).toDouble();
            ///
            ///计算各个点的位置信息
            CVTS::SPoint ls_spt;
            ls_spt.x = list_second.at(4 * i + 1).toDouble();
            ls_spt.y = list_second.at(4 * i + 2).toDouble();
            ls_spt.z = list_second.at(4 * i + 3).toDouble();
            std::pair<CVTS::SPoint,std::pair<int,int> >  ls_pair_info(ls_spt,ls_pair_location);
            m_radars_location[T] = ls_pair_info;

            Radar *r = new Radar(T, spt);
            r->setZValue(5);
            r->turn_on_forever();
            m_radars[T] = r;
        }
    }

    std::set<int>::iterator iter = ls_P.begin();
    while(iter != ls_P.end())
    {
        m_P.push_back(*iter);
        iter++;
    }
    std::sort(m_P.begin(),  m_P.end());

    std::sort(m_ID.begin(), m_ID.end());

    map_Col_Row_Num();

    m_proj_path = ProjectManager::instance()->get_path();

    m_projfile_path   = m_proj_path \
            +"/"+ ProjectManager::instance()->get_name()+PROJ_Suffix;


    //////加载加权值
    load_delt_mag();
    return true;
}

///////////////
/// \brief TaskCenter_607::init_array
/// \param path
/// \return
/// 初始化阵面文件
bool TaskCenter_607::init_array(QString path)
{
    QFile ls_file(path);
    if(!ls_file.exists()) return false;
    QSettings iniSets(path, QSettings::IniFormat);
    iniSets.beginGroup("COORDINATE");
    QStringList list = iniSets.allKeys();
    QStringList::iterator iter = list.begin();
    if(list.size()==0) return false;
    while(iter != list.end())
    {
        QStringList ls_list = iniSets.value(*iter).toString().split(QRegExp(","));
        if(ls_list.size()==3)
        {
            CVTS::SPoint ls_point;
            ls_point.x = ls_list.at(0).toDouble();
            ls_point.y = ls_list.at(1).toDouble();
            ls_point.z = ls_list.at(2).toDouble();
            m_array_data[iter->toInt()] = ls_point;
        }
        iter++;
    }
    iniSets.endGroup();

    iniSets.beginGroup("OFFSET");

    QString ls_offset;
    ls_offset = iniSets.value("offset").toString();
    QStringList ls_list = ls_offset.split(QRegExp(","));
    if(ls_list.size() == 0)
    {
        m_arrar_offset.x = ls_list.at(0).toDouble();
        m_arrar_offset.y = ls_list.at(1).toDouble();
        m_arrar_offset.z = ls_list.at(2).toDouble();
    }
    iniSets.endGroup();

    Radar_Location :: iterator iter1 = m_radars_location.begin();
    Radar_Location     ls_location;
    while(iter1 != m_radars_location.end())
    {
        if(m_array_data.count(iter1->first)>0)
        {
            CVTS::SPoint ls_point =   m_array_data[iter1->first];
            ls_location[iter1->first] = std::pair<CVTS::SPoint,std::pair<int,int> >(ls_point,iter1->second.second);
        }
        ++iter1;
    }
    m_radars_location.clear();
    m_radars_location = ls_location;
    return true;
}

/////////////
/// \brief TaskCenter_607::map_Col_Row_Num
/// ID 行列转化
void TaskCenter_607::map_Col_Row_Num()
{
    for(size_t i =0 ;i<m_ID.size();++i)
    {
        int id =  m_ID.at(i);
        short ls_col = 0,ls_row = 0;
        TwoShortToId::instance()->IdToAddr(id,ls_row,ls_col);
        m_RCN[id] = std::pair<short,short>(ls_row,ls_col);
    }
    if(m_RCN.size() >0)
        TRWaveControl::instance()->init_arrayID(m_RCN);
}


//////////////
/// \brief TaskCenter_607::init_times
/// \param sweepshel
/// \param multisw
/// \param elesw
/// \param wave
/// \param collect
/// \param pcfgtimes
/// 初始化各种设备的稳定时间
void TaskCenter_607::init_times(double sweepshel, double multisw, double elesw, \
                                double wave, double collect, int p_cfg_mp_times, \
                                int p_cfg_m_mp_times, double pdelt_base_db, bool isshow)
{
    m_sweepshelf_time = sweepshel ;
    m_elesw_time      = elesw;
    m_multisw_time    = multisw;
    m_wave_time       = wave;
    m_pnacollect_time = collect;
    m_cfg_mp_times    = p_cfg_mp_times;
    m_cfg_m_mp_times  = p_cfg_m_mp_times;
    m_base_delt_db    = pdelt_base_db;
    QString path      = m_proj_path;
    m_isshow          = isshow;
    for(int i =0;i<m_cfg_mp_times;++i)
    {
        path = m_proj_path + CFG_MP_PATH + QString("/%1").arg(i+1);
        QDir ls_dirpath(path);
        if(!ls_dirpath.exists())
        {
            ls_dirpath.mkpath(path);
        }
    }
    for(int i =0;i<p_cfg_m_mp_times;++i)
    {
        path =  m_proj_path + CFG_M_MP_PATH + QString("/%1").arg(i+1);
        QDir ls_dirpath(path);
        if(!ls_dirpath.exists())
        {
            ls_dirpath.mkpath(path);
        }
    }
    m_is_collect_s11 =  ENV_config::instance()->collect_s11();
    m_is_real_Cal    =  ENV_config::instance()->real_cal();
}

////////////
/// \brief TaskCenter_607::init_test_type
/// \param type
/// \param status
/// \param up
/// \param down
/// 初始化测试类型和工作状态
void TaskCenter_607::init_test_type(TEST_TYPE &type,WORK_STATUS &status)
{
    m_test_type = type;
    m_work_status = status;

}



//////////////
/// \brief TaskCenter_607::begin_test
///主测试流程,先测试初态,然后幅度相位一起，然后幅相分开配
void TaskCenter_607::begin_test()
{
    qDebug()<<"begin_test";
    m_isstop = false;

    //////////////初始化矢网和波控
    if(!test_init())
    {
        qDebug()<<"test_init failed!";
        return;
    }
    qDebug()<<"test_init";

    //////////创建缓冲
    Creat_Buffer(m_task_org_data,m_cfgMP_data,m_cfgM_MP_data, m_cfg_mp_times,m_cfg_m_mp_times);
    qDebug()<<"Creat_Buffer";

    ///加载校准S22和S21
    load_cal_s21(QApplication::applicationDirPath());
    qDebug()<<"load_cal_s21";
    ////////////////
    if(check_status()) return;
    qDebug()<<"check_status";
    ///////初态数据采集
    if(!ORG_TEST())
    {
        test_end_ALL();
        return ;
    }
    qDebug()<<"ORG_TEST";
    //////////
    if(check_status()) return;
    qDebug()<<"check_status";
    ////////配相测试
    if(m_test_type == CONFIG_PHASE)
    {   ////幅度相位一起配
        if(!CFG_MP_TEST())
        {
            test_end_ALL();
            return ;
        }
        qDebug()<<"CFG_MP_TEST";
        if(check_status()) return;
        qDebug()<<"check_status";
        ///先配幅度再幅相一起配
        if(!CFG_M_MP_TEST())
        {
            test_end_ALL();
            return ;
        }
        qDebug()<<"CFG_M_MP_TEST";
        if(check_status()) return;
    }
    SAVE_FINAL_CAL(true,"");
    qDebug()<<"SAVE_FINAL_CAL";
    test_end_ALL();
    qDebug()<<"test_end_ALL";
    emit  Handledata();
}

////////////
/// \brief TaskCenter_607::ORG_TEST
/// \return
///初态测试
bool TaskCenter_607::ORG_TEST()
{
    if(m_temp_cal_data.size()>0)
    {
        if(!ROW_TEST(m_task_org_data,&m_temp_cal_data))
            return false;
    }else
    {
        if(!ROW_TEST(m_task_org_data,NULL))
            return false;
    }
    QString  path = m_proj_path + ORG_PATH;
    SAVE_ORG_DATA(m_task_org_data,m_freqs,path);
    CALC_CFG(m_task_org_data,true);
    SAVE_CAL_DATA(m_task_org_data,m_freqs,m_ID,path);
    m_temp_cal_data = m_task_org_data.t_cfg_magnphase;
    SAVE_FINAL_CAL(false,"org");
    SAVE_RealCal_Data(path);

    return true;
}

////////////
/// \brief TaskCenter_607::CFG_MP_TEST
/// \return
///幅度相位一起配
bool TaskCenter_607::CFG_MP_TEST()
{
    for(int i = 0;i<m_cfg_mp_times;++i)
    {
        if(!m_iscontinus_test) return true;
        if(m_cfgMP_data.count(i) >0)
        {
            if(!ROW_TEST(m_cfgMP_data[i],&m_temp_cal_data))
                return false;
            QString  path = m_proj_path + CFG_MP_PATH + QString("/%1").arg(i+1);
            SAVE_ORG_DATA(m_cfgMP_data[i],m_freqs,path);
            CALC_CFG(m_cfgMP_data[i]);
            if(check_success(m_cfgMP_data[i].t_cfg_magnphase))
            {
                SAVE_CAL_DATA(m_cfgMP_data[i],m_freqs,m_ID,path);
                end_test();
                return true;
            }
            bool isphase = true;
            bool ismagn  = true;
            if( i == m_cfg_mp_times-1)
            {
                if(m_cfg_m_mp_times > 0)
                {
                    isphase = false;
                    ismagn  = true;
                }else
                {
                    isphase = false;
                    ismagn  = false;
                }
            }
            combine_cal_data(m_temp_cal_data,m_cfgMP_data[i].t_cfg_magnphase,ismagn,isphase);
            SAVE_CAL_DATA(m_cfgMP_data[i],m_freqs,m_ID,path);
            QString ty = QString("MP%1").arg(i);
            SAVE_FINAL_CAL(false,ty);
            SAVE_RealCal_Data(path);
        }
    }
    return true;
}

///////////
/// \brief TaskCenter_607::CFG_M_MP_TEST
/// \return
///幅度相位分开配
bool TaskCenter_607::CFG_M_MP_TEST()
{
    for(int i = 0;i<m_cfg_m_mp_times *2;++i)
    {
        if(!m_iscontinus_test) return true;
        if(m_cfgM_MP_data.count(i) >0)
        {
            if(!ROW_TEST(m_cfgM_MP_data[i],&m_temp_cal_data))
                return false;
            QString  path = m_proj_path + CFG_M_MP_PATH + QString("/%1").arg(i/2+1);
            SAVE_ORG_DATA(m_cfgM_MP_data[i],m_freqs,path);
            CALC_CFG(m_cfgM_MP_data[i]);
            if(check_success(m_cfgM_MP_data[i].t_cfg_magnphase))
            {
                SAVE_CAL_DATA(m_cfgM_MP_data[i],m_freqs,m_ID,path);
                end_test();
                return true;
            }

            bool ismagn,isphase;
            if(i%2==0)
            {
                ismagn  = false;
                isphase = true;
            }else
            {
                if(i<(m_cfg_m_mp_times-1)*2)
                {
                    ismagn  = true;
                    isphase = false;
                }else
                {
                    ismagn = true;
                    isphase = true;
                }
            }
            if( i == m_cfg_m_mp_times*2 -1)
            {
                ismagn  =  false;
                isphase =  false;
            }
            combine_cal_data(m_temp_cal_data,m_cfgM_MP_data[i].t_cfg_magnphase,\
                             ismagn,isphase);
            SAVE_CAL_DATA(m_cfgM_MP_data[i],m_freqs,m_ID,path);
            QString ty = QString("M_MP%1").arg(i);
            SAVE_FINAL_CAL(false,ty);
            SAVE_RealCal_Data(path);
        }
    }
    return true;
}


///////
/// \brief TaskCenter_607::combine_cal_data
/// \param p_old_cal_data
/// \param p_cur_cal_data
/// \param ismagn
/// \param isphase
///合并每次的校准数据
void TaskCenter_607::combine_cal_data(Task_Cmp &p_old_cal_data, Task_Cmp &p_cur_cal_data, bool ismagn, bool isphase)
{
    Task_Cmp::iterator iter = p_old_cal_data.begin();
    while(iter != p_old_cal_data.end())
    {
        QString cur_freq = iter->first;
        if(p_cur_cal_data.count(cur_freq))
        {
            std::map<int, std::pair<double, double> >  ls_map = iter->second;
            std::map<int, std::pair<double, double> >::iterator iter2 = ls_map.begin();
            while(iter2 != ls_map.end())
            {
                int id = iter2->first;
                if(p_cur_cal_data[cur_freq].count(id)>0)
                {
                    if(ismagn)
                    {
                        double p_db = transdata(iter2->second.first) +\
                                transdata(p_cur_cal_data[cur_freq][id].first);
                        if(p_db < -31.5)
                        {
                            p_cur_cal_data[cur_freq][id].first =  -31.5 - iter2->second.first;
                            p_old_cal_data[cur_freq][id].first = -31.5;

                        }
                        if(p_db > 0)
                        {
                            p_cur_cal_data[cur_freq][id].first =  0 - iter2->second.first;
                            p_old_cal_data[cur_freq][id].first =  0;

                        }
                        p_old_cal_data[cur_freq][id].first = p_db;
                    }

                    if(isphase)
                    {
                        double phase1 = searchphase(iter2->second.second);
                        double phase2 = searchphase(p_cur_cal_data[cur_freq][id].second);
                        double ls_p =0;
                        if(phase1 < 0)
                            phase1 += 360;
                        if(phase2 <0)
                            phase2 += 360;
                        ls_p = phase1 + phase2;
                        if(ls_p> 360)
                            ls_p = iter2->second.second -(int)(iter2->second.second/360)*360.0;
                        p_old_cal_data[cur_freq][id].second = ls_p;
                    }
                }
                ++iter2;
            }
        }
        ++iter;
    }
}


void TaskCenter_607::TRANS_FINAL_CAL()
{
    for(size_t i=0;i<m_freqs.size();++i)
    {
        QString cur_freq = m_freqs.at(i);
        for(size_t j=0;j<m_ID.size();++j)
        {
            int id = m_ID.at(j);
            if(m_temp_cal_data.count(cur_freq)>0&&m_temp_cal_data[cur_freq].count(id)>0)
            {
                double ls_db    = m_temp_cal_data[cur_freq][id].first;
                double ls_phase = m_temp_cal_data[cur_freq][id].second;
                ls_db    = transdata(ls_db);
                if(ls_db>0)
                    ls_db = 0;
                ls_phase =  searchphase(ls_phase);
                if(ls_phase<0) ls_phase +=360;
                m_temp_cal_data[cur_freq][id] = std::pair<double,double>(ls_db,ls_phase);
            }
        }
    }
}



/////
/// \brief TaskCenter_607::CALC_CFG
/// \param pdata
/// \param isorg
///配相流程
void TaskCenter_607::CALC_CFG(TDATA &pdata, bool isorg)
{
    /*!
     * \brief calc_s22
     * 计算补偿的S21
     *  20140703
     */
    calc_s22();

    if(isorg)
    {
        pdata.t_cfg_magnphase = m_config.PhaseCalibration(m_ID,\
                                                          pdata.t_task_s21,\
                                                          m_radars_location,\
                                                          m_arrar_offset,\
                                                          m_delt_mag, \
                                                          m_cal_s21,\
                                                          m_cal_freq_key,NULL, \
                                                          m_base_delt_db);


        m_base_mp = m_config.get_cur_base_mp();
        if(m_isshow)
        {
            emit SHOW_CAL_STATUS();
            while(!m_status_continus)
                ::Sleep(1000);
        }

    }else
        pdata.t_cfg_magnphase = m_config.PhaseCalibration(m_ID,\
                                                          pdata.t_task_s21,\
                                                          m_radars_location,\
                                                          m_arrar_offset,\
                                                          m_delt_mag,m_cal_s21,\
                                                          m_cal_freq_key,\
                                                          &m_base_mp, \
                                                          m_base_delt_db);
    pdata.t_cfg_mp_1 = m_config.get_cfg_mp_1();

}


////////////
/// \brief TaskCenter_607::Creat_Buffer
/// \param pcfg_mp_times
/// \param pcfg_m_mp_times
///创建BUF
void TaskCenter_607::Creat_Buffer(TDATA &p_org_data,\
                                  std::map<int,TDATA> &p_cfg_mp_Data,\
                                  std::map<int,TDATA> &p_cfg_m_p_data,\
                                  int pcfg_mp_times,int pcfg_m_mp_times)
{
    {
        QString ptype = PS11;
        p_org_data.t_s11_Fname   =  gen_fileName(0,ptype,0);
        ptype = PS21;
        p_org_data.t_s21_Fname   =  gen_fileName(0,ptype,0);
        ptype = PS22;
        p_org_data.t_s22_Fname   =  gen_fileName(0,ptype,0);
        ptype = CFG_CAL;
        p_org_data.t_mp_Fname    =  gen_fileName(0,ptype,0);
        ptype = CFG_CAL_1;
        p_org_data.t_mp_1_Fname  =  gen_fileName(0,ptype,0);
        ptype = CFG_EXCLE;
        p_org_data.t_excle_Fname =  gen_fileName(0,ptype,0);
    }

    for(int i =0;i< pcfg_mp_times;++i)
    {
        TDATA ls_data;
        QString type = PS11;
        ls_data.t_s11_Fname  =  gen_fileName(i,type,1);
        type = PS21;
        ls_data.t_s21_Fname  =  gen_fileName(i,type,1);
        type = PS22;
        ls_data.t_s22_Fname  =  gen_fileName(i,type,1);
        type = CFG_CAL;
        ls_data.t_mp_Fname   =   gen_fileName(i,type,1);
        type = CFG_CAL_1;
        ls_data.t_mp_1_Fname = gen_fileName(i,type,1);
        type = CFG_EXCLE;
        ls_data.t_excle_Fname= gen_fileName(i,type,1);

        p_cfg_mp_Data[i] = ls_data;
    }

    for(int i =0;i<pcfg_m_mp_times *2;++i)
    {
        TDATA ls_data;
        int index = 1;
        if(i%2 == 0)
            index = 2;
        else
            index = 1;
        QString type = PS11;
        ls_data.t_s11_Fname  =  gen_fileName(i,type,index);
        type = PS21;
        ls_data.t_s21_Fname  =  gen_fileName(i,type,index);
        type = PS22;
        ls_data.t_s22_Fname  =  gen_fileName(i,type,index);
        type = CFG_CAL;
        ls_data.t_mp_Fname   =  gen_fileName(i,type,index);
        type = CFG_CAL_1;
        ls_data.t_mp_1_Fname =  gen_fileName(i,type,index);
        type = CFG_EXCLE;
        ls_data.t_excle_Fname=  gen_fileName(i,type,index);

        p_cfg_m_p_data[i] = ls_data;
    }
}


///////
/// \brief TaskCenter_607::stop_test
///强制停止
void TaskCenter_607::stop_test()
{
    m_isstop = true;
}

////////
/// \brief TaskCenter_607::end_test
///提前收敛，停止测试
void TaskCenter_607::end_test()
{
    m_iscontinus_test = false;
}

/////////
/// \brief TaskCenter_607::load_delt_mag
///加载幅度的加权值
void TaskCenter_607::load_delt_mag()
{
    QString path  =  QApplication::applicationDirPath() + DELTMAG_PATH;
    QFile file(path);
    if(!file.exists()){
        qDebug() << "File " << path << " no exist!";
        return ;
    }
    if(!file.open(QFile::ReadOnly | QIODevice::Text)) {
        qDebug()<< path << "open failed!";

    }
    while(!file.atEnd())
    {
        QString line = file.readLine();
        line = line.trimmed();
        if(line.isEmpty()){
            continue;
        }
        QStringList ls_list  =  line.split(QRegExp("\\t+"));
        if(ls_list.size() != 3)
        {
            ls_list  =  line.split(QRegExp("\\s+"));
            if(ls_list.size() != 3)
                continue;
        }
        short row = ls_list.at(0).toShort();
        short col = ls_list.at(1).toShort();
        double db = ls_list.at(2).toDouble();
        int id = gen_ID(row,col);
        m_delt_mag[id] = db;
    }
}



////////////////
/// \brief TaskCenter_607::test_init
/// 测试准备 矢网和波控的初始化
bool TaskCenter_607::test_init()
{
    emit EnableReturn(false);

    if(!TRWaveControl::instance()->udpConnectTest())
    {
        qDebug()<<"WAVE_CONNECT_FAILED";
        emit EnableReturn(true);
        emit WAVE_CONNECT_FAILED();
        return  false;
    }

    if(!vna_init()) {
        qDebug()<<" VNA Connect failed, test stop!";
        emit VNA_CONNECT_FAILED();
        emit EnableReturn(true);
        return  false;
    }
    if(!SweepShelf::instance()->Open_DEV("COM4"))
    {
        emit Serialport_connect_failed();
        emit EnableReturn(true);
        qDebug()<<" Open serialport  COM4 failed!";
        return false;
    }
    ///////////默认初始化为接受状态
    emit INIT_WAVE(false);
    return true;
}



///////////
/// \brief TaskCenter_607::load_cal_s21
/// \param p_path
/// \param iscaldelt
///加载校准库的文件
void TaskCenter_607::load_cal_s21(QString p_path)
{
    QString filename = QString("/Calibration/CUR/match_port");
    m_parse.load_cal_data(p_path,filename);
    if(m_work_status == SEND)
        m_file_cal_S21= m_parse.get_cal_s21();
    else
        m_file_cal_S21= m_parse.get_cal_s12();

}

/*!
 * \brief TaskCenter_607::calc_s22
 * 将实时测试到的S22进行计算,再于校准库里面的进行叠加
 */
void TaskCenter_607::calc_s22()
{
    m_cal_s21.clear();
    if(m_is_real_Cal)
    {
        for(size_t i=0; i<m_P.size(); i++)
        {
            int pos = m_P.at(i);
            std::vector<int> ls_D = m_PD[pos];

            if(m_cal_new_s22_status_2.count(pos)>0 && m_cal_new_s22_status_1.count(pos) >0)
            {
                for(size_t j =0;j<ls_D.size();++j)
                {
                    int dec = ls_D.at(j);
                    if(m_cal_new_s22_status_2[pos].count(dec)>0 && m_cal_new_s22_status_1[pos].count(dec) >0&&\
                            m_cal_temp_s22_status_2.count(dec)>0&& m_cal_temp_s22_status_1.count(dec)>0)
                    {
                        for(size_t k =0;k<m_freqs.size();++k)
                        {
                            QString cur_freq = m_freqs.at(k);
                            if(m_cal_new_s22_status_2[pos][dec].count(cur_freq)>0 &&
                                    m_cal_new_s22_status_1[pos][dec].count(cur_freq) >0&&\
                                    m_cal_temp_s22_status_2[dec].count(cur_freq)>0&&\
                                    m_cal_temp_s22_status_1[dec].count(cur_freq)>0)
                            {

                                double old_magn  = qSqrt(m_cal_temp_s22_status_1[dec][cur_freq].first\
                                                         /m_cal_temp_s22_status_2[dec][cur_freq].first);
                                double old_phase = (m_cal_temp_s22_status_1[dec][cur_freq].second\
                                                    - m_cal_temp_s22_status_2[dec][cur_freq].second)/2;

                                double new_magn  = qSqrt(m_cal_new_s22_status_1[pos][dec][cur_freq].first\
                                                         /m_cal_new_s22_status_2[pos][dec][cur_freq].first);
                                double new_phase =(m_cal_new_s22_status_1[pos][dec][cur_freq].second \
                                                   - m_cal_new_s22_status_2[pos][dec][cur_freq].second)/2;

                                double delt_magn = new_magn/old_magn;
                                double delt_phase= new_phase - old_phase;

                                if(m_file_cal_S21.count(dec)>0&&m_file_cal_S21[dec].count(cur_freq)>0)
                                {
                                    double ls_magn  = (m_file_cal_S21[dec][cur_freq].first) * delt_magn;
                                    double ls_phase = (m_file_cal_S21[dec][cur_freq].second)+ delt_phase;
                                    m_cal_s21[pos][dec][cur_freq] = std::pair<double,double>(ls_magn,ls_phase);

                                }else
                                {
                                    m_cal_s21[pos][dec][cur_freq] = std::pair<double,double>\
                                            ((m_file_cal_S21[dec][cur_freq].first),\
                                             (m_file_cal_S21[dec][cur_freq].second)) ;
                                }
                            }else
                                m_cal_s21[pos][dec][cur_freq] = std::pair<double,double>\
                                        ((m_file_cal_S21[dec][cur_freq].first),\
                                         (m_file_cal_S21[dec][cur_freq].second)) ;
                        }

                    }
                }
            }
        }
    }else
    {
        for(size_t i=0; i<m_P.size(); i++)
        {
            int pos = m_P.at(i);
            std::vector<int> ls_D = m_PD[pos];

            for(size_t j =0;j<ls_D.size();++j)
            {
                int dec = ls_D.at(j);
                for(size_t k=0;k<m_freqs.size();++k)
                {
                    QString cur_freq = m_freqs.at(k);
                    if(m_file_cal_S21.count(dec)>0 && m_file_cal_S21[dec].count(cur_freq)>0)
                    {
                        m_cal_s21[pos][dec][cur_freq] = m_file_cal_S21[dec][cur_freq];
                    }
                }
            }
        }
    }
}



///////////////
/// \brief TaskCenter_607::vna_init
/// \return
/// 矢网的最初设置
bool TaskCenter_607::vna_init()
{
    if(!VNAdapter::instance()->connect()) return false;

    VNAdapter::instance()->reset();

    VNAdapter::instance()->set_S21_TRACE(m_work_status == SEND);

    VNAdapter::instance()->set_trace_S11();

    VNAdapter::instance()->set_trace_S22();

    VNAdapter::instance()->set_freq(m_freqs.at(0).toDouble(),m_freqs.at(m_freqs.size()-1).toDouble(),m_freqs.size());

    ////设置脉冲
    M_SetPulse::instance()->dosetting();
    VNAdapter::instance()->continue_triger();

    QString if_band   = "1000";
    QString power     = "15";
    QString sweeptime = "15";

    M_SetDev::instance()->get_PNA_set(if_band,power,sweeptime);
    VNAdapter::instance()->set_IF_bandwidth(if_band.toDouble());
    VNAdapter::instance()->set_power(power.toDouble());

    return true;
}

///////////
/// \brief TaskCenter_607::vna_close
//////关闭矢网连接
void TaskCenter_607::vna_close()
{
    VNAdapter::instance()->disconnect();
}

//////////
/// \brief TaskCenter_607::ROW_TEST
/// \param Pdata
/// \param pCalData
/// \param isorg
/// \return
///最底层的测试流程
bool TaskCenter_607::ROW_TEST(TDATA &Pdata, Task_Cmp *pCalData)
{
    char buf[1024] = {0};
    ///测试初始化
    if(!testinit_every_time()) return false;
    ::Sleep(100);
    /// if(! SweepShelf::instance()->Isopen()) return false;
    ///切换扫描架
    int freq_size = m_freqs.size();
    if(freq_size == 0 ) return false;
    for(size_t i=0; i<m_P.size(); i++)
    {
        int pos = m_P.at(i);

        CHECK_STOP;

        /// SweepShelf::instance()->MOVE_TO( -pos*SWEEPSHELF_DISTANCE);
        sprintf(buf,"等待扫描架移动..");
        OutputView::instance()->append(buf);

        while(!SweepShelf::instance()->IsMoveDone())
        {
            ::Sleep(500);
        }
        ::Sleep(m_sweepshelf_time);

        sprintf(buf,"移动扫描架至位置 %d",pos);
        OutputView::instance()->append(buf);
        QString note  = CVTS::GBKToUnicode::toUnicode("当前扫描架位置为---->");
        qDebug()<<note<<-pos<<-m_P[i]*SWEEPSHELF_DISTANCE;
        BuziWidget::instance()->scanner_pos_s(-m_P[i]*15.0/13.0);
        std::vector<int> ls_D = m_PD[pos];
        ///切换探头
        for(size_t j=0; j<ls_D.size(); j++)
        {
            int decnum = ls_D.at(j);
            CHECK_STOP;
            //关闭电子开关
            TEleSwitch::instance()->turn_off_all();
            TSWMatrixs::instance()->turn_on(CVTS::Matrix(decnum-1));
            BuziWidget::instance()->muti_switch_s(decnum-1);
            sprintf(buf,"切换探头至%d",decnum);
            OutputView::instance()->append(buf);

            ::Sleep(m_multisw_time);

            BuziWidget::instance()->switch_off_s(16);
            BuziWidget::instance()->switch_off_s(decnum-1);
            BuziWidget::instance()->detector_off_s(decnum-1);

            ///切换单元

            std::vector<int> cur_id_vec =  m_task_map[pos][decnum];

            for(size_t uid =0;uid<cur_id_vec.size();++uid)
            {
                CHECK_STOP;
                //////////////////////////采集S21/////////////////////////////////////////////////////////
                int id = cur_id_vec.at(uid);
                /////显示监控界面上对应的测试阵元
                emit SHOWUNIT(id);
                if(!pCalData)
                {
                    ///打开波控
                    if(initWaveUnit(id))
                    {
                        sprintf(buf,"打开阵元:%d",id);
                        ::Sleep(m_wave_time);
                    }

                    QString s21 =/* QString::number((rand()%200)/190,'f',3)\
                                                    +QString(",")+QString::number((rand()%190)/180,'f',3);*/
                            VNAdapter::instance()->collectSendData(m_work_status == SEND);
                    QStringList list_s21 = s21.split(QRegExp(","));
                    if(list_s21.size() != freq_size*2 ) continue;
                    for(int k = 0; k <freq_size;++k)
                    {
                        CHECK_STOP;
                        QString cur_freq = m_freqs.at(k);
                        QString real = list_s21.at(2*k);
                        QString imag = list_s21.at(2*k+1);
                        QString str_s21 = real +"," + imag;
                        Pdata.t_task_s21[cur_freq][id] =  str_s21;

                        double ls_magn  =  VNAdapter::instance()->genLinMag(real.toDouble(),imag.toDouble());
                        double ls_phase =  VNAdapter::instance()->genPhase(real.toDouble(),imag.toDouble());
                        emit push_radar_data(id, cur_freq.toDouble(),ls_magn,ls_phase);
                    }

                }else
                {
                    ///切换频率
                    for(int f = 0;f<freq_size;++f)
                    {
                        CHECK_STOP;

                        QString cur_freq = m_freqs.at(f);

                        if(m_success_freq.find(cur_freq) != m_success_freq.end() )
                            continue;

                        ///设置失网频率
                        VNAdapter::instance()->set_freq(cur_freq);

                        /// config phase
                        if(CONTROL_WAVE(cur_freq,id,pCalData))
                        {
                            ::Sleep(m_wave_time);
                        }else
                        {
                            qDebug()<<"Config_Phase failed";
                            continue;
                        }
                        /// S21
                        QString s21 = /*QString::number((rand()%200)/190,'f',3)\
                                                        +QString(",")+QString::number((rand()%190)/180,'f',3);*/VNAdapter::instance()->collectSendData(m_work_status == SEND);
                        QStringList list_s21_cfg = s21.split(QRegExp(","));
                        if(list_s21_cfg.size() != 2 || (list_s21_cfg.at(0).toDouble() ==0 && list_s21_cfg.at(1).toDouble()==0) )
                        {
                            ::Sleep(10);
                            s21 = VNAdapter::instance()->collectSendData(m_work_status == SEND);
                            list_s21_cfg = s21.split(QRegExp(","));
                        }
                        if(list_s21_cfg.size() == 2)
                        {
                            Pdata.t_task_s21[cur_freq][id] = s21;

                            double ls_magn  =  VNAdapter::instance()->genLinMag(list_s21_cfg.at(0).toDouble(),list_s21_cfg.at(1).toDouble());
                            double ls_phase =  VNAdapter::instance()->genPhase(list_s21_cfg.at(0).toDouble(),list_s21_cfg.at(1).toDouble());
                            emit push_radar_data(id, cur_freq.toDouble(),ls_magn,ls_phase);
                        }else
                            qDebug()<<"list_s21 size error";
                        ////////////////////////////////
                    }
                }
                //////////////////////////////////////////////////////////////////////////////////////
            }

            if(pCalData)
            {
                VNAdapter::instance()->set_freq(m_freqs.at(0).toDouble(),m_freqs.at(freq_size-1).toDouble(),freq_size);
            }

            CHECK_STOP;

            ///打开电子开关
            //TEleSwitch::instance()->turn_on(CVTS::CD_1);
            TEleSwitch::instance()->turn_on(CVTS::CVTS_Decetor(decnum-1));
            BuziWidget::instance()->switch_on_s(16);
            BuziWidget::instance()->switch_on_s(decnum-1);
            BuziWidget::instance()->detector_on_s(decnum-1);

            ::Sleep(m_elesw_time);

            ///////////////////////采集S11/////////////////////////////////////////////////////////
            if(m_is_collect_s11)
            {
                ///采集 S11
                QString s11 = QString::number((rand()%200)/190,'f',3)\
                        +QString(",")+QString::number((rand()%190)/180,'f',3);// VNAdapter::instance()->collect_S11();
                QStringList list_s11 = s11.split(QRegExp(","));

                if(list_s11.size() != freq_size*2)
                {
                    s11 = VNAdapter::instance()->collect_S11();
                    list_s11 = s11.split(QRegExp(","));
                }

                if(list_s11.size() == freq_size*2&& list_s11.size() >1 )
                {
                    for(int l = 0; l <freq_size;++l)
                    {
                        ///处理 S11
                        QString cur_freq = m_freqs.at(l);
                        QString real_11 = list_s11.at(2*l);
                        QString imag_11 = list_s11.at(2*l+1);
                        QString str_s11 = real_11 +"," + imag_11;

                        for(size_t uid =0;uid<cur_id_vec.size();++uid)
                        {
                            int id = cur_id_vec.at(uid);
                            CHECK_STOP;
                            Pdata.t_task_s11[cur_freq][id] =  str_s11;
                        }
                    }
                }

            }
            //////////////////////////////////////////////////////////////////////////////////////


            //////////////////////采集 S22 状态1///////////////////////////////////////////////////
            QString s22 = QString::number((rand()%180)/190,'f',3)\
                    +QString(",")+QString::number((rand()%210)/180,'f',3);// VNAdapter::instance()->collect_S22();
            QStringList list_s22 = s22.split(QRegExp(","));

            if(list_s22.size() != freq_size*2)
            {
                s22 = VNAdapter::instance()->collect_S22();
                list_s22 = s22.split(QRegExp(","));
            }

            if(list_s22.size() == freq_size*2 && list_s22.size() >1 )
            {
                for(int l = 0; l <freq_size;++l)
                {
                    QString cur_freq = m_freqs.at(l);
                    ///处理 S22
                    QString real_22 = list_s22.at(2*l);
                    QString imag_22 = list_s22.at(2*l+1);
                    QString str_s22 = real_22 +"," + imag_22;

                    CHECK_STOP;
                    for(size_t uid =0;uid<cur_id_vec.size();++uid)
                    {
                        int id = cur_id_vec.at(uid);
                        Pdata.t_task_s22[cur_freq][id] =  str_s22;
                    }

                    if(m_is_real_Cal)
                    {
                        double pampl  = genLinMag(real_22.toDouble(),imag_22.toDouble());
                        double pphase = genPhase(real_22.toDouble(),imag_22.toDouble());
                        m_cal_new_s22_status_1[pos][decnum][cur_freq] =\
                                std::pair<double,double>(pampl,pphase);
                        if(i == 0)
                        {
                            m_cal_temp_s22_status_1[decnum][cur_freq] =\
                                    std::pair<double,double>(pampl,pphase);
                        }
                    }

                }
            }
            //////////////////////////////////////////////////////////////////////////////////////

            CHECK_STOP;
            if(m_is_real_Cal)
            {
                //////////////////////////////////////////////////////////////////////////////////////
                /////////////开关加电//////////////////////////////////////////////////////////////////
                TMini_1TO2::instance()->turn_on_off(true);
                /////////////采集S22 状态2/////////////////////////////////////////////////////////////

                QString ps22 =QString::number((rand()%210)/190,'f',3)\
                        +QString(",")+QString::number((rand()%190)/190,'f',3);// VNAdapter::instance()->collect_S22();
                ::Sleep(m_pnacollect_time);
                QStringList plist_s22 = ps22.split(QRegExp(","));
                if(plist_s22.size() != freq_size*2)
                {
                    ps22 = VNAdapter::instance()->collect_S22();
                    plist_s22 = ps22.split(QRegExp(","));
                }
                if(plist_s22.size() == freq_size*2 )
                {
                    for(int l = 0; l <freq_size;++l)
                    {
                        CHECK_STOP;

                        QString cur_freq = m_freqs.at(l);
                        ///处理 S22
                        QString real_22 = plist_s22.at(2*l);
                        QString imag_22 = plist_s22.at(2*l+1);
                        double  pampl = genLinMag(real_22.toDouble(),imag_22.toDouble());
                        double pphase = genPhase(real_22.toDouble(),imag_22.toDouble());
                        m_cal_new_s22_status_2[pos][decnum][cur_freq] =\
                                std::pair<double,double>(pampl,pphase);
                        if(i == 0)
                        {
                            m_cal_temp_s22_status_2[decnum][cur_freq] =\
                                    std::pair<double,double>(pampl,pphase);
                        }
                    }
                }
            }

            CHECK_STOP;

            //////关闭当前监控界面上的的开关
            BuziWidget::instance()->switch_off_s(16);
            BuziWidget::instance()->switch_off_s(decnum-1);
        }
    }
    /////保存每次的实时校准的文件
    //本轮测试结束
    test_end_once();
    return true;
}

/////////////
/// \brief TaskCenter_607::initWaveUnit
/// \param id
/// \return
/// 原始测试的时候 打开波控单元 不需要配相
bool TaskCenter_607::initWaveUnit(int id)
{
    emit INIT_WAVE(m_work_status == SEND);
    ::Sleep(2);
    emit Wave_control(id,0,0,m_work_status == SEND,NULL);
    return  true;
}


bool TaskCenter_607::CONTROL_WAVE(QString p_freq,int id,Task_Cmp * p_Cal_data)
{
    double db    = 0;
    double phase = 0;
    if(p_Cal_data)
    {
        if(p_Cal_data->count(p_freq)>0)
        {
            if(p_Cal_data->at(p_freq).count(id)>0)
            {
                db    = p_Cal_data->at(p_freq)[id].first;
                phase = p_Cal_data->at(p_freq)[id].second;

                if(db>0)
                    db = 0;
                if(db<-31.5)
                    db = -31.5;
                if(phase<0)
                    phase += 360;
                if(phase<0)
                    phase =0;
                db = abs(db);
            }

        }
    }
    emit INIT_WAVE(m_work_status == SEND);
    ::Sleep(2);
    if(m_work_status == SEND)
        emit Wave_control(id,0,phase,m_work_status == SEND,NULL);
    else
        emit Wave_control(id,db,phase,m_work_status == SEND,NULL);
    return true;
}


//////////
/// \brief TaskCenter_607::testinit_every_time
/// \param index
/// \return
///每一轮测试前的准备工作
bool TaskCenter_607::testinit_every_time()
{
    char buf1[512] = {0};
    char buf2[512] = {0};
    char buf3[512] = {0};
    char buf4[512] = {0};
    char buf5[512] = {0};


    TEleSwitch::instance()->reset();
    TSWMatrixs::instance()->reset();
    TMini_1TO2::instance()->turn_on_off(false);
    sprintf(buf1,"初始化电子开关.");
    sprintf(buf2,"初始化多路开关.");
    OutputView::instance()->append(buf1);
    OutputView::instance()->append(buf2);

    TAttenuation::instance()->reset();
    int cur = M_Dampingdlg::instance()->get_dampling();
    TAttenuation::instance()->attenuation(CVTS::NI_ANTENNA(cur));
    sprintf(buf3,"初始化衰减器至 %d dB.",cur*10);
    OutputView::instance()->append(buf3);

    SweepShelf::instance()->Open_DEV("COM4");
    SweepShelf::instance()->SetMoveSpeed(SPEED_500_1000);
    SweepShelf::instance()->MOVE_TO_Origin();
    sprintf(buf4,"等待扫描架归位...");
    OutputView::instance()->append(buf4);
    while(! SweepShelf::instance()->IsMoveDone())
    {
        ::Sleep(2000);
    }
    wave_init();


    m_cal_temp_s22_status_2.clear();
    m_cal_temp_s22_status_1.clear();

    return  true;
}


///////////
/// \brief TaskCenter_607::wave_init
/// 初始化波控 使整个阵面待机
void TaskCenter_607::wave_init()
{
    emit INIT_WAVE(m_work_status == SEND);
}



////////////
/// \brief TaskCenter_607::test_end_once
///每一轮测试完 所做的事情
void TaskCenter_607::test_end_once()
{
    QString str = CVTS::GBKToUnicode::toUnicode("本轮测试结束");
    appendBuf(str);
    TAttenuation::instance()->reset();
    TEleSwitch::instance()->reset();
    TSWMatrixs::instance()->reset();
    TRWaveControl::instance()->DownPower();
    emit RESETARRAYFACE();
}


/////////////
/// \brief TaskCenter_607::test_end_ALL
/// 测试结束后工作
void TaskCenter_607::test_end_ALL()
{
    m_success_freq.clear();
    QString str = CVTS::GBKToUnicode::toUnicode("测试结束");
    appendBuf(str);
    donwpower();
    emit EnableReturn(true);
}


////////////
/// \brief TaskCenter_607::donwpower
///各种设备的下电
void TaskCenter_607::donwpower()
{
    TAttenuation::instance()->reset();
    TEleSwitch::instance()->reset();
    TSWMatrixs::instance()->reset();
    TMini_1TO2::instance()->turn_on_off(false);
    TRWaveControl::instance()->DownPower();
    SweepShelf::instance()->MOVE_TO_Origin();
    SweepShelf::instance()->Close_DEV();
    TEleSwitch::instance()->close_dev();
    vna_close();
}


QString TaskCenter_607::gen_fileName(int index, QString type, int typeindex)
{
    QString name;
    if(typeindex ==0)
        name = ORG_MP + QString("_")+ type  + QString("_%1").arg(index);
    if(typeindex == 1)
        name = CFG_MP + QString("_") +type  + QString("_%1").arg(index);
    if(typeindex == 2)
        name = CFG_M + QString("_") + type  + QString("_%1").arg(index);
    return name;
}


/////////
/// \brief TaskCenter_607::SAVE_ORG_DATA
/// \param pdata
/// \param p_freqs
/// \param psave_path
///保存采集的原始文件
void TaskCenter_607::SAVE_ORG_DATA(TDATA &pdata,\
                                   std::vector<QString> &p_freqs\
                                   ,QString psave_path)
{
    if(!pdata.t_task_s11.empty())
    {
        m_DataManage.SaveToFile(pdata.t_task_s11,p_freqs,psave_path + "/"+ pdata.t_s11_Fname + ORG_SUFFIX);
        m_DataManage.SaveToFile_dB(pdata.t_task_s11,p_freqs,psave_path + "/" +  pdata.t_s11_Fname + MP_SUFFIX);
    }
    if(!pdata.t_task_s21.empty())
    {
        m_DataManage.SaveToFile(pdata.t_task_s21,p_freqs,psave_path + "/"+ pdata.t_s21_Fname + ORG_SUFFIX);
        m_DataManage.SaveToFile_dB(pdata.t_task_s21,p_freqs,psave_path + "/" + pdata.t_s21_Fname + MP_SUFFIX);
    }
    if(!pdata.t_task_s22.empty())
    {
        m_DataManage.SaveToFile(pdata.t_task_s22,p_freqs,psave_path + "/"+ pdata.t_s22_Fname + ORG_SUFFIX);
        m_DataManage.SaveToFile_dB(pdata.t_task_s22,p_freqs,psave_path + "/" + pdata.t_s22_Fname + MP_SUFFIX);
    }

}

/////////
/// \brief TaskCenter_607::SAVE_CAL_DATA
/// \param pdata
/// \param p_freqs
/// \param p_id
/// \param psave_path
///保存校准算法后的文件,包括校准文件和中间文件，还有excle文件
void TaskCenter_607::SAVE_CAL_DATA(TDATA &pdata, std::vector<QString> &p_freqs, \
                                   std::vector<int> &p_id, QString psave_path)
{
    if(!pdata.t_cfg_magnphase.empty())
    {
        exportexcle.Export_Excel(psave_path + "/" +  pdata.t_excle_Fname + EXCLE_SUFFIX,\
                                 pdata.t_cfg_magnphase,p_freqs,p_id);

        m_DataManage.SaveToFile(pdata.t_cfg_magnphase,p_freqs, \
                                psave_path +  "/" + pdata.t_mp_Fname   + CAL_MP_SUFFIX );
    }
    if(!pdata.t_cfg_mp_1.empty())
        m_DataManage.SaveToFile(pdata.t_cfg_mp_1,p_freqs, \
                                psave_path + "/" +  pdata.t_mp_1_Fname + CAL_MP_1_SUFFIC) ;
}

void TaskCenter_607::SAVE_RealCal_Data(Task_CAL_S22 &p_cmp,QString path)
{
    if(m_is_real_Cal)
    {
        QFile ls_file(path);
        if(!ls_file.open(QFile::WriteOnly|QFile::Text))
        {
            qDebug()<<path<<"open file!";
            return;
        }
        QTextStream out(&ls_file);

        for(size_t f= 0;f<m_freqs.size();++f)
        {
            QString cur_freq = m_freqs.at(f);
            out<<"Freq:"<<cur_freq<<endl;
            for(size_t i=0; i<m_P.size(); i++)
            {
                int pos = m_P.at(i);
                std::vector<int> ls_D = m_PD[pos];
                if(p_cmp.count(pos)>0)
                {
                    out<<pos<<",";
                    for(size_t j =0;j<ls_D.size();++j)
                    {
                        int dec = ls_D.at(j);
                        if(p_cmp[pos].count(dec)&&\
                                p_cmp[pos][dec].count(cur_freq))
                        {
                            out<<dec\
                              <<","\
                             <<p_cmp[pos][dec][cur_freq].first\
                            <<","\
                            <<p_cmp[pos][dec][cur_freq].second<<endl;
                        }
                    }
                }
            }
        }
    }
}

void TaskCenter_607::SAVE_RealCal_Data(QString ppath)
{
    QString path = ppath +QString("/status1.realcal");
    if(!m_cal_new_s22_status_1.empty())
    {
        SAVE_RealCal_Data(m_cal_new_s22_status_1,path);
    }
    if(!m_cal_new_s22_status_2.empty())
    {
        path = ppath +QString("/status2.realcal");
        SAVE_RealCal_Data(m_cal_new_s22_status_2,path);
    }
}


////////
/// \brief TaskCenter_607::SAVE_FINAL_CAL
/// \param isend
/// \param type
///保存最终的测试校准数据
void TaskCenter_607::SAVE_FINAL_CAL(bool isend,QString type)
{
    if(!m_temp_cal_data.empty())
    {
        QString path ;//
        if(isend)
            path = m_proj_path + DATA_PATH + CALDATA;
        else
            path = m_proj_path + DATA_PATH + CALDATA +"_" + type;

        if(isend)
            TRANS_FINAL_CAL();
        exportexcle.Export_Excel(path + EXCLE_SUFFIX, m_temp_cal_data,m_freqs,m_ID);
        m_DataManage.SaveToFile(m_temp_cal_data,m_freqs, path + CAL_MP_SUFFIX );
    }
}


void TaskCenter_607::update_org_cal(Task_Cmp &pdata)
{
    m_task_org_data.t_cfg_magnphase  = pdata;
}

void TaskCenter_607::BASE_MP(std::map<QString, std::pair<double, double> > &pbase_data)
{
    m_status_continus = true;
    m_base_mp = pbase_data;
}


////////
/// \brief TaskCenter_607::transdata
/// \param valus
/// \return
///转化dB值以0.5db为步进
double TaskCenter_607::transdata(double valus)
{
    double tmp = 0.25;
    if(valus < 0) tmp = -0.25;
    return (((int)((valus+tmp)*100))/50*50)/100.0;
}


/////
/// \brief TaskCenter_607::searchphase
/// \param phase
/// \return
///转化相位值,以5.625为步进
double TaskCenter_607::searchphase(double phase)
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




void TaskCenter_607::reset()
{
    init_data();
    clear_buf();
    dis_connect();
}


///////////
/// \brief TaskCenter_607::check_differ
/// \param curfreq
/// \param freq_key
///频率做差值
void TaskCenter_607::check_differ(QString &curfreq,std::vector<QString> &freq_key)
{
    for(size_t i =0;i<freq_key.size();++i)
    {
        double ls_freq = freq_key.at(i).toDouble();
        double ls_next = freq_key.at(i+1).toDouble();
        double cur = curfreq.toDouble();

        if((i+1)<freq_key.size())
        {
            if(ls_freq<= cur && ls_next >=cur)
            {
                if(ls_freq == cur)
                {
                    curfreq = freq_key.at(i);
                    return;
                }
                if(cur == ls_next)
                {
                    curfreq = freq_key.at(i+1);
                    return;
                }

                if(abs(ls_freq-cur)<abs(ls_next-cur))
                {
                    curfreq = freq_key.at(i);
                    return ;
                }
                else
                {
                    curfreq = freq_key.at(i+1);
                    return ;
                }
            }
        }else
        {
            curfreq = freq_key.at(i);
            return ;
        }
    }
}




/*!
 * \brief TaskFlow::genLinMag
 * \param real
 * \param imag
 * \return
 *实部虚部变为线性幅度
 */
double TaskCenter_607::genLinMag(double real, double imag)
{
    return sqrt(real*real + imag * imag);
}

double TaskCenter_607::genLinMag(QString data)
{
    QStringList str = data.split(QRegExp(","));
    if(str.size()==2)
    {
        return genLinMag(str.at(0).toDouble(),str.at(1).toDouble());
    }else
        return 1;
}


double TaskCenter_607::genPhase(double real, double imag)
{
    return qAtan2(imag, real) / M_PI * 180;
}

double TaskCenter_607::genPhase(QString data)
{
    QStringList str = data.split(QRegExp(","));
    if(str.size()==2)
    {
        return genPhase(str.at(0).toDouble(),str.at(1).toDouble());
    }else
        return 0;
}

double TaskCenter_607::gendB(double real, double imag)
{
    double db = genLinMag(real,imag);
    if(db == 0)
        return 0;
    else
        return 20*log10(db);
}

double TaskCenter_607::gendB(double mag)
{
    if(mag ==0)
        return 0;
    else
        return 20*log10(mag);
}


double TaskCenter_607::gendB(QString data)
{
    QStringList str = data.split(QRegExp(","));
    if(str.size()==2)
    {
        return  gendB(str.at(0).toDouble(),str.at(1).toDouble());
    }else
        return 0;
}

void TaskCenter_607::gen_dBMag_Phase(QString data, double &mag, double &phase)
{
    QStringList str = data.split(QRegExp(","));
    if(str.size()==2)
    {
        mag   = gendB(str.at(0).toDouble(),str.at(1).toDouble());
        phase = genPhase(str.at(0).toDouble(),str.at(1).toDouble());
    }else
    {
        mag   = 0;
        phase = 0;
    }
}

void TaskCenter_607::gen_LinMag_Phase(QString data, double &mag, double &phase)
{
    QStringList str = data.split(QRegExp(","));
    if(str.size()==2)
    {
        mag   = genLinMag(str.at(0).toDouble(),str.at(1).toDouble());
        phase = genPhase(str.at(0).toDouble(),str.at(1).toDouble());
    }else
    {
        mag   = 1;
        phase = 0;
    }
}

void TaskCenter_607::gen_RelImg(QString data, double &mag, double &phase)
{
    QStringList str = data.split(QRegExp(","));
    if(str.size()==2)
    {
        mag   = str.at(0).toDouble();
        phase = str.at(1).toDouble();
    }else
    {
        mag   = 0;
        phase = 0;
    }
}


bool TaskCenter_607::check_status()
{
    if(m_isstop)
    {
        clear_buf();
    }

    return m_isstop ;
}


///////行列转化成ID
int TaskCenter_607::gen_ID(short row, short col)
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


bool TaskCenter_607::check_success(Task_Cmp &p_cal_mp_1)
{
    bool success = true;
    for(size_t i =0;i<m_freqs.size();++i)
    {
        QString cur_freq = m_freqs.at(i);
        if(p_cal_mp_1.count(cur_freq)>0)
        {
            std::map<int, std::pair<double, double> > ls_cal = p_cal_mp_1[cur_freq];
            int db_num = 0;
            int phase_num = 0;
            int size = ls_cal.size();
            for(size_t j =0;j<m_ID.size();++j)
            {
                int id = m_ID.at(j);
                if(ls_cal.count(id)>0)
                {
                    double db    = ls_cal[id].first;
                    double phase = ls_cal[id].second;
                    if(phase>180)
                        phase -= 360;
                    if(db >  0.5 || db < -0.5)
                        db_num++;
                    if(phase > 5.625 || phase < -5.625)
                        phase_num++;
                }
            }
            double db_ray    = (db_num*1.0)/size;
            double phase_ray = (phase_num*1.0)/size;
            qDebug()<<db_ray<<phase_ray;

            //            if(db_ray>0.05 ||  phase_ray > 0.05)
            //            {
            //                success = false;
            //                return success;
            //            }

            if(db_ray<=0.05 && phase_ray <=0.05)
            {
                m_success_freq.insert(cur_freq);
                success &= true;
            }else success &= false;
        }
    }
    if(success)
        qDebug()<<"OKokokokokokokokok ";
    return success;
}


void TaskCenter_607::clear_buf()
{
    m_task_map.clear();
    m_task_global.clear();
    m_radars_location.clear();
    m_temp_cal_data.clear();

    m_radars.clear();
    m_P.clear();
    m_PD.clear();
    m_ID.clear();

    m_RCN.clear();
    m_freqs.clear();

    m_array_data.clear();

    m_cal_s21.clear();
    m_cal_freq_key.clear();
    m_cal_new_s22_status_2.clear();
    m_cal_new_s22_status_1.clear();

    m_cfgMP_data.clear();
    m_cfgM_MP_data.clear();

    m_task_org_data.t_cfg_magnphase.clear();
    m_task_org_data.t_cfg_mp_1.clear();
    m_task_org_data.t_task_s11.clear();
    m_task_org_data.t_task_s21.clear();
    m_task_org_data.t_task_s22.clear();

    m_delt_mag.clear();
    m_base_mp.clear();
    m_success_freq.clear();

}

