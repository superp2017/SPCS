#include "vnadapter.h"
#include "_global.h"
#include "QSettings"
#include "env_config.h"
#include <qmath.h>
#include "outputview.h"
#include "rs_vnadapter.h"


VNA_ENUM VNAdapter::s_vna = VNA_AGILENT;
VNAdapter::VNAdapter()
{
    m_ip = "192.168.1.99";
    m_buffer = new char[102400];
    isconnect =false;

}

VNAdapter::~VNAdapter()
{
    delete [] m_buffer;
    disconnect();
}

VNAdapter *VNAdapter::instance()
{   
    static VNAdapter* vdp_agilent = new VNAdapter();
    static RS_VNAdapter* vdp_rs = new RS_VNAdapter();
    if(s_vna == VNA_AGILENT)
    {
        return vdp_agilent;
    }else if(s_vna == VNA_RS)
    {
        return vdp_rs;
    }
    return vdp_agilent;
}

bool VNAdapter::connect()
{
    m_ip =ENV_config::instance()->get_Aglient_ip();
    if(isconnect) return true;
    if(VI_SUCCESS != viOpenDefaultRM(&m_defaultRm))
    {
        qDebug()<<"viOpenDefaultRM failed !";
        isconnect =false;
        return false;
    }

    sprintf(m_buffer, AGLIENT_CONN_STR, m_ip.toLocal8Bit().data());

    if(VI_SUCCESS != viOpen(m_defaultRm, m_buffer, VI_NULL, VI_NULL, &m_vi))
    {
        qDebug()<<"viOpen failed !";
        isconnect =false;
        return false;
    }

    if(VI_SUCCESS != viSetAttribute (m_vi, VI_ATTR_TMO_VALUE, 5000))
    {
        qDebug()<<"Set timeout failed!";
    }


    OutputView::instance()->append("connect OK !");
    isconnect =true;
    return true;
}

void VNAdapter::disconnect()
{
    if(m_vi) viClose(m_vi); m_vi = 0;
    if(m_defaultRm) viClose(m_defaultRm); m_defaultRm = 0;
}

QString VNAdapter::get_idn()
{
    connect();
    viPrintf(m_vi, "*IDN?\n");
    viScanf(m_vi, "%t", &m_buffer);

    return QString(m_buffer);
}

void VNAdapter::reset()
{
    connect();
    /// ����
    viPrintf(m_vi, "*RST\n");

    viPrintf(m_vi, "CALC1:PAR:DEL:ALL\n");
}

void VNAdapter::delAll()
{
    viPrintf(m_vi, "CALC1:PAR:DEL:ALL\n");
}


void VNAdapter::continue_triger()
{
    /// �ڴ���
    viPrintf(m_vi, "INIT:CONT OFF\n");
}

void VNAdapter::Internal_trigger()
{
    viPrintf(m_vi, "INIT:CONT ON\n");
}



void VNAdapter::setAveTimes(int times)
{
    connect();
    viPrintf(m_vi, "SENS:AVER ON \n");
    sprintf(m_buffer, "SENS:AVER:COUN %d\n", times);
    viPrintf(m_vi, m_buffer);
}

double VNAdapter::Sweeptime()
{
    connect();
    sprintf(m_buffer, "SENS1:SWE:TIME?\n");
    viPrintf(m_vi, m_buffer);
    viScanf (m_vi, "%t", m_buffer);
    return QString(m_buffer).toDouble();
}


//////////////////
/// \brief VNAdapter::set_sweep_time
/// \param sec
///  ����ɨ��ʱ��
void VNAdapter::set_sweep_time(double sec)
{
    connect();
    sprintf(m_buffer, "SENS1:SWE:TIME %f\n", sec/1000);
    viPrintf(m_vi, m_buffer);

}



//////////////////
/// \brief VNAdapter::set_freq
/// \param freq
///  ���õ���Ƶ��
void VNAdapter::set_freq(QString &freq)
{
    connect();
    /// ����ɨ�跽ʽ�� Liner
    viPrintf (m_vi, "SENS1:SWE:TYPE LIN\n");

    /// ����Ƶ�ʵ�
    sprintf(m_buffer, "SENS1:SWE:POIN %d\n", 1);
    viPrintf (m_vi, m_buffer);
    sprintf(m_buffer, "SENS1:FREQ:STAR %fHz\n", freq.toDouble());
    viPrintf (m_vi, m_buffer);
    sprintf(m_buffer, "SENS1:FREQ:STOP %fHz\n", freq.toDouble());
    viPrintf (m_vi, m_buffer);

    viPrintf(m_vi, "*OPC?\n");
    viScanf (m_vi, "%t", m_buffer);
}



