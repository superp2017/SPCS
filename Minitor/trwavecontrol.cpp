#include "trwavecontrol.h"
#include <QDebug>

/*初始化包头*/
#define PACKAGE_HEAD(type) \
    m_data.t_pack[0] = 0x55;\
    m_data.t_pack[1] = 0xaa; \
    m_data.t_pack[2] = type;

/*初始化包尾*/
#define PACKAGE_TAIL  m_data.t_pack[17] = check;\
    m_data.t_pack[18] = 0xff; \
    m_data.t_pack[19] = 0xff;\
    m_client.WriteData(&m_data,m_rec_data,DELATYTIME);\
    return CheckData(m_rec_data);

/*包中数据备份*/
#define BACKUP(a,b)     for(int i = 0; i < a; ++i)\
{m_data.t_pack[i + b] = 0;}

/*包中数据校验*/
#define CHECK(a)    char check = m_data.t_pack[0];\
    for(int i = 1; i<= a; ++i)\
{check ^= m_data.t_pack[i];}



TRWaveControl::TRWaveControl(QObject *parent):
    QObject(parent),
    m_config(),
    m_client(m_config.getServIp(), m_config.getServPort(),m_config.getClientIp(),m_config.getClientPort())
{
    m_rec_data = new uchar[PACKAGE_NUMS];
    m_client.init();
}

TRWaveControl::~TRWaveControl()
{
    delete []m_rec_data ;
}

void TRWaveControl::init_arrayID(std::map<int, std::pair<short, short> > &map)
{
    std::map<int, std::pair<short, short> > ::iterator iter = map.begin();
    while(iter != map.end())
    {
        m_id_map[iter->first] = std::pair<qint8,qint8>((qint8)(iter->second.first),(qint8)(iter->second.second)) ;
        ++iter;
    }
}


bool TRWaveControl::udpConnectTest()
{
    PACKAGE_HEAD(UDPTEST);
    for(int i = 0; i < 14; ++i)
    {
        m_data.t_pack[i + 3] = i+1;
    }
    CHECK(16);
    PACKAGE_TAIL;
}

bool TRWaveControl::AntenaInit(bool isSent)
{
    PACKAGE_HEAD(ANTE_INIT);

    if(isSent)
        m_data.t_pack[3] = 0x1;
    else
        m_data.t_pack[3] = 0x0;

    BACKUP(13,4);
    CHECK(16);
    PACKAGE_TAIL;
}

bool TRWaveControl::DownPower()
{
    PACKAGE_HEAD(DOWN_POWER);
    BACKUP(14,3);
    CHECK(16);
    PACKAGE_TAIL;
}

bool TRWaveControl::TRControl()
{
    PACKAGE_HEAD(MAGNPHASE_C);
    if(m_TR_Buf.t_status)
    {
        if( m_TR_Buf.t_row == 0 || m_TR_Buf.t_col == 0)
            return false;
    }

    m_data.t_pack[3]   = m_TR_Buf.t_row      & 0xFF;
    m_data.t_pack[4]   = m_TR_Buf.t_col      & 0xFF;
    m_data.t_pack[5]   = m_TR_Buf.t_magn_s   & 0xFF;
    m_data.t_pack[6]   = m_TR_Buf.t_phase_s  & 0xFF;
    m_data.t_pack[7]   = m_TR_Buf.t_magn_r   & 0xFF;
    m_data.t_pack[8]   = m_TR_Buf.t_phase_r  & 0xFF;

    if(m_TR_Buf.t_status)
    {
        m_data.t_pack[9]    = 1  & 0xFF;
        m_data.t_pack[10]   = 3  & 0xFF;
    }
    else
    {
        m_data.t_pack[9]    = 0  & 0xFF;
        m_data.t_pack[10]   = 12 & 0xFF;
    }

    m_data.t_pack[11] = 0;
    m_data.t_pack[12] = 0;
    m_data.t_pack[13] = 0;
    m_data.t_pack[14] = 0;
    m_data.t_pack[15] = 0;
    m_data.t_pack[16] = 0;

    CHECK(16);
    PACKAGE_TAIL;
}

