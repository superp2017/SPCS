#include "niparser.h"
#include "_global.h"
#include <QFile>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <qmath.h>


using namespace  std;
NIParser::NIParser(QObject *parent) :
    QObject(parent)
{
    parse(NI_DATA);
}

void NIParser::parse(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    if(!file.atEnd())
    {
        QByteArray line = file.readLine();
        sscanf(QString(line).toLocal8Bit().data(), "N=%d,%d I=%f,%f,%d S=%d,%d", \
               &m_N, &m_N_num, &m_I, &m_I_step, &m_I_num, &m_S_min, &m_S_max);
    }

    int N=0;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QStringList list = QString(line).trimmed().split(QRegExp(QChar(' ')));
        if(list.size() != m_N) continue;
        for(int i=0; i<m_N; i++)
        {
            m_mmd[N][i] = list.at(i).toFloat();
        }
        N++;
    }
}

vector<vector<complex<double> > >& NIParser::get_S1()
{
    if(m_res_S1.size() > 0) return m_res_S1;
    for(int i_ = 0;i_ < m_N_num;++i_)
    {
        vector<complex<double>> row_;
        for(int j_ = 0;j_ < m_N;++j_)
        {
            complex<double> cell_;
            cell_.real(cos(2 * M_PI * m_mmd[i_][j_] / (m_N_num+1)));
            cell_.imag(sin(2 * M_PI * m_mmd[i_][j_] / (m_N_num+1)));
            row_.push_back(cell_);
        }
        m_res_S1.push_back(row_);
    }
    return m_res_S1;

}

std::vector<std::vector<std::complex<double> > >& NIParser::get_S2()
{
    if(m_res_S2.size() > 0) return m_res_S2;
    for(int i_ = 0;i_ < m_N_num;++i_)
    {
        vector<complex<double>> row_;

        for(int j_ = 0;j_ < m_N;++j_)
        {
            complex<double> cell_;
            cell_.real(cos(2 * M_PI * m_mmd[i_][j_] / (m_N_num+1)));
            cell_.imag(sin(2 * M_PI * m_mmd[i_][j_] / (m_N_num+1)) * -1.0);
            row_.push_back(cell_);
        }
        m_res_S2.push_back(row_);
    }
    return m_res_S2;
}