////////////////////
/// \brief VNAdapter::set_freq
/// \param start
/// \param end
/// \param num
///  ����ɨƵƵ��
void VNAdapter::set_freq(double start, double end, int num)
{
    connect();
    /// ����ɨ�跽ʽ�� Liner
    viPrintf (m_vi, "SENS1:SWE:TYPE LIN\n");

    /// ����Ƶ�ʵ�
    sprintf(m_buffer, "SENS1:SWE:POIN %d\n", num);
    viPrintf (m_vi, m_buffer);
    sprintf(m_buffer, "SENS1:FREQ:STAR %fHz\n", start);
    viPrintf (m_vi, m_buffer);
    sprintf(m_buffer, "SENS1:FREQ:STOP %fHz\n", end);
    viPrintf (m_vi, m_buffer);
    viPrintf(m_vi, "*OPC?\n");
    viScanf (m_vi, "%t", m_buffer);
}



////////////////////////////
/// \brief VNAdapter::setPulseDefault
///  ��������
///  Ŀǰû�õ�
void VNAdapter::setPulseDefault()
{
    connect();
    viPrintf (m_vi, "sens:path:conf:elem 'PulseModDrive','Pulse1'\n");
    viPrintf (m_vi, "sour:pow:alc:mode openloop \n");
    viPrintf (m_vi, "sens:path:conf:elem 'Src1Out1PulseModEnable','Enable'\n");

    viPrintf (m_vi, "sens:path:conf:elem 'PulseTrigInput','Internal'\n");



    //viPrintf (m_vi, "trigger:sequence:scope current\n");
    // viPrintf (m_vi, "sens:swe:trig:poin on\n");
    // viPrintf (m_vi, "trigger:sequence:source immediate\n");


    viPrintf (m_vi, "SENS:PULS0:STAT 1\n");
    viPrintf (m_vi, "SENS:PULS1:STAT 1\n");
    viPrintf (m_vi, "SENS:PULS2:STAT 1\n");
    viPrintf (m_vi, "SENS:PULS3:STAT 1\n");
    viPrintf (m_vi, "SENS:PULS4:STAT 1\n");

    viPrintf (m_vi, "sens:puls:per .001\n");

    viPrintf (m_vi, "sens:puls1:width 0.0005\n");
    viPrintf (m_vi, "sens:puls1:delay 0.00008\n");
    viPrintf (m_vi, "sens:puls0:width 0.000001\n");
    viPrintf (m_vi, "sens:puls0:delay 0.0000004\n");

    viPrintf (m_vi, "sens:puls2:width 0.00025\n");
    viPrintf (m_vi, "sens:puls2:delay 0.00004\n");
    viPrintf (m_vi, "sens:puls3:width 0.00012\n");
    viPrintf (m_vi, "sens:puls3:delay 0.00002\n");
    viPrintf (m_vi, "sens:puls4:width 0.00006\n");
    viPrintf (m_vi, "sens:puls4:delay 0.00001\n");
    ///////
    viPrintf (m_vi, "SENS:SWE:GEN STEP\n");
    viPrintf (m_vi, "TRIG:SOUR MAN\n");


    //   viPrintf (m_vi, "TRIG:SCOP CURRENT\n");
}



