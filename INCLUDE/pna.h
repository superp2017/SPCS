#ifndef PNA_H
#define PNA_H

#include "PNA_global.h"
#include <string>
#include <list>
#include <visa.h>
#include "commandcenter.h"
using namespace std;

class PNASHARED_EXPORT PNA
{
public:
    /*!
     * \brief PNA 每个实例代表一台矢量网络分析仪（简称“矢网”）
     * \param _ip 每个矢量分析仪必须有一个ip
     */
    PNA(string _ip);
    /*!
     * \brief status 查询矢网的连接状态
     * \return true连接，false：断开
     */
    bool status();
    /*!
     * \brief connect 连接到矢网
     * \return true：连接成功，false：连接失败
     */
    bool connect();
    /*!
     * \brief disConnect 断开连接
     * \return 返回连接状态，true：连接，false
     */
    bool disConnect();
    /*!
     * \brief heartBeat 由用户定时调用，测试连接状态
     * \return 返回连接状态，true：连接，false
     */
    bool heartBeat();

    virtual ~PNA();
    /*!
     * \brief execSCPI 执行SCPI命令
     * \param _cmd  SCPI命令
     * \param _result 输出的执行结构
     * \param _record 指示是否记录该命令，true：记录，false：不记录
     * \return 返回执行情况，true：执行成功，false：执行失败
     */
    bool execSCPI(string _cmd,string& _result,bool _record);

    /*!
     * \brief getCmdHistory 获取命令执行历史
     * \return
     */
    virtual const list<string> getCmdHistory();

    virtual bool createMeasure(CommandCenter& _cmdCenter,string _mname,string _param,string _cnum=0);
    virtual bool dispMeasure(CommandCenter& _cmdCenter,string _mname,string _wnum=0,string _tnum=0);
    virtual bool delAllMeasure(CommandCenter& _cmdCenter,string _cnum);
    virtual bool setSweepType(CommandCenter& _cmdCenter,string _cnum,string _type);
    virtual bool setSweepPointNum(CommandCenter& _cmdCenter,string _cnum,string _pointnum);
    virtual bool setStartFreq(CommandCenter& _cmdCenter,string _cnum,string _freq);
    virtual bool setStopFreq(CommandCenter& _cmdCenter,string _cnum,string _freq);

protected:
    /*!
     * \brief m_cmdHistory 记录执行的历史命令
     */
    list<string> m_cmdHistory;
    /*!
     * \brief m_defaultRM,m_vi 用于与VISA通讯的session对象
     */
    ViSession m_defaultRM,m_vi;
    /*!
     * \brief m_ip 矢网的ip地址，这里必须指定ip，这里所有与pna通讯均使用TCPIP协议
     */
    string m_ip;
    /*!
     * \brief m_connected 记录与矢网的连接状态。true：连接，false：未连接
     */
    bool m_connected;
};

#endif // PNA_H
