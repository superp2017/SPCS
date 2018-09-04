#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <QTextCodec>
#include <QString>
#include <map>
#include <vector>
#include <complex>

//global config

#define ENV_config_path      "./config/env.ini"
#define IC_CARD_CONFIG_PATH  "./config/IC_Card.ini"
#define FLOW_CONFIG          "./config/flowconfig.ini"

#define CURVE_SUFFIX         ".curve"
#define INI_Suffix           ".ini"
#define FILELISTS_SUFFIX     ".list"
#define PROJ_Suffix          ".spcs"



#define FULLRESULTFILE       "/FULLRESULT.res"
#define UNIT_TROUBLE         "UnitTrouble"

#define DEFAULT_PROJ         "/Default"
#define PROJ_PATH            "/Project"
#define PARAM_PATH           "/Param"
#define DATA_PATH            "/DATA"
#define PRINTIVE             "/primtive"

#define ORG_PATH             "/ORG_PATH"
#define CFG_MP_PATH          "/CFG_MP"
#define CFG_M_MP_PATH        "/CFG_M_MP"
#define FINAL_CFG            "FINAL_CFG"

#define CALDATA              "/CALDATA"

#define RESULT               "/result"
#define MIDDLE_DIR           "/middle"

#define BEFORE    "Before"
#define MIDDLE    "Middle"
#define AFTER     "After "
#define CAL_MP     "Cal"

#define S_1_1     "   S11 "
#define S_2_1     "   S21 "
#define S_2_2     "   S22 "


#define TYPE_CFG  "configphase"
#define TYPE_MP_1 "cfg_mp_1"

#define P_0_360   " 0~360  "
#define P180180   "-180~180"

#define AFG_COM     "COM3"

#define COLLECTNUMS_CFG   1
#define COLLECTNUMS_ORG   3
#define DELT_PHASE    10
#define DLET_P        2


#define TESTINIT_DIS        -724.5
#define SWEEPSHELF_DISTANCE  63

#define SweepShelf_Base     12

#define PS11             "S11"
#define PS21             "S21"
#define PS22             "S22"
#define PS12             "S12"

#define CFG_CAL         "MagnPhase"
#define CFG_CAL_1       "MP_1"
#define CFG_M           "CFG_M"
#define CFG_MP          "CFG_MP"
#define ORG_MP          "ORG_MP"
#define CFG_EXCLE       "CalData"
#define EXCLE_SUFFIX    ".xls"
#define ORG_SUFFIX      ".org"
#define MP_SUFFIX       ".mp"
#define CAL_MP_SUFFIX   ".cal"
#define CAL_MP_1_SUFFIC ".data"

#define Grid_step_w         63
#define Grid_step_h         105
#define Grid_width          27
#define Grid_height         16
#define Grid_half_w         13
#define Grid_half_h         8

#define Detector_num        16
#define MAX_OUTPUT          500

#define FREQ_K              1000
#define FREQ_M              1000000
#define FREQ_G              1000000000

#define OUT_BUFFER          1024 * 1024
#define RAY_Speed           300000000


#define AGLIENT_CONN_STR    "TCPIP0::%s::INSTR"
#define RS_CONN_STR         "TCPIP0::%s::INSTR"

#define CVTS_RED            QColor(255,0,0)
#define CVTS_GREEN          QColor(0,255,0)
#define CVTS_BLUE           QColor(0,0,255)
#define CVTS_YELLOW         QColor(255,255,0)
#define CVTS_PURPLE         QColor(255,0,255)
#define CVTS_GRAY           QColor(0,255,255)
#define CVTS_WHITE          QColor(255,255,255)
#define CVTS_BLACK          QColor(0,0,0)

enum VNA_ENUM{VNA_AGILENT,VNA_RS};


#define SPCS_Muti_N         16