//////////////////////////////////////
/// \brief VNAdapter::setPulse
/// \param iseable    �����ʹ��
/// \param period     ����
/// \param path0      path0ʹ��
/// \param path1      path1ʹ��
/// \param path2      path2ʹ��
/// \param path3      path3ʹ��
/// \param path4      path4ʹ��
/// \param path0_de   path0���
/// \param path0_wi   path0��ʱ
/// \param path1_de   path1���
/// \param path1_wi   path1��ʱ
/// \param path2_de   path2���
/// \param path2_wi   path2��ʱ
/// \param path3_de   path3���
/// \param path3_wi   path3��ʱ
/// \param path4_de   path4���
/// \param path4_wi   path4��ʱ
///
void VNAdapter::setPulse(bool iseable, double period, \
                         bool path0, bool path1, bool path2, bool path3, bool path4, \
                         double path0_de, double path0_wi, double path1_de, \
                         double path1_wi, double path2_de, double path2_wi, \
                         double path3_de, double path3_wi, double path4_de, \
                         double path4_wi)
{
    connect();
    if(!iseable)
        viPrintf (m_vi, "sens:path:conf:elem 'Src1Out1PulseModEnable','Disable'\n");
    else
    {
        viPrintf (m_vi, "sens:path:conf:elem 'PulseModDrive','Pulse1'\n");
        viPrintf (m_vi, "sour:pow:alc:mode openloop \n");
        viPrintf (m_vi, "sens:path:conf:elem 'Src1Out1PulseModEnable','Enable'\n");

        viPrintf (m_vi, "sens:path:conf:elem 'PulseTrigInput','Internal'\n");

        int ret = (path0 ? 1:0);
        sprintf(m_buffer, "SENS:PULS0:STAT %d\n", ret);
        viPrintf (m_vi, m_buffer);

        ret = (path1 ? 1:0);
        sprintf(m_buffer, "SENS:PULS1:STAT %d\n", ret);
        viPrintf (m_vi, m_buffer);

        ret = (path2 ? 1:0);
        sprintf(m_buffer, "SENS:PULS2:STAT %d\n", ret);
        viPrintf (m_vi, m_buffer);

        ret = (path3 ? 1:0);
        sprintf(m_buffer, "SENS:PULS3:STAT %d\n", ret);
        viPrintf (m_vi, m_buffer);

        ret = (path4 ? 1:0);
        sprintf(m_buffer, "SENS:PULS4:STAT %d\n", ret);
        viPrintf (m_vi, m_buffer);

        double  m_k = 1000000.0;
        double ls_period = period/m_k;
        double ls_path0_wi = path0_wi/m_k;
        double ls_path0_de = path0_de/m_k;
        double ls_path1_wi = path1_wi/m_k;
        double ls_path1_de = path1_de/m_k;
        double ls_path2_wi = path2_wi/m_k;
        double ls_path2_de = path2_de/m_k;
        double ls_path3_wi = path3_wi/m_k;
        double ls_path3_de = path3_de/m_k;
        double ls_path4_wi = path4_wi/m_k;
        double ls_path4_de = path4_de/m_k;


        sprintf(m_buffer, "sens:puls:per %.9lf\n", ls_period);
        viPrintf (m_vi, m_buffer);

        //  sprintf(m_buffer, "sens:puls0:width %.9lf\n", ls_path0_wi);
        // viPrintf (m_vi, m_buffer);
        sprintf(m_buffer, "sens:puls0:delay %.9lf\n", ls_path0_de);
        viPrintf (m_vi, m_buffer);

        sprintf(m_buffer, "sens:puls1:width %.9lf\n", ls_path1_wi);
        viPrintf (m_vi, m_buffer);
        sprintf(m_buffer, "sens:puls1:delay %.9lf\n", ls_path1_de);
        viPrintf (m_vi, m_buffer);

        sprintf(m_buffer, "sens:puls2:width %.9lf\n", ls_path2_wi);
        viPrintf (m_vi, m_buffer);
        sprintf(m_buffer, "sens:puls2:delay %.9lf\n", ls_path2_de);
        viPrintf (m_vi, m_buffer);

        sprintf(m_buffer, "sens:puls3:width %.9lf\n", ls_path3_wi);
        viPrintf (m_vi, m_buffer);
        sprintf(m_buffer, "sens:puls3:delay %.9lf\n", ls_path3_de);
        viPrintf (m_vi, m_buffer);

        sprintf(m_buffer, "sens:puls4:width %.9lf\n", ls_path4_wi);
        viPrintf (m_vi, m_buffer);
        sprintf(m_buffer, "sens:puls4:delay %.9lf\n", ls_path4_de);
        viPrintf (m_vi, m_buffer);

    }
    viPrintf (m_vi, "SENS:SWE:GEN STEP\n");
    viPrintf (m_vi, "TRIG:SOUR MAN\n");
}



