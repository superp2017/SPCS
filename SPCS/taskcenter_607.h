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
 * �ܵĲ��������࣬��ɲ�������ĵ���
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
    CVTS::map_st                            m_task_global;  /////ӳ���ļ�
    CVTS::SPoint                            m_arrar_offset; ///��������ƫ����
    int                                     m_map_width;
    int                                     m_map_height;

    TEST_TYPE                               m_test_type;  ////��������
    WORK_STATUS                             m_work_status;  ////����״̬
    Task_Map                                m_task_map;    ////ӳ���ļ�����Ӧλ��,û�����꣩

    std::map<int, Radar *>                  m_radars;     ////�����״��
    std::map<int,std::vector<int> >         m_PD;           ////��Ӧɨ���λ���µ�̽ͷ��Ϣ
    std::map<int ,std::pair<short ,short> > m_RCN;           ////���к�ID ���ձ�
    std::map<int,CVTS::SPoint>              m_array_data;  ///�����ļ���Ϣ

    std::vector<int>                        m_ID;           ////����̽ͷ��Ϣ
    std::vector<int>                        m_P;                    ////����ɨ���λ��
    std::vector<QString>                    m_freqs;
    std::vector<QString>                    m_cal_freq_key;          ////У׼�������е�Ƶ��
    std::set<QString>                       m_success_freq;          ////��ǰ������Ƶ��

    Radar_Location                          m_radars_location;       ////�����ļ���Ϣ
    Task_CAL_S22                            m_cal_s21;               ///У׼����������
    Task_CAL_S22                            m_cal_new_s22_status_2;  ///ʵʱ���״̬2��S22
    Task_CAL_S22                            m_cal_new_s22_status_1;  ///ʵʱ���״̬1��S22
    Task_CAL_S21                            m_cal_temp_s22_status_2; ///���ڱ����һ��λ�õ�ƥ��S22
    Task_CAL_S21                            m_cal_temp_s22_status_1; ///���ڱ����һ��λ�õĶ�·S22
    Task_CAL_S21                            m_file_cal_S21;          ///У׼����ļ�

    TDATA                                   m_task_org_data;   ////��̬��������
    std::map<int,TDATA>                     m_cfgMP_data;     ////������λһ��������
    std::map<int,TDATA>                     m_cfgM_MP_data;////�ȷ�����λ������
    std::map<int,double>                    m_delt_mag;          ////��Ȩֵ
    std::map<QString,std::pair<double,double> > m_base_mp;       ///��׼ֵ

    Task_Cmp                                m_temp_cal_data;     ///�м�У׼�ļ�

    double                                  m_sweepshelf_time;////ɨ��ܵȴ�ʱ��
    double                                  m_elesw_time;///���ӿ��صȴ�ʱ��
    double                                  m_multisw_time;///��·���صȴ�ʱ��
    double                                  m_wave_time;///���صȴ�ʱ��
    double                                  m_pnacollect_time; ///ʸ���ɼ��ȴ�ʱ��Ĭ��0

    int                                     m_cfg_mp_times;///������λһ����Ĵ���
    int                                     m_cfg_m_mp_times;  ///�������������λ�Ĵ���

    bool                                    m_is_real_Cal;  ////�Ƿ�ʵʱУ׼
    bool                                    m_is_enable_S11;/////�Ƿ�ʹ���㷨�е�S11
    bool                                    m_is_collect_s11;  ////�Ƿ�ɼ�S11
    volatile bool                           m_iscontinus_test;/////������������Ϊtrue
    volatile bool                           m_isstop;////ǿ��ֹͣ

    ConfigPhase                             m_config;      /////�㷨����
    DataManage                              m_DataManage; ////���ݹ��������
    CParsefile                              m_parse;      ////��������У׼�ļ���
    ConfigerExcel                           exportexcle;   ////��������excle��ʽ����

    QString                                 m_projfile_path;  ////�����ļ�.spcs·��
    QString                                 m_proj_path;     ////����·��

    bool                                    m_status_continus;  ///��Ϊ��Ԥ��׼ʱ,һֱ����false
    bool                                    m_isshow;///�Ƿ������Ϊ��Ԥ;
    double                                  m_base_delt_db;///�㷨���һ�׼ֵ


};

#endif // TASKCENTER_607_H
