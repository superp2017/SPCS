#include "calibrationmp.h"
#include <QSettings>
#include <QStringList>
#include <QString>
#include <QFile>

CalibrationMP::CalibrationMP(QObject *parent) :
    QObject(parent)
{
}

double CalibrationMP::get_mag(QString &freq, size_t id)
{
    double m1 = 0;
    if(m_M2[freq].size() >= id)
    {
        m1 = m_M2[freq][id-1];
    }

    return m1;
}

double CalibrationMP::get_phase(QString &freq, size_t id)
{
    double p1 = 0;
    if(m_P2[freq].size() >= id)
    {
        p1 = m_P2[freq][id-1];
    }

    return p1;
}

void CalibrationMP::calibration_path(QString path)
{
    m_path = path;
    QSettings sets(path + "/FreqList.freq", QSettings::IniFormat);
    sets.beginGroup("frequency");
    QStringList list = sets.value("f").toString().trimmed().split(QRegExp(QChar(',')));
    QStringList::iterator iter = list.begin();
    while(iter != list.end())
    {
        load_M(*iter, "M2_", m_M2);
        load_P(*iter, "P2_", m_P2);
        iter++;
    }
}


void CalibrationMP::load_M(QString &freq, const QString &prefix, std::map<QString, std::vector<double> > &value)
{
    QFile file(m_path + prefix + freq + ".dat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        value[freq].push_back(QString(line).trimmed().toDouble());
    }
}

void CalibrationMP::load_P(QString &freq, const QString &prefix, std::map<QString, std::vector<double> > &value)
{
    QFile file(m_path + prefix + freq + ".dat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        value[freq].push_back(QString(line).trimmed().toDouble());
    }
}
