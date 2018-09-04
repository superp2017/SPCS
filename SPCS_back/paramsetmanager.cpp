#include "paramsetmanager.h"
#include "m_setpnadlg.h"
#include "m_selectgallerydlg.h"
#include "m_dampingdlg.h"
#include "m_setfreqdlg.h"
#include "m_testinitdlg.h"
#include "radarface.h"
#include "statusoutput.h"
#include "projectmanager.h"
#include "eleswitch.h"
#include "m_set_times.h"
#include "m_setdev.h"
#include "m_setpulse.h"


ParamSetManager::ParamSetManager(QObject *parent) :
    QObject(parent)
{

}

ParamSetManager::~ParamSetManager()
{
}


void ParamSetManager::Save(QString path)
{
    fill_param();
    QSettings settings(path,QSettings::IniFormat);
    settings.beginGroup("PROJECT");
    ////工程名字
    settings.setValue("proj_name",m_param.t_proj_name);
    settings.setValue("cfg_table",m_param.t_init_cfg_table);
    ////测试类型
    QString testtype;
    if(m_param.t_test_type == FILED_MAGN)
        testtype = "FILED_MAGN";
    else if(FILED_PHASE)
        testtype = "FILED_PHASE";
    else if(FILED_MAGN_PHASE)
        testtype = "FILED_MAGN_PHASE";
    else if(CONFIG_PHASE)
        testtype = "CONFIG_PHASE";
    else
        testtype = "TYPE_NONE";
    settings.setValue("test_type",testtype);
    ////工作状态
    QString status;
    if(m_param.t_status == SEND)
        status = "SEND";
    else
        status = "RECEIVE";
    settings.setValue("worke_status",status);
    settings.endGroup();

    settings.beginGroup("HDA");
    ////工作频率
    QString freq;
    for(size_t i=0;i<m_param.t_fre_pts.size();++i)
    {
        freq += m_param.t_fre_pts.at(i);
        if(i != m_param.t_fre_pts.size()-1)
            freq += ",";
    }
    settings.setValue("freq",freq);

    ////频率个数
    settings.setValue("freq_iter",m_param.t_fre_iter);
    ////数据采集模式
    QString sweeptype;
    if(m_param.t_sweep_type == SINGLE_POINT)
        sweeptype = "SINGLE_POINT";
    else
        sweeptype = "CONTINUOUS_POINT";

    ////扫描模式
    settings.setValue("sweep_type",sweeptype);
    ////中频带宽
    settings.setValue("bandwidth",m_param.t_bandwidth);
    ////电压dB值
    settings.setValue("power",m_param.t_power);
    ////衰减量
    settings.setValue("attenua",m_param.t_attenua);
    settings.endGroup();


    settings.beginGroup("TEST_TIME");
    ///扫描架稳定时间
    settings.setValue("sweepshelf_times",m_param.t_test_time.t_sweepshelf_times);
    ///波控稳定稳定时间
    settings.setValue("wavec_times",m_param.t_test_time.t_wavec_times);
    ///波控稳定稳定时间
    settings.setValue("multiswitch_times",m_param.t_test_time.t_multiswitch_times);
    ///波控稳定稳定时间
    settings.setValue("elecswitch_times",m_param.t_test_time.t_elecswitch_times);
    ///配相次数
    settings.setValue("CFG_MP",m_param.t_test_time.t_cfg_mp_times);
    settings.setValue("CFG_M_MP",m_param.t_test_time.t_cfg_m_mp_times);
    settings.setValue("DELT_BASE_DB",m_param.t_test_time.t_base_delt_db);

    settings.endGroup();

    /////////////////////////////////////
    ////脉冲测试参数
    ///
    settings.beginGroup("PULSE");
    if(m_param.t_SetPulse.t_enable)
        settings.setValue("enable",1);
    else
        settings.setValue("enable",0);
    settings.setValue("period",m_param.t_SetPulse.t_period);
    ///path0
    if(m_param.t_SetPulse.t_path0_enable)
        settings.setValue("path0_enable",1);
    else
        settings.setValue("path0_enable",0);
    settings.setValue("path0_wid",m_param.t_SetPulse.t_path0_wid);
    settings.setValue("path0_de",m_param.t_SetPulse.t_path0_de);
    ///path1
    if(m_param.t_SetPulse.t_path1_enable)
        settings.setValue("path1_enable",1);
    else
        settings.setValue("path1_enable",0);
    settings.setValue("path1_wid",m_param.t_SetPulse.t_path1_wid);
    settings.setValue("path1_de",m_param.t_SetPulse.t_path1_de);
    ///path2
    if(m_param.t_SetPulse.t_path2_enable)
        settings.setValue("path2_enable",1);
    else
        settings.setValue("path2_enable",0);
    settings.setValue("path2_wid",m_param.t_SetPulse.t_path2_wid);
    settings.setValue("path2_de",m_param.t_SetPulse.t_path2_de);
    ///path3
    if(m_param.t_SetPulse.t_path3_enable)
        settings.setValue("path3_enable",1);
    else
        settings.setValue("path3_enable",0);
    settings.setValue("path3_wid",m_param.t_SetPulse.t_path3_wid);
    settings.setValue("path3_de",m_param.t_SetPulse.t_path3_de);
    ///path4
    if(m_param.t_SetPulse.t_path4_enable)
        settings.setValue("path4_enable",1);
    else
        settings.setValue("path4_enable",0);
    settings.setValue("path4_wid",m_param.t_SetPulse.t_path4_wid);
    settings.setValue("path4_de",m_param.t_SetPulse.t_path4_de);
    settings.endGroup();

}

