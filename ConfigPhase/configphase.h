#ifndef CONFIGPHASE_H
#define CONFIGPHASE_H

#include "configphase_global.h"
#include "_global.h"
#include <set>
#include <QString>
#include  <map>


using namespace CVTS;
#define SPEEDOFLIGHT 3*100000000


class CONFIGPHASESHARED_EXPORT ConfigPhase
{
    
public:
    ConfigPhase();
    Task_Cmp& PhaseCalibration(std::vector<int> &p_id, Task_S21 &p_s21,
                               Radar_Location &p_location, \
                               CVTS::SPoint &offset, \
                               std::map<int,double>  &p_delt_data, \
                               Task_CAL_S22 &p_cal_s21, \
                               std::vector<QString> &p_freq_key, \
                               std::map<QString,std::pair<double,double> > *p_base_mp, \
                               double pbase_db);
    void ClearBuffer();
    std::map<QString,std::map<int,double> > &get_Phase1();
    Task_Cmp&get_cfg_mp_1()      {return m_cfg_mp_1;}
    std::map<QString,std::pair<double,double> > &get_cur_base_mp()\
    {return m_cur_base_mp;}
protected:
    int    gen_id(short row,short col);
    void   CalcORGMagnPhase();
    void   CalcDMin();
    void   CalcMag_Phase_d();
    void   CalMag_Final();
    void   Calc_Phase_1();
    void   Calc_mp_1();
    void   Calc_delt_phase();
    double Calc_Density(double phase, double std, double ave);
    double Search_phase(double phase);
    double genMagn(double real, double imag);
    double genPhase(double real, double imag);
    void   check_differ(QString &curfreq);
    void IdToAddr(int id, short &row, short &col);
private:
    std::vector<int>                            m_id;
    Task_S21                                    m_s21;
    Radar_Location                              m_location;
    Task_Cmp                                    m_Data1;
    Task_Cmp                                    m_Data2;
    Task_Cmp                                    m_configpha_result;
    Task_Cmp                                    m_cfg_mp_1;
    double                                      m_DMin_min;
    std::map<QString,std::map<int,double> >     m_CAL_mag;
    std::map<QString,std::map<int,double> >     m_mag_1;
    std::map<QString,std::map<int,double> >     m_Phase_1;
    std::map<QString,std::map<int,double> >     m_CAL_mag_final;
    std::map<QString,std::map<int,double> >     m_Phase_d;
    std::map<QString,std::pair<double,double> > m_Ave_std_Phase_1;
    std::map<QString,std::pair<double,double> > *m_base_mp;
    std::map<int,double>                        m_DMin;
    std::map<int,double>                        m_delt_mag;
    Task_CAL_S22                                m_s21_cal;
    std::vector<QString>                        m_freq_key;
    std::map<QString,std::pair<double,double> > m_cur_base_mp ;
    double                                      m_base_db;
    CVTS::SPoint                                m_arrar_offset;
    };

#endif // CONFIGPHASE_H
