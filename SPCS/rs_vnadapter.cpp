#include "rs_vnadapter.h"
#include "_global.h"
#include "QSettings"
#include "env_config.h"
#include <qmath.h>
#include "outputview.h"

RS_VNAdapter::RS_VNAdapter()
{
    m_ip = "192.168.1.99";
    m_buffer = new char[102400];
    isconnect =false;
}

RS_VNAdapter::~RS_VNAdapter()
{
    delete [] m_buffer;
    disconnect();
}

//RS_VNAdapter *RS_VNAdapter::instance()
//{
//    static RS_VNAdapter* vdp = new RS_VNAdapter();
//    return vdp;
//}

bool RS_VNAdapter::connect()
{
    if(isconnect) return true;

    m_ip = ENV_config::instance()->get_r_s_ip();
    if(VI_SUCCESS != viOpenDefaultRM(&m_defaultRm))
    {
        qDebug()<<"viOpenDefaultRM failed !";
        isconnect =false;
        return false;
    }

    sprintf(m_buffer, RS_CONN_STR, m_ip.toLocal8Bit().data());
    //  viSetAttribute()
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


    //OutputView::instance()->append("connect OK !");
    isconnect =true;
    return true;
}

void RS_VNAdapter::disconnect()
{
    if(m_vi) viClose(m_vi); m_vi = 0;
    if(m_defaultRm) viClose(m_defaultRm); m_defaultRm = 0;
}

QString RS_VNAdapter::get_idn()
{
    connect();
    viPrintf(m_vi, ViString("*IDN?\n"));
    viScanf(m_vi, ViString("%t"), &m_buffer);

    return QString(m_buffer);
}

void RS_VNAdapter::reset()
{
    connect();
    /// 重置
    viPrintf(m_vi, ViString("*RST\n"));

    viPrintf(m_vi, ViString("CALC1:PAR:DEL:ALL\n"));
}

void RS_VNAdapter::delAll()
{
    viPrintf(m_vi, ViString("CALC1:PAR:DEL:ALL\n"));
}

double RS_VNAdapter::Sweeptime()
{
    connect();
    sprintf(m_buffer, ViString("SENS1:SWE:TIME?\n"));
    viPrintf(m_vi, m_buffer);
    viScanf (m_vi, ViString("%t"), m_buffer);
    return QString(m_buffer).toDouble();
}

void RS_VNAdapter::continue_triger()
{
    /// 内触发
    viPrintf(m_vi, ViString("INIT:CONT OFF\n"));
}

void RS_VNAdapter::Internal_trigger()
{
    viPrintf(m_vi, ViString("INIT:CONT ON\n"));
}

void RS_VNAdapter::setAveTimes(int times)
{
    connect();
    viPrintf(m_vi, ViString("SENS1:AVER ON \n"));
    sprintf(m_buffer, "SENS1:AVER:COUN %d\n", times);
    viPrintf(m_vi, m_buffer);
}

void RS_VNAdapter::set_sweep_time(double sec)
{
    connect();
    sprintf(m_buffer,"SENS1:SWE:TIME %f\n", sec/1000);
    viPrintf(m_vi, m_buffer);
}

void RS_VNAdapter::set_freq(QString &freq)
{
    connect();
    /// 设置扫描方式： Liner
    viPrintf (m_vi, ViString("SENS1:SWE:TYPE LIN\n"));

    /// 设置频率点
    sprintf(m_buffer, "SENS1:SWE:POIN %d\n", 1);
    viPrintf (m_vi, m_buffer);
    sprintf(m_buffer,"SENS1:FREQ:STAR %fHz\n", freq.toDouble());
    viPrintf (m_vi, m_buffer);
    sprintf(m_buffer, "SENS1:FREQ:STOP %fHz\n", freq.toDouble());
    viPrintf (m_vi, m_buffer);

    viPrintf(m_vi, ViString("*OPC?\n"));
    viScanf (m_vi, ViString("%t"), m_buffer);
}

