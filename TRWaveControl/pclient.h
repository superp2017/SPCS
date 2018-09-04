#ifndef PCLIENT_H
#define PCLIENT_H

#include <QWidget>
#include <QUdpSocket>
#include <QHostAddress>
#include "TRWaveControl_global.h"


class PClient : public QWidget
{
    Q_OBJECT
public:
    PClient(QHostAddress servIp, quint16 servPort, QHostAddress clientIp, quint16 clentPort, QWidget *parent = 0);
    void init();
private:
    QUdpSocket          *m_udpSocket;
    QHostAddress         m_servIpAddr;
    quint16              m_servPort;
    QHostAddress         m_clientpAddr;
    quint16              m_clientPort;

public:
    void setServIp(QHostAddress &servIp)       {m_servIpAddr = servIp;}
    QHostAddress &curSendIp()                  {return m_servIpAddr;}
    void setServPort(quint16 servPort)         {m_servPort = servPort;}
    quint16 &curSendPort()                     {return m_servPort;}

public slots:
    void  WriteData(PACKAGE *meg, uchar *recivedata = 0, double waittime = 0);

private:
    PACKAGE data;

};

#endif // PCLIENT_H





