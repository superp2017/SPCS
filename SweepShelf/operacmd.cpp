#include "operacmd.h"
#include "Windows.h"
#include <stdio.h>
#include <iostream>
#include <QDebug>
#include <QSettings>
#include <QApplication>
#include <QStringList>
#include <QDebug>

OperaCmd::OperaCmd()
{
    initdata();
}
void OperaCmd::initdata()
{
    m_effic.clear();
    m_segment_point.clear();

    QString file = QApplication::applicationDirPath() + "/config/sweepshelf.precision";
    QSettings iniSets(file, QSettings::IniFormat);
    iniSets.beginGroup("Precision");

    QStringList list = iniSets.allKeys();
    QStringList::iterator iter = list.begin();
    while(iter != list.end())
    {
        int key = (*iter).toInt();
        double value = iniSets.value(*iter).toString().toDouble();
        m_segment_point.push_back(key);
        m_effic[key] = value;
        iter++;
    }
    iniSets.endGroup();

}

bool OperaCmd::S_OpenCOM(QString com)
{
    return m_SerialPort.f_OpenSerialPort(com);
}

void OperaCmd::S_CloseCOM()
{
    m_SerialPort.f_CloseSerialPort();
}

/*************************************************************************
�������ƣ�S_serveon
�������ͣ���
�������ͣ��ŷ���������1�����򷵻�0
�����������ŷ�����
�޸����ڣ�201402
**************************************************************************/

void OperaCmd::S_serveon()
{
    // const char*   setP3_06 = "0106030C00F8";
    // const char*   setP4_07 = "0106040E00E0";
    char  setP3_06[] = {'0','1','0','6','0','3','0','C','0','0','F','8'};
    char  setP4_07[] = {'0','1','0','6','0','4','0','E','0','0','E','0'};

    m_SerialPort.f_Send(setP3_06,sizeof(setP3_06));
    m_SerialPort.f_Send(setP4_07,sizeof(setP4_07));

}

/*************************************************************************
�������ƣ�S_serveoff
�������ͣ���
�������ͣ��ŷ�ֹͣ����1�����򷵻�0
����������ֹͣ�ŷ�
�޸����ڣ�201402
**************************************************************************/

void OperaCmd::S_serveoff()
{
    // char  *setP4_07 = "0106040E00C0";
    char setP4_07[] = {'0','1','0','6','0','4','0','E','0','0','C','0'};

    m_SerialPort.f_Send(setP4_07,sizeof(setP4_07));
}

/*************************************************************************
�������ƣ�S_position
�������ͣ���
�������ͣ�double
����������λ�ü���������̽ͷ������λ��
�޸����ڣ�201402
**************************************************************************/

double OperaCmd::S_position()
{
    // const char*  setP0_09 = "010300120002";
    char setP0_09[] = {'0','1','0','3','0','0','1','2','0','0','0','2'};
    double posistion =0;
    m_SerialPort.f_Send(setP0_09,sizeof(setP0_09));
    ::Sleep(20);
    uchar * ls_readbuffer=0;
    //  int ls_bufsize = m_SerialPort.f_GetReadbuffer(ls_readbuffer);
    int ls_bufsize = m_SerialPort.get_readbuf(ls_readbuffer);
    // if(ls_bufsize >= 6)
    //  {
    posistion = ls_readbuffer[5] * 65536 * 256/4000.000    + \
            ls_readbuffer[6] * 65536 / 4000.000     + \
            ls_readbuffer[3] * 256   / 4000.000     + \
            ls_readbuffer[4] / 4000.000;
    // }
    // else
    //    return NOPOSITION;
    return posistion;
}

/*************************************************************************
�������ƣ�M_origin
�������ͣ���
�������ͣ�bool
������������ԭ��,���ԭ��P4-07��Ϊ00E8����ú����޷�����
�޸����ڣ�201402
**************************************************************************/