void RS_VNAdapter::set_freq(double start, double end, int num)
{
    connect();
    /// 设置扫描方式： Liner
    viPrintf (m_vi, ViString("SENS1:SWE:TYPE LIN\n"));

    /// 设置频率点
    sprintf(m_buffer, "SENS1:SWE:POIN %d\n", num);
    viPrintf (m_vi, m_buffer);
    sprintf(m_buffer, "SENS1:FREQ:STAR %fHz\n", start);
    viPrintf (m_vi, m_buffer);
    sprintf(m_buffer, "SENS1:FREQ:STOP %fHz\n", end);
    viPrintf (m_vi, m_buffer);
    viPrintf(m_vi, ViString("*OPC?\n"));
    viScanf (m_vi, ViString("%t"), m_buffer);
}

void RS_VNAdapter::set_power(double pow)
{
    connect();
    /// 设置功率
    sprintf(m_buffer, ViString("SOUR:POW %f\n"), pow);
    viPrintf(m_vi, m_buffer);
}

void RS_VNAdapter::set_IF_bandwidth(double bw)
{
    connect();
    /// 设置中频带宽
    sprintf(m_buffer, ViString("SENS1:BANDwidth %f\n"), bw);
    viPrintf(m_vi, m_buffer);
}

void RS_VNAdapter::setPulseDefault()
{

}

void RS_VNAdapter::setPulse(bool iseable, double period, \
                            bool path0, bool path1, bool path2, bool path3, bool path4,\
                            double path0_de, double path0_wi, \
                            double path1_de, double path1_wi, \
                            double path2_de, double path2_wi, \
                            double path3_de, double path3_wi, \
                            double path4_de, double path4_wi)
{
    //    sprintf(buf,"SENS1:SWE:TYPE POINt\n");
    //    viPrintf (m_vi, buf);

    //    sprintf(buf, "SOUR1:FREQ:CW %fMHz\n", freq);
    //    viPrintf (m_vi, buf);

    //    char* ret = (path0 ? "ON":"OFF");
    //    sprintf(buf,"EUN:PMOD1 %s\n", ret);
    //    viPrintf(m_vi,buf);


    if(iseable)
    {
        double  m_k = 1000000.0;
        double ls_period = period/m_k;
        //    double ls_path0_wi = path0_wi/m_k;
        //    double ls_path0_de = path0_de/m_k;
        double ls_path1_wi = path1_wi/m_k;
        double ls_path1_de = path1_de/m_k;
        double ls_path2_wi = path2_wi/m_k;
        double ls_path2_de = path2_de/m_k;
        double ls_path3_wi = path3_wi/m_k;
        double ls_path3_de = path3_de/m_k;
        double ls_path4_wi = path4_wi/m_k;
        double ls_path4_de = path4_de/m_k;

        sprintf(m_buffer,"PULS:GEN ON\n");
        viPrintf (m_vi, m_buffer);


        //channel 2
        char *ret = (path2 ? (char*)("ON"):(char*)("OFF"));
        sprintf(m_buffer,ViString("EUN:PMOD1 %s\n"), ret);
        viPrintf(m_vi,m_buffer);



        //channel 4
        ret = (path4 ? (char*)("ON"):(char*)("OFF"));
        sprintf(m_buffer,"EUN:PMOD2 %s\n", ret);
        viPrintf(m_vi,m_buffer);




        sprintf(m_buffer,"PULS:GEN:PER %f us\n",period);
        viPrintf(m_vi,m_buffer);



        //channel 2
        sprintf(m_buffer,"PULS:GEN1:WIDT %f us\n",ls_path2_wi * 1000000);
        viPrintf(m_vi,m_buffer);
        //        sprintf(m_buffer,"PULS:GEN1:DEL %f s\n",ls_path2_de);
        //        viPrintf(m_vi,m_buffer);



        //channel 4
        sprintf(m_buffer,"PULS:GEN2:WIDT %f us\n",ls_path4_wi * 1000000);
        viPrintf(m_vi,m_buffer);
        qDebug() << "delay = " << ls_path4_de;
        sprintf(m_buffer,"PULS:GEN1:DEL %f us\n",ls_path4_de * 1000000);
        viPrintf(m_vi,m_buffer);

        sprintf(m_buffer,"PULS:GEN1:TYPE SING\n");//pulse1 type:single
        viPrintf(m_vi,m_buffer);
        sprintf(m_buffer,"PULS:GEN2:TYPE SING\n");//pulse2 type:single
        viPrintf(m_vi,m_buffer);

        sprintf(m_buffer,"TRIG:PULS REP\n");
        viPrintf(m_vi,m_buffer);

        sprintf(m_buffer,"TRIG:SOUR PGEN\n");
        viPrintf (m_vi, m_buffer);

        viPrintf(m_vi, ViString("INIT:CONT OFF\n"));
        viPrintf(m_vi, ViString("INIT1:IMM\n"));

    }else
    {
        sprintf(m_buffer,"PULS:GEN OFF\n");
        viPrintf (m_vi, m_buffer);
    }
}

