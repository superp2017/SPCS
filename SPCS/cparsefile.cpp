#include "cparsefile.h"
#include <QStringList>
#include <QFile>
#include "qmath.h"
#include <QDebug>

CParsefile::CParsefile(QObject *parent) :
    QObject(parent)
{

}


void CParsefile::load_cal_data(QString p_path,QString pname)
{
    m_s11_cal.clear();
    m_s12_cal.clear();
    m_s21_cal.clear();
    m_s22_cal.clear();
    m_freq_key.clear();
    bool ls_once =true;;
    for(int i =1;i<17;++i)
    {
        QString filename = p_path + pname +QString("%1").arg(i) + ".s2p";
        QFile   ls_file(filename);
        if(!ls_file.exists()) continue;
        
        if(!ls_file.open(QFile::ReadOnly | QIODevice::Text)) continue;
        bool isdB = false;
        double cur_index =1;
        int s11_index = -1;
        int s21_index = -1;
        int s12_index = -1;
        int s22_index = -1;
        while(!ls_file.atEnd())
        {
            QString line = ls_file.readLine();
            line = line.trimmed();
            if(line.isEmpty())
                continue;
            if(line.at(0) == '!')
            {
                QStringList ls_info = line.split(QRegExp(":"));
                if(ls_info.size() == 4)
                {
                    if(ls_info.at(1).trimmed() == "Measurements")
                    {
                        QStringList ls_s = ls_info.at(2).trimmed().split(QRegExp(","));
                        {
                            if(ls_s.size() == 4)
                            {
                                for(int j=0;j<4;++j)
                                {
                                    if(ls_s.at(j).trimmed() == "S11")
                                        s11_index = 2*j+1;
                                    if(ls_s.at(j).trimmed() == "S21")
                                        s21_index = 2*j+1;
                                    if(ls_s.at(j).trimmed() == "S12")
                                        s12_index = 2*j+1;
                                    if(ls_s.at(j).trimmed() == "S22")
                                        s22_index = 2*j+1;
                                }
                            }
                        }
                    }
                }
                continue;
            }
            if(line.at(0) == '#')
            {
                QStringList ls_list_type = line.split(QRegExp("\\s+"));
                if(ls_list_type.size() == 6)
                {
                    if(ls_list_type.at(1) == "Hz")
                        cur_index = 1;
                    if(ls_list_type.at(1) == "KHz")
                        cur_index = 1000;
                    if(ls_list_type.at(1) == "MHz")
                        cur_index = 1000000;
                    if(ls_list_type.at(1) == "GHz")
                        cur_index = 1000000000;

                    if(ls_list_type.at(3) == "dB")
                        isdB = true;
                }
                continue;
            }
            QStringList ls_list = line.split(QRegExp("\\s+"));
            if(ls_list.size() == 9)
            {
                QString cur_freq = QString::number(ls_list.at(0).toDouble()*cur_index,'f',0);
                if(ls_once)
                    m_freq_key.push_back(cur_freq);

                double ls_magn = 0;
                if(s11_index >= 0)
                {
                    ls_magn = ls_list.at(s11_index).toDouble();
                    if(isdB)
                        ls_magn =  pow(10.0,ls_magn/20);
                    m_s11_cal[i][cur_freq] = std::pair<double,double>(ls_magn,ls_list.at(s11_index+1).toDouble());
                }else
                    m_s11_cal[i][cur_freq] = std::pair<double,double>(0,0);

                if(s21_index >= 0)
                {
                    ls_magn = ls_list.at(s21_index).toDouble();
                    if(isdB)
                        ls_magn =  pow(10.0,ls_magn/20);
                    m_s21_cal[i][cur_freq] = std::pair<double,double>(ls_magn,ls_list.at(s21_index+1).toDouble());
                }else
                    m_s21_cal[i][cur_freq] = std::pair<double,double>(0,0);

                if(s12_index >= 0)
                {
                    ls_magn = ls_list.at(s12_index).toDouble();
                    if(isdB)
                        ls_magn =  pow(10.0,ls_magn/20);
                    m_s12_cal[i][cur_freq] = std::pair<double,double>(ls_magn,ls_list.at(s12_index+1).toDouble());
                }else
                    m_s12_cal[i][cur_freq] = std::pair<double,double>(0,0);
                if(s22_index >= 0)
                {
                    ls_magn = ls_list.at(s22_index).toDouble();
                    if(isdB)
                        ls_magn =  pow(10.0,ls_magn/20);
                    m_s22_cal[i][cur_freq] = std::pair<double,double>(ls_magn,ls_list.at(s22_index+1).toDouble());
                }else
                    m_s22_cal[i][cur_freq] = std::pair<double,double>(0,0);
            }
        }
        ls_once = false;
    }
}

