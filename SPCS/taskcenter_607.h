#ifndef TASKCENTER_607_H
#define TASKCENTER_607_H

#include <QObject>
#include "radar.h"
#include "projectmanager.h"
#include "datamanage.h"
#include "configphase.h"
#include "trwavecontrol.h"
#include "configerexcel.h"
#include "cparsefile.h"
#include "_global.h"

using namespace CVTS;

class CompareWithFreq
{
public:
    bool operator()(const QString &L_, const QString &R_)
    {
        double ls_R = R_.toDouble();
        double ls_L = L_.toDouble();
        return ls_L < ls_R;
    }
};

#define CHECK_STOP         if(m_isstop){clear_buf();return false;}

/*!
 * \brief The TaskCenter_607 class
 * 总的测试流程类，完成测试最核心的类
 *
 */
class TaskCenter_607 : public QObject
{
    Q_OBJECT
protected:
    explicit TaskCenter_607(QObject *parent = 0);
    ~TaskCenter_607();
public:
    static TaskCenter_607* instance()
    {
        static TaskCenter_607 *s_607  = new TaskCenter_607();
        return s_607;
    }
    static void destroy()
    {
        delete instance();
    }
    int  get_map_width(){return m_map_width;}
    int  get_map_height(){return m_map_height;}
    void init_data();
    void init_cfg_table(QString path);
    void init_freq(std::vector<QString> &p_freqs);
    void init_connect();
    void dis_connect();
    bool init_array(QString path);
    bool init_map(const QString &map_file);
    void init_times(double sweepshel, double multisw, double elesw, \
                    double wave, double collect, \
                    int p_cfg_mp_times, int p_cfg_m_mp_times, \
                    double pdelt_base_db, bool isshow = false);
    void init_test_type(TEST_TYPE &type, WORK_STATUS &status);

    Radar_Location get_radars_location()           {return m_radars_location;}
    std::map<int, Radar *> &get_radars()           {return m_radars;}
    std::vector<int>       &get_id()               {return m_ID;    }
    std::vector<QString>   &get_freqs()            {return m_freqs; }
    Task_CAL_S22           &get_cal_s21()          {return m_cal_s21;}
    std::vector<QString>   &get_cal_freq()         {return m_cal_freq_key;}

    std::map<int,double>   &get_delt_mag()         {return m_delt_mag;}
    TDATA                  &get_org_data()         {return m_task_org_data;}
    std::map<int,TDATA>    &get_cfg_mp_data()      {return m_cfgMP_data;}
    std::map<int,TDATA>    &get_cfg_m_mp_data()    {return m_cfgM_MP_data;}
    Task_Cmp               &get_final_cal_Data()   {return m_temp_cal_data;}
    double                 &get_base_add_db()      {return m_base_delt_db;}
    std::map<QString,std::pair<double,double> >\
    &get_org_base_mp()       {return m_base_mp;}

    void clear_buf();
    void donwpower();
    void reset();
    void check_differ(QString &curfreq, std::vector<QString> &freq_key);
    void load_cal_s21(QString p_path);
    void calc_s22();
    void update_org_cal(Task_Cmp &pdata);
    void BASE_MP(std::map<QString,std::pair<double,double> > &pbase_data);

    void begin_test();
    QString gen_fileName(int index, QString type, int typeindex = true);


    bool ROW_TEST(TDATA &Pdata, Task_Cmp *pCalData);

    bool check_success(Task_Cmp &p_cal_mp_1);

    void Creat_Buffer(TDATA &p_org_data,\
                      std::map<int,TDATA> &p_cfg_mp_Data,\
                      std::map<int,TDATA> &p_cfg_m_p_data,\
                      int pcfg_mp_times,int pcfg_m_mp_times);

    void  CALC_CFG(TDATA & pdata,bool isorg = false);
    void  load_delt_mag();
public slots:
    void  stop_test();
    void  end_test();
protected:
    bool   test_init();
    bool   vna_init();
    void   vna_close();
    void   wave_init();
    bool   testinit_every_time();
    void   test_end_once();
    void   test_end_ALL();
    bool   initWaveUnit(int id);
    bool   CONTROL_WAVE(QString p_freq, int id, Task_Cmp * p_Cal_data);
    void   map_Col_Row_Num();
    bool   check_status();
    bool   ORG_TEST();
    bool   CFG_MP_TEST();
    bool   CFG_M_MP_TEST();
    void   combine_cal_data(Task_Cmp &p_old_cal_data,Task_Cmp & p_cur_cal_data,\
                            bool ismagn = true,bool isphase = true);


    void SAVE_ORG_DATA(TDATA &pdata, std::vector<QString> &p_freqs,\
                       QString psave_path);
    void SAVE_CAL_DATA(TDATA &pdata, std::vector<QString> &p_freqs,\
                       std::vector<int> &p_id,  QString psave_path);

    void SAVE_RealCal_Data(Task_CAL_S22 &p_cmp, QString path);
    void SAVE_RealCal_Data(QString ppath);
    void SAVE_FINAL_CAL(bool isend, QString type);