void RS_VNAdapter::set_S21_TRACE(bool issend)
{
    if(issend)
        set_trace_S21();
    else
        set_trace_S12();
}

void RS_VNAdapter::set_trace_S11()
{
    connect();
    //    viPrintf(m_vi, "CALC1:PAR 'ch1_S11',S11,1\n");
    //    viPrintf(m_vi, "DISP:WIND1:TRAC1:FEED 'ch1_S11'\n");
    /// 设置端口通道1 S11
    viPrintf (m_vi, ViString("CALC1:PAR:SDEF 'ch1_S11','S11'\n"));

    /// 设置显示窗口
    viPrintf(m_vi, ViString("DISP:WIND1:TRAC1:FEED 'ch1_S11'\n"));
}

void RS_VNAdapter::set_trace_S22()
{
    connect();
    /// 设置端口通道1 S22
    viPrintf (m_vi, ViString("CALC1:PAR:SDEF 'ch1_S22','S22'\n"));
    /// 设置显示窗口
    viPrintf(m_vi, ViString("DISP:WIND1:TRAC4:FEED 'ch1_S22'\n"));
}

void RS_VNAdapter::set_trace_S21()
{
    connect();
    /// 设置端口通道1 S21
    viPrintf (m_vi, ViString("CALC1:PAR:SDEF 'ch1_S21','S21'\n"));
    /// 设置显示窗口
    viPrintf(m_vi, ViString("DISP:WIND1:TRAC3:FEED 'ch1_S21'\n"));
}

void RS_VNAdapter::set_trace_S12()
{
    connect();
    /// 设置端口通道1 S21
    viPrintf (m_vi, ViString("CALC1:PAR:SDEF 'ch1_S12','S12'\n"));
    /// 设置显示窗口
    viPrintf(m_vi, ViString("DISP:WIND1:TRAC2:FEED 'ch1_S12'\n"));
}

void RS_VNAdapter::set_trace_S31()
{
    connect();
    /// 设置端口通道1 S31
    viPrintf (m_vi, ViString("CALC1:PAR:SDEF 'ch1_S31','S31'\n"));
    /// 设置显示窗口
    viPrintf(m_vi, ViString("DISP:WIND1:TRAC5:FEED 'ch1_S31'\n"));
}

void RS_VNAdapter::set_trace_S33()
{
    connect();
    /// 设置端口通道1 S33
    viPrintf (m_vi, ViString("CALC1:PAR:SDEF 'ch1_S33','S33'\n"));
    /// 设置显示窗口
    viPrintf(m_vi, ViString("DISP:WIND1:TRAC6:FEED 'ch1_S33'\n"));
}

double RS_VNAdapter::genLinMag(double real, double imag)
{
    return sqrt(real*real + imag * imag);
}

double RS_VNAdapter::genMagn(double real, double imag)
{
    double db = (real * real + imag * imag)/50;
    if( db== 0)
        return 10 * log10(1.0) + 30;
    else
        return 10 * log10(db) + 30;
}

double RS_VNAdapter::genMagn_w(double real, double imag)
{
    double db = (real * real + imag * imag);
    if( db== 0)
        return 10 * log10(1.0);
    else
        return 10 * log10(db);
}

double RS_VNAdapter::genPhase(double real, double imag)
{
    return qAtan2(imag, real) / M_PI * 180;
}