void CParsefile::combine_data(std::map<QString,std::map<QString, std::vector<std::pair<QString,QString> > > > &p_data, \
                              std::vector<QString> &m_freq, QString path,bool issave)
{

    QFile   ls_file(path);
    if(!ls_file.exists()) return;

    if(!ls_file.open(QFile::ReadOnly | QIODevice::Text)) return;
    bool isdB = false;
    double cur_index =1;
    int s11_index = -1;
    int s21_index = -1;
    int s12_index = -1;
    int s22_index = -1;
    while(!ls_file.atEnd())
    {
        QString line = ls_file.readLine();
        line = line.trimmed();
        if(line.isEmpty())
            continue;
        if(line.at(0) == '!')
        {
            QStringList ls_info = line.split(QRegExp(":"));
            if(ls_info.size() == 4)
            {
                if(ls_info.at(1).trimmed() == "Measurements")
                {
                    QStringList ls_s = ls_info.at(2).trimmed().split(QRegExp(","));
                    {
                        if(ls_s.size() == 4)
                        {
                            for(int j=0;j<4;++j)
                            {
                                if(ls_s.at(j).trimmed() == "S11")
                                    s11_index = 2*j+1;
                                if(ls_s.at(j).trimmed() == "S21")
                                    s21_index = 2*j+1;
                                if(ls_s.at(j).trimmed() == "S12")
                                    s12_index = 2*j+1;
                                if(ls_s.at(j).trimmed() == "S22")
                                    s22_index = 2*j+1;
                            }
                        }
                    }
                }
            }
            continue;
        }
        if(line.at(0) == '#')
        {
            QStringList ls_list_type = line.split(QRegExp("\\s+"));
            if(ls_list_type.size() == 6)
            {
                if(ls_list_type.at(1) == "Hz")
                    cur_index = 1;
                if(ls_list_type.at(1) == "KHz")
                    cur_index = 1000;
                if(ls_list_type.at(1) == "MHz")
                    cur_index = 1000000;
                if(ls_list_type.at(1) == "GHz")
                    cur_index = 1000000000;

                if(ls_list_type.at(3) == "dB")
                    isdB = true;
            }
            continue;
        }
        QStringList ls_list = line.split(QRegExp("\\s+"));
        if(ls_list.size() == 9)
        {
            QString cur_freq = QString::number(ls_list.at(0).toDouble()*cur_index,'f',0);
            if(issave)
                m_freq.push_back(cur_freq);
            double ls_magn  = 0;
            QString type = "S11";

            if(s11_index >=0)
            {
                ls_magn= ls_list.at(s11_index).toDouble();
                if(!isdB)
                    ls_magn =  20*log10(ls_magn);

                p_data[cur_freq][type].push_back(std::pair<QString,QString>\
                                                 (QString::number(ls_magn,'f'),ls_list.at(s11_index+1)));
            }else
                p_data[cur_freq][type].push_back(std::pair<QString,QString>("0","0"));
            type = "S21";
            if(s21_index >=0)
            {
                ls_magn = ls_list.at(s21_index).toDouble();
                if(!isdB)
                    ls_magn =  20*log10(ls_magn);
                p_data[cur_freq][type].push_back(std::pair<QString,QString>\
                                                 (QString::number(ls_magn,'f'),ls_list.at(s21_index+1)));
            }else
                p_data[cur_freq][type].push_back(std::pair<QString,QString>("0","0"));

            type = "S12";
            if(s12_index >= 0)
            {
                ls_magn = ls_list.at(s12_index).toDouble();
                if(!isdB)
                    ls_magn =  20*log10(ls_magn);
                p_data[cur_freq][type].push_back(std::pair<QString,QString>\
                                                 (QString::number(ls_magn,'f'),ls_list.at(s12_index+1)));

            }else
                p_data[cur_freq][type].push_back(std::pair<QString,QString>("0","0"));
            type = "S22";
            if(s22_index >= 0)
            {
                ls_magn = ls_list.at(s22_index).toDouble();
                if(!isdB)
                    ls_magn =  20*log10(ls_magn);
                p_data[cur_freq][type].push_back(std::pair<QString,QString>\
                                                 (QString::number(ls_magn,'f'),ls_list.at(s22_index+1)));
            }else
                p_data[cur_freq][type].push_back(std::pair<QString,QString>("0","0"));
        }
    }
}