    int    gen_ID(short row, short col);
    double transdata(double valus = 0);
    double searchphase(double phase);
    void   TRANS_FINAL_CAL();
    void   gen_dBMag_Phase(QString data,double &mag,double &phase);
    void   gen_LinMag_Phase(QString data,double &mag,double &phase);
    void   gen_RelImg(QString data,double &mag,double &phase);
    double genLinMag(double real, double imag);
    double genLinMag(QString data);
    double genPhase(double real, double imag);
    double genPhase(QString data);
    double gendB(double real, double imag);
    double gendB(double mag);
    double gendB(QString data);
signals:
    void   EnableReturn(bool res);
    void   push_radar_data(int id, double freq, double M, double P);
    void   Handledata();
    void   appendBuf(QString str);
    void   appendbuf(const char *text);
    void   Wave_control(int id, double m, double p, bool status,TRontrol *p_TR);
    void   INIT_WAVE(bool status);
    void   DOWN_WAVE();
    void   SHOWUNIT(int id);
    void   RESETARRAYFACE();
    void   WAVE_CONNECT_FAILED();
    void   VNA_CONNECT_FAILED();
    void   Serialport_connect_failed();
    void   SHOW_CAL_STATUS();
private:
    CVTS::map_st                            m_task_global;  /////映射文件
    CVTS::SPoint                            m_arrar_offset; ///阵面中心偏移量
    int                                     m_map_width;
    int                                     m_map_height;

    TEST_TYPE                               m_test_type;  ////测试类型
    WORK_STATUS                             m_work_status;  ////工作状态
    Task_Map                                m_task_map;    ////映射文件（对应位置,没有坐标）

    std::map<int, Radar *>                  m_radars;     ////所有雷达点
    std::map<int,std::vector<int> >         m_PD;           ////对应扫描架位置下的探头信息
    std::map<int ,std::pair<short ,short> > m_RCN;           ////行列和ID 对照表
    std::map<int,CVTS::SPoint>              m_array_data;  ///阵面文件信息

    std::vector<int>                        m_ID;           ////所有探头信息
    std::vector<int>                        m_P;                    ////所有扫描架位置
    std::vector<QString>                    m_freqs;
    std::vector<QString>                    m_cal_freq_key;          ////校准库中所有的频率
    std::set<QString>                       m_success_freq;          ////提前收敛的频率

    Radar_Location                          m_radars_location;       ////阵面文件信息
    Task_CAL_S22                            m_cal_s21;               ///校准的最终数据
    Task_CAL_S22                            m_cal_new_s22_status_2;  ///实时测的状态2的S22
    Task_CAL_S22                            m_cal_new_s22_status_1;  ///实时测的状态1的S22
    Task_CAL_S21                            m_cal_temp_s22_status_2; ///用于保存第一个位置的匹配S22
    Task_CAL_S21                            m_cal_temp_s22_status_1; ///用于保存第一个位置的短路S22
    Task_CAL_S21                            m_file_cal_S21;          ///校准库的文件

    TDATA                                   m_task_org_data;   ////初态测试数据
    std::map<int,TDATA>                     m_cfgMP_data;     ////幅度相位一起测得数据
    std::map<int,TDATA>                     m_cfgM_MP_data;////先幅后相位的数据
    std::map<int,double>                    m_delt_mag;          ////加权值
    std::map<QString,std::pair<double,double> > m_base_mp;       ///基准值

    Task_Cmp                                m_temp_cal_data;     ///中间校准文件

    double                                  m_sweepshelf_time;////扫描架等待时间
    double                                  m_elesw_time;///电子开关等待时间
    double                                  m_multisw_time;///多路开关等待时间
    double                                  m_wave_time;///波控等待时间
    double                                  m_pnacollect_time; ///矢网采集等待时间默认0

    int                                     m_cfg_mp_times;///幅度相位一起配的次数
    int                                     m_cfg_m_mp_times;  ///先配幅度再配相位的次数

    bool                                    m_is_real_Cal;  ////是否实时校准
    bool                                    m_is_enable_S11;/////是否使用算法中的S11
    bool                                    m_is_collect_s11;  ////是否采集S11
    volatile bool                           m_iscontinus_test;/////满足收敛条件为true
    volatile bool                           m_isstop;////强制停止

    ConfigPhase                             m_config;      /////算法对象
    DataManage                              m_DataManage; ////数据管理类对象
    CParsefile                              m_parse;      ////用来解析校准文件类
    ConfigerExcel                           exportexcle;   ////将数据以excle形式保存

    QString                                 m_projfile_path;  ////工程文件.spcs路径
    QString                                 m_proj_path;     ////工程路径

    bool                                    m_status_continus;  ///人为干预基准时,一直处于false
    bool                                    m_isshow;///是否进行人为干预;
    double                                  m_base_delt_db;///算法中找基准值


};

#endif // TASKCENTER_607_H
