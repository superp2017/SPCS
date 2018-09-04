#include "env_config.h"
#include "_global.h"
#include <QSettings>
#include <QString>
#include <QDebug>

ENV_config::ENV_config(QObject *parent) :
    QObject(parent)
{
    init();
}

void ENV_config::init()
{
    QSettings sets(ENV_config_path, QSettings::IniFormat);
    sets.beginGroup("Aglient");
    m_Aglient_ip = sets.value("ip").toString();
    sets.endGroup();

    sets.beginGroup("R&S");
    m_rs_ip = sets.value("ip").toString();
    sets.endGroup();

    sets.beginGroup ("Collect");
    m_collect_s11 = sets.value ("collect_s11").toString() == QString("true");
    sets.endGroup();


    sets.beginGroup ("CAL");
    m_real_cal = sets.value ("real_cal").toString()== QString("true");
    sets.endGroup();

}