void CParsefile::get_s2p(std::map<QString, std::pair<QString, QString> > &p_data, std::vector<QString> &m_freq, QString path, bool issave)
{

    QFile   ls_file(path);
    if(!ls_file.exists()) return;

    if(!ls_file.open(QFile::ReadOnly | QIODevice::Text)) return;
    bool isdB = false;
    double cur_index =1;
    int s11_index = -1;
    int s21_index = -1;
    int s12_index = -1;
    int s22_index = -1;
    while(!ls_file.atEnd())
    {
        QString line = ls_file.readLine();
        line = line.trimmed();
        if(line.isEmpty())
            continue;
        if(line.at(0) == '!')
        {
            QStringList ls_info = line.split(QRegExp(":"));
            if(ls_info.size() == 4)
            {
                if(ls_info.at(1).trimmed() == "Measurements")
                {
                    QStringList ls_s = ls_info.at(2).trimmed().split(QRegExp(","));
                    {
                        if(ls_s.size() == 4)
                        {
                            for(int j=0;j<4;++j)
                            {
                                if(ls_s.at(j).trimmed() == "S11")
                                    s11_index = 2*j+1;
                                if(ls_s.at(j).trimmed() == "S21")
                                    s21_index = 2*j+1;
                                if(ls_s.at(j).trimmed() == "S12")
                                    s12_index = 2*j+1;
                                if(ls_s.at(j).trimmed() == "S22")
                                    s22_index = 2*j+1;
                            }
                        }
                    }
                }
            }
            continue;
        }
        if(line.at(0) == '#')
        {
            QStringList ls_list_type = line.split(QRegExp("\\s+"));
            if(ls_list_type.size() == 6)
            {
                if(ls_list_type.at(1) == "Hz")
                    cur_index = 1;
                if(ls_list_type.at(1) == "KHz")
                    cur_index = 1000;
                if(ls_list_type.at(1) == "MHz")
                    cur_index = 1000000;
                if(ls_list_type.at(1) == "GHz")
                    cur_index = 1000000000;

                if(ls_list_type.at(3) == "dB")
                    isdB = true;
            }
            continue;
        }
        QStringList ls_list = line.split(QRegExp("\\s+"));
        if(ls_list.size() == 9)
        {
            QString cur_freq = QString::number(ls_list.at(0).toDouble()*cur_index,'f',0);
            if(issave)
                m_freq.push_back(cur_freq);
            double ls_magn  = 0;
          //  QString type = "S11";

//            if(s11_index >=0)
//            {
//                ls_magn= ls_list.at(s11_index).toDouble();
//                if(!isdB)
//                    ls_magn =  20*log10(ls_magn);

//                p_data[cur_freq][type].push_back(std::pair<QString,QString>\
//                                                 (QString::number(ls_magn,'f'),ls_list.at(s11_index+1)));
//            }else
//                p_data[cur_freq][type].push_back(std::pair<QString,QString>("0","0"));
           // type = "S21";
            if(s21_index >=0)
            {
                ls_magn = ls_list.at(s21_index).toDouble();
                if(!isdB)
                    ls_magn =  20*log10(ls_magn);
                p_data[cur_freq]= (std::pair<QString,QString>\
                                                 (QString::number(ls_magn,'f'),ls_list.at(s21_index+1)));
            }else
                p_data[cur_freq]= (std::pair<QString,QString>("0","0"));

//            type = "S12";
//            if(s12_index >= 0)
//            {
//                ls_magn = ls_list.at(s12_index).toDouble();
//                if(!isdB)
//                    ls_magn =  20*log10(ls_magn);
//                p_data[cur_freq][type].push_back(std::pair<QString,QString>\
//                                                 (QString::number(ls_magn,'f'),ls_list.at(s12_index+1)));

//            }else
//                p_data[cur_freq][type].push_back(std::pair<QString,QString>("0","0"));
//            type = "S22";
//            if(s22_index >= 0)
//            {
//                ls_magn = ls_list.at(s22_index).toDouble();
//                if(!isdB)
//                    ls_magn =  20*log10(ls_magn);
//                p_data[cur_freq][type].push_back(std::pair<QString,QString>\
//                                                 (QString::number(ls_magn,'f'),ls_list.at(s22_index+1)));
//            }else
//                p_data[cur_freq][type].push_back(std::pair<QString,QString>("0","0"));
        }
    }
}

double CParsefile::genLinMag(double real, double imag)
{
    return sqrt(real*real + imag * imag);
}

//////
/// \brief VNAdapter::genPhase
/// \param real
/// \param imag
/// \return
/// 产生相位
double CParsefile::genPhase(double real, double imag)
{
    return qAtan2(imag, real) / M_PI * 180;
}

double CParsefile::gendB(double magn)
{
    if(magn ==0)
        return magn;
    return 20*log10(magn);
}





//std::map<QString, std::map<int, std::pair<double, double> > > &CParsefile::get_cal_s21(QString p_apppath)
//{
//    QString file = p_apppath + "/config/CALI.ini";
//    m_s21_cal.clear();
//    QSettings iniSets(file, QSettings::IniFormat);
//    iniSets.beginGroup("INFO");
//    QString cur_freq = iniSets.value("Freq").toString();
//    iniSets.endGroup();

//    iniSets.beginGroup("DATA");
//    QStringList list = iniSets.allKeys();
//    QStringList::iterator iter = list.begin();
//    while(iter != list.end())
//    {
//        QStringList ls_list = iniSets.value(*iter).toString().split(QRegExp(","));
//        if(ls_list.size() == 2)
//        {
//            m_s21_cal[cur_freq][iter->toInt()] =  \
//                    std::pair<double,double>(ls_list.at(0).toDouble(),ls_list.at(1).toDouble());
//        }
//        iter++;
//    }
//    iniSets.endGroup();
//    return m_s21_cal;
//}