////////////
/// \brief VNAdapter::set_power
/// \param pow
///  ���ù���
void VNAdapter::set_power(double pow)
{
    connect();
    /// ���ù���
    sprintf(m_buffer, "SOUR:POW %f\n", pow);
    viPrintf(m_vi, m_buffer);
}



///////////////
/// \brief VNAdapter::set_IF_bandwidth
/// \param bw
///  ������Ƶ����
void VNAdapter::set_IF_bandwidth(double bw)
{
    connect();
    /// ������Ƶ����
    sprintf(m_buffer, "SENS1:BANDwidth %f\n", bw);
    viPrintf(m_vi, m_buffer);
}


//////////
/// \brief VNAdapter::set_trace_S11
/// ���ü��� S11
void VNAdapter::set_trace_S11()
{
    connect();
    //    viPrintf(m_vi, "CALC1:PAR 'ch1_S11',S11,1\n");
    //    viPrintf(m_vi, "DISP:WIND1:TRAC1:FEED 'ch1_S11'\n");
    /// ���ö˿�ͨ��1 S11
    viPrintf (m_vi, "CALC1:PAR 'ch1_S11',S11,1\n");
    /// ������ʾ����
    viPrintf(m_vi, "DISP:WIND1:TRAC1:FEED 'ch1_S11'\n");
}




///////
/// \brief VNAdapter::set_trace_S22
///  ���ü��� S22
void VNAdapter::set_trace_S22()
{
    connect();
    /// ���ö˿�ͨ��1 S22
    viPrintf (m_vi, "CALC1:PAR 'ch1_S22',S22,1\n");
    /// ������ʾ����
    viPrintf(m_vi, "DISP:WIND1:TRAC4:FEED 'ch1_S22'\n");
}

/// \param isSend ? S21:S12
///  ���ü��� S21 �� S12
void VNAdapter::set_S21_TRACE(bool issend)
{
    if(issend)
        set_trace_S21();
    else
        set_trace_S12();
}



///////////////////
/// \brief VNAdapter::set_trace_S21

void VNAdapter::set_trace_S21()
{
    connect();
    /// ���ö˿�ͨ��1 S21
    viPrintf (m_vi, "CALC1:PAR 'ch1_S21',S21,1\n");
    /// ������ʾ����
    viPrintf(m_vi, "DISP:WIND1:TRAC3:FEED 'ch1_S21'\n");
}

//////////
/// \brief VNAdapter::set_trace_S12
/// ���ü��� S12
void VNAdapter::set_trace_S12()
{
    connect();
    /// ���ö˿�ͨ��1 S21
    viPrintf (m_vi, "CALC1:PAR 'ch1_S12',S12,1\n");
    /// ������ʾ����
    viPrintf(m_vi, "DISP:WIND1:TRAC2:FEED 'ch1_S12'\n");
}


//////////////
/// \brief VNAdapter::collect_S11
/// \return
///  �ɼ�S11
QString VNAdapter::collect_S11()
{
    /// ѡ������S11
    viPrintf(m_vi, "*OPC\n");
    viPrintf(m_vi, "INIT1:IMM\n");
    viPrintf(m_vi, "*OPC?\n");
    viScanf (m_vi, "%t", m_buffer);

    /// �ɼ�����
    viPrintf (m_vi, "CALC1:PAR:SEL 'ch1_S11'\n");
    viPrintf (m_vi, "CALC1:DATA? SDATA\n");

    viScanf (m_vi, "%t", m_buffer);

    return QString(m_buffer);
}


//////////
/// \brief VNAdapter::collect_S22
/// \return
///  �ɼ�S22
QString VNAdapter::collect_S22()
{
    /// ѡ������S22

    viPrintf(m_vi, "*OPC\n");
    viPrintf(m_vi, "INIT1:IMM\n");
    viPrintf(m_vi, "*OPC?\n");
    viScanf (m_vi, "%t", m_buffer);

    /// �ɼ�����
    viPrintf (m_vi, "CALC1:PAR:SEL 'ch1_S22'\n");
    viPrintf (m_vi, "CALC1:DATA? SDATA\n");
    viScanf (m_vi, "%t", m_buffer);

    return QString(m_buffer);
}
/// \param isSend ? S21:S12
/// \return
///  �ɼ�S21
QString VNAdapter::collectSendData(bool isSend)
{
    if(isSend)
        return collect_S21();
    else
        return collect_S12();
}