void ParamSetManager::Read(QString p_path, Param_sets &set)
{

    QSettings settings(p_path,QSettings::IniFormat);
    settings.beginGroup("PROJECT");
    ////工程名字
    set.t_proj_name           =  settings.value("proj_name").toString();
    set.t_init_cfg_table      =  settings.value("cfg_table").toString();
    qDebug()<<set.t_proj_name;
    ////测试类型
    QString testtype         = settings.value("test_type").toString();

    if(testtype == "FILED_MAGN" )
        set.t_test_type = FILED_MAGN;
    else if(testtype == "FILED_PHASE")
        set.t_test_type = FILED_PHASE;
    else if(testtype == "FILED_MAGN_PHASE")
        set.t_test_type = FILED_MAGN_PHASE;
    else if(testtype == "CONFIG_PHASE")
        set.t_test_type = CONFIG_PHASE;
    else
        set.t_test_type = TYPE_NONE;
    ////系统工作状态
    QString status           = settings.value("worke_status").toString();
    if(status == "SEND")
        set.t_status = SEND;
    else
        set.t_status = RECEIVE;

    settings.endGroup();

    settings.beginGroup("HDA");
    ////扫描类型
    QString sweeptype         =  settings.value("sweep_type").toString();
    if(sweeptype == "SINGLE_POINT")
        set.t_sweep_type      =  SINGLE_POINT;
    else if(sweeptype == "CONTINUOUS_POINT")
        set.t_sweep_type      =  CONTINUOUS_POINT;
    ////中频带宽
    set.t_bandwidth           = settings.value("bandwidth").toString();
    ////电压dB值
    set.t_power               = settings.value("power").toString();

    set.t_sweep_times         = settings.value("sweep_times").toString();

    ////系统工作频率
    QString freq             = settings.value("freq").toString();
    QStringList  ls_list3 = freq.split(",");
    for(int i =0;i<ls_list3.size();++i)
    {
        QString f = ls_list3.at(i);
        set.t_fre_pts.push_back(f);
    }
    /////频率个数
    set.t_fre_iter =  settings.value("freq_iter").toString();
    ////衰减量
    set.t_attenua = settings.value("attenua").toString();

    settings.endGroup();

    ///测试时间
    settings.beginGroup("TEST_TIME");

    set.t_test_time.t_wavec_times        = settings.value("wavec_times").toString();
    set.t_test_time.t_multiswitch_times  = settings.value("multiswitch_times").toString();
    set.t_test_time.t_elecswitch_times   = settings.value("elecswitch_times").toString();
    set.t_test_time.t_sweepshelf_times   = settings.value("sweepshelf_times").toString();
    set.t_test_time.t_cfg_mp_times       = settings.value("CFG_MP").toString();
    set.t_test_time.t_cfg_m_mp_times     = settings.value("CFG_M_MP").toString();
    set.t_test_time.t_base_delt_db       = settings.value("DELT_BASE_DB").toString();
    settings.endGroup();


    ////脉冲测试参数
    ///
    settings.beginGroup("PULSE");
    set.t_SetPulse.t_enable       = (bool)(settings.value("enable").toString().toInt() == 1);
    set.t_SetPulse.t_period       =  settings.value("period").toString();
    ////path0
    set.t_SetPulse.t_path0_enable = (bool)(settings.value("path0_enable").toString().toInt() == 1);
    set.t_SetPulse.t_path0_wid    =  settings.value("path0_wid").toString();
    set.t_SetPulse.t_path0_de    =  settings.value("path0_de").toString();
    ////path1
    set.t_SetPulse.t_path1_enable = (bool)(settings.value("path1_enable").toString().toInt() == 1);
    set.t_SetPulse.t_path1_wid    =  settings.value("path1_wid").toString();
    set.t_SetPulse.t_path1_de    =  settings.value("path1_de").toString();
    ////path2
    set.t_SetPulse.t_path2_enable = (bool)(settings.value("path2_enable").toString().toInt() == 1);
    set.t_SetPulse.t_path2_wid    =  settings.value("path2_wid").toString();
    set.t_SetPulse.t_path2_de    =  settings.value("path2_de").toString();
    ////path3
    set.t_SetPulse.t_path3_enable = (bool)(settings.value("path3_enable").toString().toInt() == 1);
    set.t_SetPulse.t_path3_wid    =  settings.value("path3_wid").toString();
    set.t_SetPulse.t_path3_de    =  settings.value("path3_de").toString();
    ////path4
    set.t_SetPulse.t_path4_enable = (bool)(settings.value("path4_enable").toString().toInt() == 1);
    set.t_SetPulse.t_path4_wid    =  settings.value("path4_wid").toString();
    set.t_SetPulse.t_path4_de    =  settings.value("path4_de").toString();

    settings.endGroup();
    /////////////////////
}

