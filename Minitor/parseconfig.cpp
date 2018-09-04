#include "parseconfig.h"
#include <QSettings>

ParseConfig::ParseConfig()
{
    QSettings settings(CONFIGPATH,QSettings::IniFormat);
    settings.beginGroup("SERVER");
    m_servIp     = QHostAddress(settings.value("ip").toString());
    m_servPort   = settings.value("port").toString().toInt();   
    settings.endGroup();    
    settings.beginGroup("CLIENT");
    m_clientIp     = QHostAddress(settings.value("ip").toString());
    m_clientPort   = settings.value("port").toString().toInt();
    settings.endGroup();
}
