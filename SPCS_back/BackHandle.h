#ifndef BACKHANDLE_H
#define BACKHANDLE_H

#include <QObject>
#include "_global.h"
#include "radar.h"
#include <QStringList>
#include "taskcenter_607.h"
#include "testresult.h"
#include "radaranaly.h"
#include <map>
using namespace CVTS;

/*!
 * \brief The BackHandle class
 * �������������
 */
class BackHandle : public QObject
{
    Q_OBJECT
protected:
    BackHandle(QObject *parent = 0);
    ~BackHandle();
public:
    static BackHandle* instance()
    {
        static BackHandle *bh = new BackHandle();
        return bh;
    }

    static void destory()
    {
        delete instance();
    }

signals:
    void add_item(std::vector<QString>);

public slots:
    void DATA_Manage(TDATA &p_org_data, \
                     std::map<int,TDATA> &p_cfg_mp_data,\
                     std::map<int,TDATA> &p_cfg_m_mp_data,\
                     Task_Cmp &p_final_cfg, \
                     std::vector<int> &p_id, \
                     std::vector<QString> &p_freq, \
                     std::map<int, Radar *> &p_radars);
protected slots:
    void HandleData();
protected:
    void   clean();
    void   manager();
    double getMagn(QString pStr);
    double getPhase(QString pStr);
    double genMagn(double real, double imag);
    double genPhase(double real, double imag);

    void   dataAnaly_org(TDATA &tData,H_ORG &p_org);
    void   dataAnaly_cfg_mp(std::map<int, TDATA> &tData,H_CFG_MP &t_cfg_mp);
    void   dataAnaly_cfg_final(Task_Cmp &tData,H_CFG_FINAL &t_cfg_final);
    void   analy(TDATA &tData,H_ORG &p_org,QString type);
private:

    std::vector<int>         m_id;
    std::vector<QString>     m_freq;
    std::map<int, Radar *>   m_radars;

    std::map<int, TDATA>     m_cfg_mp_data;  //������λһ��
    std::map<int, TDATA>     m_cfg_m_mp_data;//�ȷ�����
    TDATA                    m_org_data;  //ԭʼ����
    Task_Cmp                 m_final_cfg;  //���յ�У׼ֵ

    H_ORG                    m_org;      //ԭʼ���ݣ�ת����
    H_CFG_MP                 m_cfg_mp;   //������λһ��ת����
    H_CFG_MP                 m_cfg_m_mp; //�ȷ����ࣨת����
    H_CFG_FINAL              m_cfg_final; //���յ�У׼ֵ��ת����
};

#endif // BACKHANDLE_H





