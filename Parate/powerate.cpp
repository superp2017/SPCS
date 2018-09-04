#include "powerate.h"
#include <QFile>
#include <QDebug>
#include <QStringList>

Powerate::Powerate(const QString &file,QObject *parent) :
    QObject(parent)
{
    parse(file);
}

double Powerate::get_avg()
{
    double sum = 0;
    int n = 0;
    std::map<QString, QString>::iterator iter = m_freq_mag.begin();
    while(iter != m_freq_mag.end())
    {
        sum += iter->second.toDouble();
        n++;
        iter++;
    }
    return sum / n;
}

void Powerate::parse(const QString &file)
{
    QFile ls_file(file);

    if (!ls_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int i = 0;
    while (i < 9 && !ls_file.atEnd()) {
        ls_file.readLine();
        i++;
    }

    while(!ls_file.atEnd())
    {
        QByteArray bry = ls_file.readLine();
        QString str(bry);
        QStringList list = str.split(QRegExp(QChar(' ')));
        if(list.size() != 9) continue;
        m_freq_mag[list.at(0)]= list.at(3);
    }
}