/////////////////////
/// \brief VNAdapter::collect_S21

QString VNAdapter::collect_S21()
{
    /// ѡ������S21
    viPrintf(m_vi, "*OPC\n");
    viPrintf(m_vi, "INIT1:IMM\n");
    viPrintf(m_vi, "*OPC?\n");
    viScanf (m_vi, "%t", m_buffer);
    /// �ɼ�����
    viPrintf (m_vi, "CALC1:PAR:SEL 'ch1_S21'\n");
    viPrintf (m_vi, "CALC1:DATA? SDATA\n");
    viScanf (m_vi, "%t", m_buffer);

    return QString(m_buffer);
}


/////////
/// \brief VNAdapter::collect_S12
/// \return
///  �ɼ�S12
QString VNAdapter::collect_S12()
{
    /// ѡ������S12
    viPrintf(m_vi, "*OPC\n");
    viPrintf(m_vi, "INIT1:IMM\n");
    viPrintf(m_vi, "*OPC?\n");
    viScanf (m_vi, "%t", m_buffer);

    /// �ɼ�����
    viPrintf (m_vi, "CALC1:PAR:SEL 'ch1_S12'\n");
    viPrintf (m_vi, "CALC1:DATA? SDATA\n");
    viScanf (m_vi, "%t", m_buffer);

    return QString(m_buffer);
}

/////////////
/// \brief VNAdapter::genLinMag
/// \param real
/// \param imag
/// \return
///  �������Է���
double VNAdapter::genLinMag(double real, double imag)
{
    return sqrt(real*real + imag * imag);
}

//////
/// \brief VNAdapter::genPhase
/// \param real
/// \param imag
/// \return
/// ������λ
double VNAdapter::genPhase(double real, double imag)
{
    return qAtan2(imag, real) / M_PI * 180;

}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///�������еĺ�����û�õ�
double VNAdapter::genMagn(double real, double imag)
{
    double db = (real * real + imag * imag)/50;
    if( db== 0)
        return 10 * log10(1.0) + 30;
    else
        return 10 * log10(db) + 30;
}

double VNAdapter::genMagn_w(double real, double imag)
{
    double db = (real * real + imag * imag);
    if( db== 0)
        return 10 * log10(1.0);
    else
        return 10 * log10(db);
}
QString VNAdapter::collect_S31()
{
    /// ѡ������S31

    // viPrintf(m_vi, "*OPC\n");
    viPrintf(m_vi, "INIT1:IMM\n");
    viPrintf(m_vi, "*OPC?\n");
    viScanf (m_vi, "%t", m_buffer);

    /// �ɼ�����
    viPrintf (m_vi, "CALC1:PAR:SEL 'ch1_S31'\n");
    viPrintf (m_vi, "CALC1:DATA? SDATA\n");

    viScanf (m_vi, "%t", m_buffer);

    return QString(m_buffer);
}

QString VNAdapter::collect_S33()
{
    /// ѡ������S33
    //   viPrintf(m_vi, "*OPC?\n");
    viPrintf(m_vi, "INIT1:IMM\n");
    viPrintf(m_vi, "*OPC?\n");
    viScanf (m_vi, "%t", m_buffer);

    /// �ɼ�����
    viPrintf (m_vi, "CALC1:PAR:SEL 'ch1_S33'\n");
    viPrintf (m_vi, "CALC1:DATA? SDATA\n");
    viScanf (m_vi, "%t", m_buffer);

    return QString(m_buffer);
}


void VNAdapter::set_trace_S31()
{
    connect();
    /// ���ö˿�ͨ��1 S31
    viPrintf (m_vi, "CALC1:PAR 'ch1_S31',S31,1\n");
    /// ������ʾ����
    viPrintf(m_vi, "DISP:WIND1:TRAC5:FEED 'ch1_S31'\n");
}

void VNAdapter::set_trace_S33()
{
    connect();
    /// ���ö˿�ͨ��1 S33
    viPrintf (m_vi, "CALC1:PAR 'ch1_S33',S33,1\n");
    /// ������ʾ����
    viPrintf(m_vi, "DISP:WIND1:TRAC6:FEED 'ch1_S33'\n");
}