namespace CVTS {

enum CVTS_Decetor{CD_1 = 0, CD_2, CD_3, CD_4, CD_5, CD_6, CD_7, CD_8, CD_9, \
                  CD_10, CD_11, CD_12, CD_13, CD_14, CD_15, CD_16,CD_17,CD_NUMS};

enum SwitchMatrix{S_1 = 17, S_2, S_3, S_4, S_5, S_6,S_7,S_8,S_9,S_10,S_11,S_12,\
                  S_13,S_14,S_15,S_16,S_17,S_18,S_19,S_20,SWNum};

enum CVTS_ANTENNA{AN_1 = 37,AN_2,AN_3,ANNUMS};

enum MINI1TI2{MINI=40};

enum NI_ANTENNA{AN_ZERO, AN_10, AN_20, AN_30, AN_40, AN_50,AN_60, AN_70};

enum Matrix{M_1 = 0,M_2,M_3,M_4,M_5,M_6,M_7,M_8,M_9,M_10,M_11,M_12,M_13,M_14,M_15,M_16,M_NUMS};

enum CVTS_STATUS{CVTS_NULL, CVTS_BEFORE_TEST, CVTS_TESTING, CVTS_AFTER_TEST};


enum TEST_TYPE{FILED_MAGN,FILED_PHASE,FILED_MAGN_PHASE,CONFIG_PHASE,TYPE_NONE};

enum WORK_STATUS{SEND,RECEIVE};

enum VNA_SWEEP_TYPE{SINGLE_POINT,CONTINUOUS_POINT};

enum CURVE_TYPE{MAGN_LINER,MAGN_dB,PHASE_LINER};

typedef struct _OUTPUT_STATUS_DATA
{
    double              t_begin_freq;
    double              t_end_freq;
    double              t_step_freq;
    int                 t_begin_detector;
    int                 t_end_detector;
    int                 t_begin_sweep;
    int                 t_end_sweep;
    int                 t_antenna_count;
}OUTPUT_STATUS_DATA;



typedef struct _pulse
{
    bool                   t_enable;
    QString                t_period;
    bool                   t_path0_enable;
    QString                t_path0_de;
    QString                t_path0_wid;
    bool                   t_path1_enable;
    QString                t_path1_de;
    QString                t_path1_wid;
    bool                   t_path2_enable;
    QString                t_path2_de;
    QString                t_path2_wid;
    bool                   t_path3_enable;
    QString                t_path3_de;
    QString                t_path3_wid;
    bool                   t_path4_enable;
    QString                t_path4_de;
    QString                t_path4_wid;

}PULSE;

typedef struct _TESTTIMES
{
    QString                t_sweepshelf_times;
    QString                t_wavec_times;
    QString                t_multiswitch_times;
    QString                t_elecswitch_times;
    QString                t_cfg_mp_times;
    QString                t_cfg_m_mp_times;
    QString                t_base_delt_db;
}TESTTIMES;

typedef struct _param_sets
{
    QString                t_proj_name;
    QString                t_init_cfg_table;
    VNA_SWEEP_TYPE         t_sweep_type;
    WORK_STATUS            t_status;
    TEST_TYPE              t_test_type;
    QString                t_bandwidth;
    QString                t_power;
    QString                t_sweep_times;
    std::vector<QString>   t_fre_pts;
    QString                t_fre_iter;
    QString                t_attenua;

    TESTTIMES              t_test_time;
    PULSE                  t_SetPulse;
}Param_sets;

typedef struct _Monitor_info    //监控实时显示的信息
{
    QString  t_shelfinfo;        //扫描架信息
    QString  t_probeinfo;        //探头信息
    QString  t_unitinfo;         //阵元信息
    QString  t_nearprobeninfo;   //近场探头信息
    QString  t_vnainfo;          //矢网信息
}Monitor_info;

typedef struct _SPoint
{
    double  x;
    double  y;
    double  z;
}SPoint;

typedef struct _RadarD
{
    int     id;
    SPoint  pr;
    SPoint  pd;
}RadarD;

typedef std::map<int, std::complex<double> >        S11_Map;
typedef std::map<int, std::complex<double> >        S22_Map;
typedef std::map<int, std::complex<double> >        S21_Map;

typedef std::map<int, std::pair<CVTS::SPoint,std::pair<int,int> > >     Radar_Location;
typedef std::map<int, std::map<int, std::vector<int> > >                Task_Map;

typedef std::map<QString, std::map<int, QString > >                     Task_S11;
typedef std::map<QString, std::map<int, QString > >                     Task_S22;
typedef std::map<QString, std::map<int, QString > >                     Task_S21;
typedef std::map<QString, std::map<int, QString > >                     Task_Res;

typedef std::map<QString, std::map<int, std::pair<double, double> > >   Task_Cmp;
typedef std::map<QString, std::map<int, std::pair<double, double> > >   Task_Relevance;

typedef std::map<QString,std::map<QString,std::map<int,double> > >      Task_Phase1;

typedef  std::map<int,std::map<QString,std::pair<double,double> > >     Task_CAL_S21;

typedef  std::map<int,std::map<int,std::map<QString,std::pair<double,double> > > >   Task_CAL_S22;


typedef std::map<NI_ANTENNA,int>                    AN_Map;
typedef std::map<QString,std::pair<double,double> > RadarDataMap;


//typedef std::map<QString,std::map<QString,std::map<QString,std::pair<std::vector<QString>, std::vector<QString> > > > > BackHandleData;
typedef std::map<QString,std::map<QString,std::map<QString,std::map<int,std::pair<QString,QString> > > > > BackHandleData;



///2014/6/9 hf
//type,freq,id,magn,phase
typedef std::map<QString, std::map<QString, std::map<int, std::pair<QString,QString> > > > H_ORG;
//times,type,freq,id,magn,phase
typedef std::map<int, std::map<QString, std::map<QString, std::map<int, std::pair<QString,QString> > > > > H_CFG_MP;
//freq,id,magn,phase
typedef std::map<QString, std::map<int, std::pair<QString,QString> > >  H_CFG_FINAL;

typedef struct _TDATA
{
    QString                                 t_s11_Fname;
    QString                                 t_s21_Fname;
    QString                                 t_s22_Fname;
    QString                                 t_mp_Fname;
    QString                                 t_mp_1_Fname;
    QString                                 t_excle_Fname;

    Task_S21                                t_task_s21;
    Task_S11                                t_task_s11_open;
    Task_S22                                t_task_s22_open;
    Task_S11                                t_task_s11_close;
    Task_S22                                t_task_s22_close;

    Task_Cmp                                t_cfg_magnphase;
    Task_Cmp                                t_cfg_mp_1;
}TDATA;



typedef struct _Curvedata
{
    std::vector<QString>     t_magn;
    std::vector<QString>     t_phase;
    std::vector<QString>     t_id;
    QString                  t_date;
    QString                  t_freq;
} Curvedata;

struct GBKToUnicode
{
    static QString toUnicode(const char *p)
    {
        static QTextCodec *codec = QTextCodec::codecForName("GBK");
        return codec->toUnicode(p);
    }
    static QString toUnicode(QString &text)
    {
        static QTextCodec *codec = QTextCodec::codecForName("GBK");
        return codec->toUnicode(text.toLocal8Bit().data());
    }
};


struct SPCS_dB
{
    static double dB(double magn)
    {
        if(magn >0)
            return  20*log10(magn);
        else
            return 0;
    }
};



struct COMBOX_INDEX_RREQ
{
    static  void GET_Combox_Index_Freq(QString freq, QString &cur,int &index)
    {
        double fre = freq.toDouble();
        if(fre <FREQ_K)
        {
            cur = freq;
            index = 0;
        }
        if(fre >= FREQ_K && fre < FREQ_M)
        {
            cur = QString::number(fre/FREQ_K);
            index = 1;
        }
        if(fre >= FREQ_M && fre <FREQ_G)
        {
            cur = QString::number(fre/FREQ_M);
            index = 2;
        }
        if(fre >= FREQ_G)
        {
            cur = QString::number(fre/FREQ_G);
            index = 3;
        }
    }
};

struct DoubleFre_TO_QStringFreq
{
    static  void Double_TO_QString(double freq_num, QString &freq_str)
    {
        if(freq_num < FREQ_K)
            freq_str = QString::number(freq_num,'f',2) + " Hz";
        if(freq_num >= FREQ_K && freq_num < FREQ_M)
        {
            freq_num  = freq_num/FREQ_K;
            freq_str = QString::number(freq_num,'f',2) + " KHz";
        }
        if(freq_num >= FREQ_M && freq_num < FREQ_G)
        {
            freq_num  = freq_num/FREQ_M;
            freq_str = QString::number(freq_num,'f',2) +  " MHz";
        }
        if(freq_num >= FREQ_G)
        {
            freq_num  = freq_num/FREQ_G;
            freq_str = QString::number(freq_num,'f',2) + " GHz";
        }
    }
};

typedef struct _map_item_st
{
    int item_p;
    int item_d;
    int item_count;
    std::map<int, SPoint>   items;
}map_item_st;

typedef struct _map_st
{
    int min_d;
    int max_d;
    int min_p;
    int max_p;
    int count;
    std::vector<map_item_st>    map_vec;
    void clear()
    {
        min_d = 0;
        max_d = 0;
        min_p = 0;
        max_p = 0;
        count = 0;
        map_vec.clear();
    }
}map_st;

typedef struct st_task_res
{

    bool    sign;
    int     last_id;
    int     next_id;
    int     cur_position;
    int     cur_detector;
    int     cur_antenna;
    void*   others;
}task_res;

typedef std::map<int, std::vector<std::complex<double> >* >      MVCD;

}




#endif // _GLOBAL_H
