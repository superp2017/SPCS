#ifndef TRWAVECONTROL_H
#define TRWAVECONTROL_H

#include "TRWaveControl_global.h"
#include "pclient.h"
#include "parseconfig.h"

class TRWAVECONTROLSHARED_EXPORT TRWaveControl: public QObject
{
    Q_OBJECT
protected:
    TRWaveControl(QObject *parent =0);
    ~TRWaveControl();
  public:
    static  TRWaveControl* instance()
    {
        static TRWaveControl *con = new TRWaveControl;
        return con;
    }
    static void destory()
    {
        delete instance();
    }
public slots:
    bool udpConnectTest();
    bool AntenaInit(bool isSent);
    bool DownPower();
    bool setMagnPhase_ID(int id, double m, double p, bool status, TRontrol *p_TR = 0);
    bool setMagnPhase(TRontrol &p_TR,int row, int col,bool issent = false, \
                      double m_r = 0, double p_r=0, double m_s =0, double p_s = 0);
    void init_arrayID(std::map<int, std::pair<short, short> > &map);

protected:
    bool TRControl();
    void TransData(double magn, double phase, int &p_m, int &p_p);
    bool CheckData(uchar *data);
    bool __udpConnectTest(uchar *p_package);
    bool __AntenaInit(uchar *p_package);
    bool __SwitchContrl(uchar *p_package);
    bool __Antenna_data(uchar *p_package);
    bool __DownPower(uchar *p_package);
    bool __TRControl(uchar *p_package);
private:
    ParseConfig                                    m_config;
    std::map<int,std::pair<qint8,qint8> >          m_id_map;
    TRontrol                                       m_TR_Buf;
    uchar *                                        m_rec_data;
    PACKAGE                                        m_data;
    PClient                                        m_client;
};

#endif // TRWAVECONTROL_H