void ParamSetManager::Reload(Param_sets &set)
{
    ProjectManager::instance()->set_name(set.t_proj_name);
    M_TestInitDlg::instance()->set_test_type(set.t_test_type);
    M_TestInitDlg::instance()->set_work_status(set.t_status);
    M_TestInitDlg::instance()->set_cfg_table(set.t_init_cfg_table);
    M_SetDev::instance()->set_parame(set.t_bandwidth,set.t_power,set.t_sweep_times,set.t_attenua);
    M_SetFreqdlg::instance()->setfreq(set.t_sweep_type,set.t_fre_pts);

  // M_Set_Times::instance()->reload_param( set.t_test_time.t_wavec_times,\
    //                                      set.t_test_time.t_multiswitch_times,\
    //                                      set.t_test_time.t_elecswitch_times,\
    //                                      set.t_test_time.t_sweepshelf_times,\
    ///////////////////////////////////////////////////
    /////////设置脉冲
    M_SetPulse::instance()->Relad_Parame(set.t_SetPulse.t_enable,set.t_SetPulse.t_period,\
                                         set.t_SetPulse.t_path0_enable,set.t_SetPulse.t_path0_wid,set.t_SetPulse.t_path0_de,\
                                         set.t_SetPulse.t_path1_enable,set.t_SetPulse.t_path1_wid,set.t_SetPulse.t_path1_de,\
                                         set.t_SetPulse.t_path2_enable,set.t_SetPulse.t_path2_wid,set.t_SetPulse.t_path2_de,\
                                         set.t_SetPulse.t_path3_enable,set.t_SetPulse.t_path3_wid,set.t_SetPulse.t_path3_de,\
                                         set.t_SetPulse.t_path4_enable,set.t_SetPulse.t_path4_wid,set.t_SetPulse.t_path4_de);
    /////////////////////////////
}