bool OperaCmd::M_origin()
{
    // const char*  setP4_07   = "0106040E00E8";
    // const char*  resetP4_07 = "0106040E00E0";

    char setP4_07[] = {'0','1','0','6','0','4','0','E','0','0','E','8'};
    char resetP4_07[] = {'0','1','0','6','0','4','0','E','0','0','E','0'};

    m_SerialPort.f_Send(setP4_07,sizeof(setP4_07));
    ::Sleep(10);

    m_SerialPort.f_Send(resetP4_07,sizeof(resetP4_07));
    ::Sleep(10);
    return true;
}

/*************************************************************************
�������ƣ�S_movedone
�������ͣ���
�������ͣ�bool
���������������������ŷ�������ͨѶ�������ŷ�״̬������¿��Բ鿴�˶��Ƿ�
        λ����λ����ture������λ����·æ��ʱ�޷���ѯ����false
�޸����ڣ�201402
**************************************************************************/

bool OperaCmd::S_movedone()
{
    //  const char *  readP5_07 = "0103050E0002";
    char readP5_07[] = {'0','1','0','3','0','5','0','E','0','0','0','2'};
    uchar * ls_readbuffer =0;
    //int ls_bufsize = m_SerialPort.f_GetReadbuffer(ls_readbuffer);

    int ls_bufsize = m_SerialPort.get_readbuf(ls_readbuffer);
    m_SerialPort.f_Send(readP5_07,12);

    if(ls_bufsize >= 4)
    {
        return ((ls_readbuffer[3] * 256 + ls_readbuffer[4]) > 20000) || ((ls_readbuffer[3] * 256 + ls_readbuffer[4]) == 1000);
    }
    return false;
}

/*************************************************************************
�������ƣ�M_move
�������ͣ�˫��������λ��
�������ͣ�uchar
���������������������Ӧ�ٶ��˶������������Ӧ����
�޸����ڣ�201402
**************************************************************************/

bool OperaCmd::M_move(double distance)
{
    if(distance >750||distance<-750) return false;

    double curP = S_position();

    long  position = S_Calc_PUU(curP,distance);
    if(position== 123456)
        position =  (long) 4000*distance;
    else
        position += curP*4000.0;
    //���´��뽫һ����ֵ���˴�Ϊposition����ʮ�����Ʊ�ʾ���ٽ�ʮ��
    //���Ʊ�Ϊ����8λ�й����ַ��������ǰ4�����4��λ�ý����õ�
    //�й����ַ���p3���������趨��ַ�ȴ˴��õ�setP6_05��


    char pn[]  = {'0','1','1','0','0','6','0','A','0','0','0','2','0','4'};
    char cmd[] = {'0','1','0','6','0','5','0','E','0','0','0','2'};

    char tmp[8] = {0};

    QString pdata = QString::number(position, 16);
    while(pdata.size() < 8)
    {
        pdata = QString('0') + pdata;
    }

    if(pdata.size()>8)
        memcpy(tmp, pdata.toLocal8Bit().data()+8, 8);
    else
        memcpy(tmp, pdata.toLocal8Bit().data(), 8);

    char tmp3[8] = {0};
    memcpy(tmp3, tmp+4, 4);
    memcpy(tmp3 + 4, tmp, 4);

    int ls_len = sizeof(pn) + sizeof(tmp3);
    uchar ls_data[22] = {0};
    memcpy(ls_data,pn,sizeof(pn));
    memcpy(ls_data+14,tmp3,sizeof(tmp3));

    m_SerialPort.f_Send(reinterpret_cast<char *>(ls_data),ls_len);

    ::Sleep(10);

    m_SerialPort.f_Send(cmd,sizeof(cmd));

    ::Sleep(10);

    return true;
}

