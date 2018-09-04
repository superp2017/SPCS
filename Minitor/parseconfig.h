#ifndef PARSECONFIG_H
#define PARSECONFIG_H

#include <QHostAddress>

#define CONFIGPATH      "./config/LocalHost.cfg"

class ParseConfig
{
public:
    ParseConfig();

    QHostAddress& getServIp()          {return m_servIp;}
    quint16       getServPort()        {return m_servPort;}

    QHostAddress& getClientIp()          {return m_clientIp;}
    quint16       getClientPort()        {return m_clientPort;}

private:
    QHostAddress  m_servIp;
    quint16       m_servPort;
    QHostAddress  m_clientIp;
    quint16       m_clientPort;
};

#endif // PARSECONFIG_H