Param_sets &ParamSetManager::get_Param()
{
    fill_param();
    return m_param;
}

void ParamSetManager::fill_param()
{
    ///////////////////
    //////工程
    m_param.t_proj_name          =  ProjectManager::instance()->get_name();

    M_TestInitDlg::instance()->get_param(m_param.t_test_type,m_param.t_status,m_param.t_init_cfg_table);
    ////////////////////////////
    ////////硬件设置
    M_SetDev::instance()->get_PNA_set(m_param.t_bandwidth,m_param.t_power,m_param.t_sweep_times);
    m_param.t_fre_pts            =  M_SetFreqdlg::instance()->get_freq();
    m_param.t_fre_iter           =  M_SetFreqdlg::instance()->get_freq_step();
    m_param.t_attenua            = QString("%1").arg(M_Dampingdlg::instance()->get_dampling()*10);


    ///////////////////////////////////////////////////////////////////////
    ///测试流程的时间的保存
    QString wave,mule,elec,sweep,cfgmptimes,cfgm_mptimes,base_delt_db;
    M_Set_Times::instance()->get_param(wave,mule,elec,sweep,cfgmptimes,cfgm_mptimes,base_delt_db);
    m_param.t_test_time.t_wavec_times          =  wave;
    m_param.t_test_time.t_multiswitch_times    =  mule;
    m_param.t_test_time.t_elecswitch_times     =  elec;
    m_param.t_test_time.t_sweepshelf_times     =  sweep;
    m_param.t_test_time.t_cfg_mp_times         =  cfgmptimes;
    m_param.t_test_time.t_cfg_m_mp_times       =  cfgm_mptimes;
    m_param.t_test_time.t_base_delt_db         =  base_delt_db;
    /////////////
    //////脉冲参数的保存
    bool enable,pulse0_EN,pulse1_EN,pulse2_EN,pulse3_EN,pulse4_EN;
    QString period,p0_wi,p0_de,p1_wi,p1_de,p2_wi,p2_de,p3_wi,p3_de,p4_wi,p4_de;
    M_SetPulse::instance()->get_param(enable,period,
                                      pulse0_EN,p0_wi,p0_de,\
                                      pulse1_EN,p1_wi,p1_de,\
                                      pulse2_EN,p2_wi,p2_de,\
                                      pulse3_EN,p3_wi,p3_de,\
                                      pulse4_EN,p4_wi,p4_de);
    m_param.t_SetPulse.t_enable       = enable;
    m_param.t_SetPulse.t_period       = period;
    m_param.t_SetPulse.t_path0_enable = pulse0_EN;
    m_param.t_SetPulse.t_path0_wid    = p0_wi;
    m_param.t_SetPulse.t_path0_de     = p0_de;

    m_param.t_SetPulse.t_path1_enable = pulse1_EN;
    m_param.t_SetPulse.t_path1_wid    = p1_wi;
    m_param.t_SetPulse.t_path1_de     = p1_de;

    m_param.t_SetPulse.t_path2_enable = pulse2_EN;
    m_param.t_SetPulse.t_path2_wid    = p2_wi;
    m_param.t_SetPulse.t_path2_de     = p2_de;

    m_param.t_SetPulse.t_path3_enable = pulse3_EN;
    m_param.t_SetPulse.t_path3_wid    = p3_wi;
    m_param.t_SetPulse.t_path3_de     = p3_de;

    m_param.t_SetPulse.t_path4_enable = pulse4_EN;
    m_param.t_SetPulse.t_path4_wid    = p4_wi;
    m_param.t_SetPulse.t_path4_de     = p4_de;
    //////////////////////////////////////////////////////////////////////////
}
