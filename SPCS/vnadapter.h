#ifndef VNADAPTER_H
#define VNADAPTER_H
#include <QString>
#include <string>
//#include "pna.h"
#include <list>
#include <vector>
#include <visa.h>
#include <QDebug>
#include <Windows.h>
#include <qmath.h>
#include "_global.h"

/*!
 * \brief The VNAdapter class
 * Ê§Íø¿ØÖÆÀà£¨°²½ÝÂ×£©
 */
class  VNAdapter
{
protected:
    VNAdapter();
    virtual ~VNAdapter();

public:
    static VNAdapter *instance();
    static VNA_ENUM s_vna;

    virtual bool connect();
    virtual void disconnect();
    virtual QString get_idn();
    virtual void reset();

    virtual void delAll();
    virtual double Sweeptime();
    virtual void continue_triger();
    virtual void Internal_trigger();
    virtual void setAveTimes(int times);
    virtual void set_sweep_time(double sec);
    virtual void set_freq(QString &freq);
    virtual void set_freq(double start,double end,int num);
    virtual void set_power(double pow);
    virtual void set_IF_bandwidth(double bw);
    virtual void setPulseDefault();
    virtual void setPulse(bool iseable,double period = 0,bool path0 = false,bool path1 = false,bool path2 =false,\
                  bool path3 =false,bool path4 =false,double path0_de = 0.0004,double path0_wi = 0.001,\
                  double path1_de = 0.008,double path1_wi = 0.01,double path2_de = 0.008,double path2_wi = 0.01,\
                  double path3_de = 0.008,double path3_wi = 0.01,double path4_de = 0.008,double path4_wi = 0.01);

    virtual void set_S21_TRACE(bool issend = false);
    virtual void set_trace_S11();
    virtual void set_trace_S22();
    virtual void set_trace_S21();
    virtual void set_trace_S12();
    virtual void set_trace_S31();
    virtual void set_trace_S33();


    static double genLinMag(double real, double imag);
    static double genMagn(double real, double imag);
    static double genMagn_w(double real, double imag);
    static double genPhase(double real, double imag);

    virtual QString collect_S11();
    virtual QString collect_S22();
    virtual QString collectSendData(bool isSend  = false);
    virtual QString collect_S21();
    virtual QString collect_S12();
    virtual QString collect_S31();
    virtual QString collect_S33();

protected:
    ViSession   m_defaultRm;
    ViSession   m_vi;
    QString     m_ip;
    char*       m_buffer;
    bool        isconnect;
};

#endif // VNADAPTER_H


