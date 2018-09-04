 #include "parseresultdata.h"
#include <QDebug>
#include <QStringList>

ParseResultData::ParseResultData(QObject *parent) :
    QObject(parent)
{
}

ParseResultData::~ParseResultData()
{
    m_result_map.clear();
}

Task_Cmp &ParseResultData::Parse(QString p_path)
{
    m_result_map.clear();
    QFile file(p_path);
    if(!file.exists()){
        qDebug() << "File " << p_path << " no exist!";
        return m_result_map;
    }
    if(!file.open(QFile::ReadOnly | QIODevice::Text)) {
        qDebug()<< p_path << "open failed!";
        return m_result_map;
    }
    QString cur_freq = "-1";

    while(!file.atEnd())
    {
        QString line = file.readLine();
        line = line.trimmed();
        if(line.isEmpty()){
            continue;
        }
        QStringList ls_list = line.split(QRegExp(":"));
        if(ls_list.size() == 2 && ls_list.at(0).trimmed() == FREQUENCE){
            cur_freq = QString(ls_list.at(1));
        }
        else
        {
            if(ls_list.size() == 1 && ls_list.at(0).trimmed() == FREQUENCE){
                cur_freq = "-1";
                continue;
            }
            ls_list = line.split(QRegExp(","));
            if(ls_list.size() != 3)
                continue;
            int id = ls_list.at(0).toInt();
            m_result_map[cur_freq][id].first  = ls_list.at(1).toDouble();
            m_result_map[cur_freq][id].second = ls_list.at(2).toDouble();
        }
    }
    file.close();
    return m_result_map;
}


void ParseResultData::Save(QString p_path,Task_Cmp p_cmp)
{
    if(p_path.isEmpty()) return;
    QFile file(p_path);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        qDebug()<< p_path << "open failed!";
        return;
    }
    QTextStream out(&file);
    for(Task_Cmp::const_iterator constIter = p_cmp.begin(); constIter != p_cmp.end(); ++constIter)
    {
        out << "Freq:" << constIter->first;
        out << endl;

        std::map<int, std::pair<double, double> > tmp_map = constIter->second;
        std::map<int, std::pair<double, double> >::const_iterator iter = tmp_map.begin();
        for(;iter != tmp_map.end(); ++iter)
        {
            out << iter->first << ",";
            out << QString::number(iter->second.first,'f');
            out << "," ;
            out << QString::number(iter->second.second,'f');
            out << endl;
        }
        out << endl;
    }
    file.close();
}
