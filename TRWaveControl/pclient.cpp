#include "pclient.h"
#include <QDataStream>
#include "parseconfig.h"
#include <QDebug>

PClient::PClient(QHostAddress servIp, quint16 servPort,QHostAddress clientIp, quint16 clentPort, QWidget *parent) :
    QWidget(parent),
    m_servIpAddr(servIp),
    m_servPort(servPort),
    m_clientpAddr(clientIp),
    m_clientPort(clentPort)
{
}

void PClient::init()
{
    m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(m_clientpAddr,m_clientPort);

}

void PClient::WriteData(PACKAGE *meg,uchar *recivedata,double waittime)
{
    m_udpSocket->writeDatagram(reinterpret_cast< const char *>(meg->t_pack), PACKAGE_NUMS,m_servIpAddr,m_servPort);
    if(m_udpSocket->waitForReadyRead(waittime))
    {
        m_udpSocket->readDatagram((char*)recivedata, PACKAGE_NUMS);
    }
    else
    {
        qDebug() << "WaveControl Wait for read timeout ...";
        recivedata = 0;
    }
}