QString RS_VNAdapter::collect_S11()
{
    /// 选定迹线S11
    viPrintf(m_vi, ViString("*OPC\n"));
    viPrintf(m_vi, ViString("INIT1:IMM\n"));
    viPrintf(m_vi, ViString("*OPC?\n"));
    viScanf (m_vi, ViString("%t"), m_buffer);

    /// 采集数据
    viPrintf (m_vi, ViString("CALC1:PAR:SEL 'ch1_S11'\n"));
    viPrintf (m_vi, ViString("CALC1:DATA? SDATA\n"));

    viScanf (m_vi, ViString("%t"), m_buffer);

    return QString(m_buffer);
}

QString RS_VNAdapter::collect_S22()
{
    /// 选定迹线S22

    viPrintf(m_vi, ViString("*OPC\n"));
    viPrintf(m_vi, ViString("INIT1:IMM\n"));
    viPrintf(m_vi, ViString("*OPC?\n"));
    viScanf (m_vi, ViString("%t"), m_buffer);

    /// 采集数据
    viPrintf (m_vi, ViString("CALC1:PAR:SEL 'ch1_S22'\n"));
    viPrintf (m_vi, ViString("CALC1:DATA? SDATA\n"));
    viScanf (m_vi, ViString("%t"), m_buffer);

    return QString(m_buffer);
}

QString RS_VNAdapter::collectSendData(bool isSend)
{
    if(isSend)
        return collect_S21();
    else
        return collect_S12();
}

QString RS_VNAdapter::collect_S21()
{
    /// 选定迹线S21
    viPrintf(m_vi, ViString("*OPC\n"));
    viPrintf(m_vi, ViString("INIT1:IMM\n"));
    viPrintf(m_vi, ViString("*OPC?\n"));
    viScanf (m_vi, ViString("%t"), m_buffer);
    /// 采集数据
    viPrintf (m_vi, ViString("CALC1:PAR:SEL 'ch1_S21'\n"));
    viPrintf (m_vi, ViString("CALC1:DATA? SDATA\n"));
    viScanf (m_vi, ViString("%t"), m_buffer);

    return QString(m_buffer);
}

QString RS_VNAdapter::collect_S12()
{
    /// 选定迹线S12
    viPrintf(m_vi, ViString("*OPC\n"));
    viPrintf(m_vi, ViString("INIT1:IMM\n"));
    viPrintf(m_vi, ViString("*OPC?\n"));
    viScanf (m_vi, ViString("%t"), m_buffer);

    /// 采集数据
    viPrintf (m_vi, ViString("CALC1:PAR:SEL 'ch1_S12'\n"));
    viPrintf (m_vi, ViString("CALC1:DATA? SDATA\n"));
    viScanf (m_vi, ViString("%t"), m_buffer);

    return QString(m_buffer);
}

QString RS_VNAdapter::collect_S31()
{
    /// 选定迹线S31

    // viPrintf(m_vi, "*OPC\n");
    viPrintf(m_vi, ViString("INIT1:IMM\n"));
    viPrintf(m_vi, ViString("*OPC?\n"));
    viScanf (m_vi, ViString("%t"), m_buffer);

    /// 采集数据
    viPrintf (m_vi, ViString("CALC1:PAR:SEL 'ch1_S31'\n"));
    viPrintf (m_vi, ViString("CALC1:DATA? SDATA\n"));

    viScanf (m_vi, ViString("%t"), m_buffer);

    return QString(m_buffer);
}

QString RS_VNAdapter::collect_S33()
{
    /// 选定迹线S33
    //   viPrintf(m_vi, "*OPC?\n");
    viPrintf(m_vi, ViString("INIT1:IMM\n"));
    viPrintf(m_vi, ViString("*OPC?\n"));
    viScanf (m_vi, ViString("%t"), m_buffer);

    /// 采集数据
    viPrintf (m_vi, ViString("CALC1:PAR:SEL 'ch1_S33'\n"));
    viPrintf (m_vi, ViString("CALC1:DATA? SDATA\n"));
    viScanf (m_vi, ViString("%t"), m_buffer);

    return QString(m_buffer);
}