void TRWaveControl::TransData(double magn, double phase, int &p_m, int &p_p)
{
    double ls_m = 0; double ls_p =0;
    p_m = 0;
    p_p = 0;
    int m_index = 0;
    int p_index =0;
    double ls_phase = phase;
    for(int i =0;i<64;++i)
    {
        if(magn >32)
            m_index = 31;
        else
        {
            if(magn == ls_m)
                m_index = i;
            else if(magn>ls_m && magn<(ls_m +0.5))
            {
                if(abs(magn - ls_m) > abs(magn-ls_m-0.5))
                    m_index = i+1;
                else
                    m_index = i;
            }
        }
        ///////////////// 2014/4/9 mp
        if(ls_phase<0) ls_phase += 360;
        ///////////////////

        if(ls_phase > 360)
            p_index = 63;
        else
        {
            if (ls_phase == ls_p)
                p_index = i;
            else if(ls_phase>ls_p && ls_phase<(ls_p +5.625))
            {
                if(abs(ls_phase - ls_p) > abs(ls_phase-ls_p-5.625))
                    p_index = i+1;
                else
                    p_index = i;
            }
        }

        ls_m += 0.5;
        ls_p += 5.625;
    }

    if(m_index ==64)
        p_m = 0;
    else
        p_m = m_index;

    if(p_index == 64)
        p_p = 0;
    else
        p_p = p_index;
}
bool TRWaveControl::setMagnPhase_ID(int id, double m, double p, bool status, TRontrol *p_TR )
{
    m_TR_Buf.t_row     =  m_id_map[id].first;
    m_TR_Buf.t_col     =  m_id_map[id].second;
    m_TR_Buf.t_magn_s  =  0;
    m_TR_Buf.t_magn_r  =  0;
    m_TR_Buf.t_phase_s =  0;
    m_TR_Buf.t_phase_r =  0;

    int ls_magn = 0;
    int ls_phase =0;
    TransData(m,p,ls_magn,ls_phase);

    if(status)
    {
        m_TR_Buf.t_magn_s  = ls_magn;
        m_TR_Buf.t_phase_s = ls_phase;
    }else
    {
        m_TR_Buf.t_magn_r  =  ls_magn;
        m_TR_Buf.t_phase_r =  ls_phase;
    }
    m_TR_Buf.t_status      =  status;

    bool ret =  TRControl();
    if(p_TR)
    {
        p_TR->t_col     = m_TR_Buf.t_col;
        p_TR->t_row     = m_TR_Buf.t_row;
        p_TR->t_magn_r  = m_TR_Buf.t_magn_r;
        p_TR->t_magn_s  = m_TR_Buf.t_magn_s;
        p_TR->t_phase_r = m_TR_Buf.t_phase_r;
        p_TR->t_phase_s = m_TR_Buf.t_phase_s;
        p_TR->t_status  = m_TR_Buf.t_status;
    }
    return ret;
}

bool TRWaveControl::setMagnPhase(TRontrol &p_TR,int row, int col, bool issent, double m_r, double p_r, double m_s, double p_s)
{
    if(issent)
    {
        if(row ==0 || col == 0)
            return false;
    }

    m_TR_Buf.t_row     = row;
    m_TR_Buf.t_col     = col;
    int ls_magn = 0;
    int ls_phase =0;
    TransData(m_s,p_s,ls_magn,ls_phase);
    m_TR_Buf.t_magn_s  = ls_magn;
    m_TR_Buf.t_phase_s = ls_phase;
    TransData(m_r,p_r,ls_magn,ls_phase);
    m_TR_Buf.t_magn_r  = ls_magn;
    m_TR_Buf.t_phase_r = ls_phase;
    m_TR_Buf.t_status  = issent;

    bool ret =  TRControl();
    p_TR = m_TR_Buf;
    return ret;
}



bool TRWaveControl::CheckData(uchar *data)
{
    if(data[0] != HEAD_1 || data[1] != HEAD_2)                              //检查包头
    {
        qDebug() << "package head error";
        return false;
    }
    if(data[18] != TAIL_1 || data[19] != TAIL_2)                            //检查包尾
    {
        qDebug() << "package tail error";
        return false;
    }
    char type = data[2];                                                    //返回类型
    switch(type)
    {
    case UDPTEST:                                                                                   //UDP链接测试状态字
        return __udpConnectTest(data);
        break;
    case ANTE_INIT:                                                                                 //天线初始化状态字
        return __AntenaInit(data);
        break;
    case DOWN_POWER:                                                                                //下电处理状态字
        return __DownPower(data);
        break;
    case MAGNPHASE_C:                                                                                //幅度相位控制状态字
        return  __TRControl(data);
        break;
    default:
        qDebug() << "ReciveData data error";
        return false;
        break;
    }
    return false;
}

bool TRWaveControl::__udpConnectTest(uchar *p_package)
{
    uchar check = p_package[0];
    for(int i = 1; i<= 16; ++i)
    {
        check ^= p_package[i];
    }

    return p_package[17] == check;
}

bool TRWaveControl::__AntenaInit(uchar *p_package)
{
    uchar check = p_package[0];
    for(int i = 1; i<= 16; ++i)
    {
        check ^= p_package[i];
    }
    if(p_package[17] == check)
    {
        return p_package[4] == 0;
    }
    else
    {
        return false;
        qDebug() << "AntenaInit check error";
    }
}


bool TRWaveControl::__DownPower(uchar *p_package)
{
    uchar check = p_package[0];
    for(int i = 1; i<= 16; ++i)
    {
        check ^= p_package[i];
    }
    if(p_package[17] == check)
    {
        return  p_package[3] == 0;
    }
    else
    {
        return false;
        qDebug() << "DownPower check error";
    }
}

bool TRWaveControl::__TRControl(uchar *p_package)
{
    uchar check = p_package[0];
    m_TR_Buf.t_row      = (qint8)(p_package[3]); //通道行号
    m_TR_Buf.t_col      = (qint8)(p_package[4]); //通道列号
    m_TR_Buf.t_magn_s   = (qint8)(p_package[5]); //
    m_TR_Buf.t_phase_s  = (qint8)(p_package[6]);

    m_TR_Buf.t_magn_r    = (qint8)(p_package[7]);
    m_TR_Buf.t_phase_r   = (qint8)(p_package[8]);

    m_TR_Buf.t_status = p_package[9] == 12 ? true:false;

    for(int i = 1; i <= 16; ++i)
    {
        check ^= p_package[i];
    }
    if(p_package[17] == check)
    {
        return p_package[16] == 0;
    }
    else
    {
        return false;
        qDebug() << "TRContrl check error";
    }
}
