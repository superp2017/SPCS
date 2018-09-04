#include "env_config.h"
#include "_global.h"
#include <QSettings>
#include <QString>
#include <QDebug>
#include <QStringList>

ENV_config::ENV_config(QObject *parent) :
    QObject(parent)
{
    init();
}

void ENV_config::init()
{
    QSettings set1(ENV_config_path, QSettings::IniFormat);
    set1.beginGroup("Aglient");
    m_Aglient_ip = set1.value("ip").toString();
    set1.endGroup();

    set1.beginGroup("R&S");
    m_rs_ip = set1.value("ip").toString();
    set1.endGroup();

    set1.beginGroup ("Collect");
    m_collect_s11 = set1.value ("collect_s11").toString() == QString("true");
    set1.endGroup();


    set1.beginGroup ("CAL");
    m_real_cal = set1.value ("real_cal").toString()== QString("true");
    set1.endGroup();

    QSettings set2(FLOW_CONFIG, QSettings::IniFormat);
    set2.beginGroup("FLOW");
    m_enable_single_decrot_test= set2.value("EnableSingleDectorTest")== QString("true");
    m_single_dector = set2.value("SingleDec").toInt();
    set2.endGroup();
}