void OperaCmd::S_SetMoveSpeed(MOVESPEESD speed)
{
    char  m_vvcc_less100[]     = {'0','1','1','0','0','6','0','8','0','0','0','2','0','4','0','0','0','2','0','0','0','2'};
    char  m_vvcc_100to299[]    = {'0','1','1','0','0','6','0','8','0','0','0','2','0','4','2','2','0','2','0','0','0','3'};
    char  m_vvcc_300to499[]    = {'0','1','1','0','0','6','0','8','0','0','0','2','0','4','4','4','0','2','0','0','0','4'};
    char  m_vvcc_500to999[]    = {'0','1','1','0','0','6','0','8','0','0','0','2','0','4','6','6','0','2','0','0','0','5'};
    char  m_vvcc_1000to1499[]  = {'0','1','1','0','0','6','0','8','0','0','0','2','0','4','8','8','0','2','0','0','0','7'};
    char  m_vvcc_more1500[]    = {'0','1','1','0','0','6','0','8','0','0','0','2','0','4','9','9','0','2','0','0','0','9'};
    if(speed == SPEED_0_100)
    {
        m_SerialPort.f_Send(m_vvcc_less100,sizeof(m_vvcc_less100));
    }
    if(speed == SPEED_100_300)
    {
        m_SerialPort.f_Send(m_vvcc_100to299,sizeof(m_vvcc_100to299));
    }
    if(speed == SPEED_300_500)
    {
        m_SerialPort.f_Send(m_vvcc_300to499,sizeof(m_vvcc_300to499));
    }
    if(speed == SPEED_500_1000)
    {
        m_SerialPort.f_Send(m_vvcc_500to999,sizeof(m_vvcc_500to999));
    }
    if(speed == SPEED_1000_1500)
    {
        m_SerialPort.f_Send(m_vvcc_1000to1499,sizeof(m_vvcc_1000to1499));
    }
    if(speed == SPEED_1500_)
    {
        m_SerialPort.f_Send(m_vvcc_more1500,sizeof(m_vvcc_more1500));
    }
}

double OperaCmd::S_Calc_PUU(double curp, double dis)
{
    if(curp > 750 || curp < -750 || dis > 750 || dis < -750) return 123456;
    int index_c = 0;
    int index_d = 0;
    double puu = 0;
    for(size_t i =0;i<m_segment_point.size();++i)
    {
        if(curp == 750)
            index_c = 0;
        else
        {
            if(m_segment_point.at(i)+100 > curp )
                index_c  = i;
        }
        if(dis == 750)
            index_c  = 0;
        else
        {
            if(m_segment_point.at(i)+100 > dis)
                index_d  = i;
        }
    }

    if(index_c == index_d)
    {
        puu += (dis -curp)*4000 / m_effic[m_segment_point.at(index_c)];
    }
    else
    {
        int start =0;
        int end   = 0;
        if(index_c < index_d)
        {
            start = index_d-1;
            end = index_c;

            puu +=  (m_segment_point.at(index_c)-curp)*4000/m_effic[m_segment_point.at(index_c)];
            for(int i =start ;i >end ;--i)
            {
                puu += (m_segment_point.at(i)-m_segment_point.at(i-1))*4000/ m_effic[m_segment_point.at(i)];
            }
            puu +=  (dis-m_segment_point.at(index_d -1)) *4000/ m_effic[m_segment_point.at(index_d)];
        }
        if(index_d < index_c)
        {
            start = index_d ;
            end = index_c -1;
            puu += (m_segment_point.at(index_c-1)-curp)*4000/m_effic[m_segment_point.at(index_c)];
            for(int i =start ;i <end ;++i)
            {

                puu += (m_segment_point.at(i)-m_segment_point.at(i+1))*4000/ m_effic[m_segment_point.at(i+1)];
            }
            puu += (dis - m_segment_point.at(index_d)) *4000/ m_effic[m_segment_point.at(index_d)];
        }
    }
    return  puu;
}



/*************************************************************************
�������ƣ�S_clearwarn
�������ͣ���
�������ͣ�bool
�����������������
�޸����ڣ�201402
**************************************************************************/

void OperaCmd::S_clearwarn()
{
    //   char * setP4_07 = "0106040E00E0";
    //   char * resetP4_07 = "0106040E00F0";

    char setP4_07[]   = {'0','1','0','6','0','4','0','E','0','0','E','0'};
    char resetP4_07[] = {'0','1','0','6','0','4','0','E','0','0','F','0'};

    m_SerialPort.f_Send(setP4_07,sizeof(setP4_07));

    m_SerialPort.f_Send(resetP4_07,sizeof(resetP4_07));
}
