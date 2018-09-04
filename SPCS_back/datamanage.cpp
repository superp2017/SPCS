#include "datamanage.h"
#include <QDateTime>
#include "twoshorttoid.h"

DataManage::DataManage()
{

}

void DataManage::SaveToFile(std::map<QString, std::map<int, QString> > &pdata, std::vector<QString> &p_freq,QString p_path)
{
    Task_Cmp  ls_cmp;
    StrToDouble(pdata,ls_cmp,false);
    SaveToFile(ls_cmp,p_freq,p_path);
}

void DataManage::SaveToFile(Task_Cmp &p_cmp, std::vector<QString> &p_freq, QString p_path)
{
    if(p_cmp.size() ==0)
    {
        qDebug()<<" DataManage::SaveToFile buf size ==0";
        return ;
    }
    if(p_path.isEmpty()) {qDebug()<<p_path<<"is empty"; return;}
    QFile file(p_path);
    if(!file.open(QFile::ReadWrite|QFile::Text)){
        qDebug()<< "DataManage::SaveToFile "<<  p_path << "open failed!";
        return;
    }
    QTextStream out(&file);

    for(size_t i =0;i<p_freq.size();++i)
    {
        QString cur_freq = p_freq.at(i);
        if(cur_freq.isEmpty()) continue;

        if(p_cmp.count(cur_freq)>0)
        {
            out<<FREQUENCE<<":"<<cur_freq<<endl;
            std::map<int, std::pair<double, double> > tmp_map = p_cmp[cur_freq];
            std::map<int, std::pair<double, double> >::const_iterator iter = tmp_map.begin();
            for(;iter != tmp_map.end(); ++iter)
            {
                int id =  iter->first;
                short row,col;
                TwoShortToId::instance()->IdToAddr(id,row,col);
                out << id<< ","<<row<<","<<col<<",";
                out << QString::number(iter->second.first,'f',9);
                out << "," ;
                out << QString::number(iter->second.second,'f',9);
                out << endl;
            }
        }else
            qDebug()<<"freq"<<cur_freq<<"not exist!";
    }
    ////////////


    file.close();
}

void DataManage::SaveToFile_dB(std::map<QString, std::map<int, QString> > &pdata,std::vector<QString> &p_freq,  QString p_path)
{
    Task_Cmp  ls_cmp;
    if(pdata.size() ==0)
    {
        qDebug()<<" DataManage::SaveToFile_dB buf size ==0";
        return ;
    }
    StrToDouble(pdata,ls_cmp,true);
    SaveToFile(ls_cmp,p_freq,p_path);
}

void DataManage::SavePhase1(std::map<QString, std::map<int, double> > p_data, std::vector<QString> &p_freq,QString path)
{
    if(p_data.size() ==0)
    {
        qDebug()<<" DataManage::SavePhase1 buf size ==0";
        return ;
    }
    if(path.isEmpty()) return;
    QFile file(path);
    if(!file.open(QFile::ReadWrite|QFile::Text)){
        qDebug()<< path << "open failed!";
        return;
    }
    QTextStream out(&file);

    for(size_t i =0;i<p_freq.size();++i)
    {
        QString cur_freq = p_freq.at(i);
        if(cur_freq.isEmpty()) continue;

        if(p_data.count(cur_freq)>0)
        {
            out<<FREQUENCE<<":"<<cur_freq<<endl;
            std::map<int,double> ls_pair = p_data[cur_freq];
            std::map<int,double>::iterator iter2 = ls_pair.begin();
            while(iter2 != ls_pair.end())
            {
                int id =  iter2->first;
                short row,col;
                TwoShortToId::instance()->IdToAddr(id,row,col);
                out<<iter2->first<<","<<row<<","<<col<<","<<QString::number(iter2->second,'f',3)<<endl;
                ++iter2;
            }
        }
    }
    ///////

    file.close();
}

std::map<QString, std::map<int, double> > &DataManage::ReadformPhase1(QString path)
{
    m_phase_1.clear();
    QFile file(path);
    if(!file.exists()){
        qDebug() << "File " << path << " no exist!";
        return m_phase_1;
    }
    if(!file.open(QFile::ReadOnly | QIODevice::Text)) {
        qDebug()<< path << "open failed!";
        return m_phase_1;
    }
    QString cur_freq = "-1";
    while(!file.atEnd())
    {
        QString line = file.readLine();
        line = line.trimmed();
        if(line.isEmpty()){
            continue;
        }
        QStringList ls_list = line.split(QRegExp(":"),QString::SkipEmptyParts);
        if(ls_list.size() == 2 && ls_list.at(0) == FREQUENCE){
            cur_freq = QString(ls_list.at(1));
        }
        else
        {
            if(ls_list.size() == 1 && ls_list.at(0) == FREQUENCE){
                cur_freq = "-1";
                continue;
            }
            ls_list = line.split(QRegExp(","));
            if(ls_list.size() != 4)
                continue;
            int id = ls_list.at(0).toInt();
            m_phase_1[cur_freq][id] = ls_list.at(3).toDouble();
        }
    }
    file.close();
    return m_phase_1;
}

void DataManage::clear_buf()
{
    m_result_cmp.clear();
    m_curves.clear();
    m_resule_res.clear();
}

Task_Cmp DataManage::ReadFromFile_cmp(QString p_path )
{
    m_result_cmp.clear();
    QFile file(p_path);
    if(!file.exists()){
        qDebug() << "File " << p_path << " no exist!";
        return m_result_cmp;
    }
    if(!file.open(QFile::ReadOnly | QIODevice::Text)) {
        qDebug()<< p_path << "open failed!";
        return m_result_cmp;
    }
    QString cur_freq = "-1";

    while(!file.atEnd())
    {
        QString line = file.readLine();
        line = line.trimmed();
        if(line.isEmpty()){
            continue;
        }
        QStringList ls_list = line.split(QRegExp(":"),QString::SkipEmptyParts);
        if(ls_list.size() == 2 && ls_list.at(0) == FREQUENCE){
            cur_freq = QString(ls_list.at(1));
        }
        else
        {
            if(ls_list.size() == 1 && ls_list.at(0) == FREQUENCE){
                cur_freq = "-1";
                continue;
            }
            ls_list = line.split(QRegExp(","));
            if(ls_list.size() != 5)
                continue;
            int id = ls_list.at(0).toInt();
            m_result_cmp[cur_freq][id].first  = ls_list.at(3).toDouble();
            m_result_cmp[cur_freq][id].second = ls_list.at(4).toDouble();
        }
    }
    file.close();
    return m_result_cmp;
}

Task_Res DataManage::ReadFromFile_org(QString &p_path)
{
    m_resule_res.clear();
    QFile file(p_path);
    if(!file.exists()){
        qDebug() << "File " << p_path << " no exist!";
        return m_resule_res;
    }
    if(!file.open(QFile::ReadOnly | QIODevice::Text)) {
        qDebug()<< p_path << "open failed!";
        return m_resule_res;
    }
    QString cur_freq = "-1";

    while(!file.atEnd())
    {
        QString line = file.readLine();
        line = line.trimmed();
        if(line.isEmpty()){
            continue;
        }
        QStringList ls_list = line.split(QRegExp(":"),QString::SkipEmptyParts);
        if(ls_list.size() == 2 && ls_list.at(0) == FREQUENCE){
            cur_freq = QString(ls_list.at(1));
        }
        else
        {
            if(ls_list.size() == 1 && ls_list.at(0) == FREQUENCE){
                cur_freq = "-1";
                continue;
            }
            ls_list = line.split(QRegExp(","));
            if(ls_list.size() != 5)
                continue;
            int id = ls_list.at(0).toInt();
            QString str = ls_list.at(3) + "," + ls_list.at(4);
            m_resule_res[cur_freq][id] = str;
        }
    }
    file.close();
    return m_resule_res;
}

std::vector<Curvedata> &DataManage::ReadMAXFile(QString& p_path,\
                                                std::vector<QString> &p_freq,\
                                                bool ismp)
{
    m_curves.clear();
    m_once = true;
    QFile file(p_path);
    if(!file.exists()){
        qDebug() << "File " << p_path << " no exist!";
        return m_curves;
    }
    if(!file.open(QFile::ReadOnly | QIODevice::Text)) {
        qDebug()<< p_path << "open failed!";
        return m_curves;
    }
    QString cur_freq = "-1";

    Curvedata ls_curvedata;
    while(!file.atEnd())
    {
        QString line = file.readLine();
        line = line.trimmed();
        if(line.isEmpty()){
            continue;
        }
        ls_curvedata.t_date = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz");
        QStringList ls_list = line.split(QRegExp(":"));
        if(ls_list.size() == 2 && ls_list.at(0) == FREQUENCE)
        {
            if(!m_once)
            {
                m_curves.push_back(ls_curvedata);
            }else
                m_once = false;

            ls_curvedata.t_id.clear();
            ls_curvedata.t_magn.clear();
            ls_curvedata.t_phase.clear();

            cur_freq = QString(ls_list.at(1));
            ls_curvedata.t_freq = cur_freq;
            p_freq.push_back(cur_freq);
            continue;
        }else
        {
            if(ls_list.size() == 1 && ls_list.at(0) == FREQUENCE)
            {
                cur_freq = "-1";
                continue;
            }
            ls_list = line.split(QRegExp(","));
            if(ls_list.size() != 5)
                continue;
            int id = ls_list.at(0).toInt();
            ls_curvedata.t_id.push_back(QString("%1").arg(id));

            double  ls_m     = ls_list.at(3).toDouble();
            double  ls_p     = ls_list.at(4).toDouble();
            if(!ismp)
            {
                ls_m = genMagn(ls_m,ls_p);
                ls_p = genPhase(ls_m,ls_p);
            }
            if(ls_p >180) ls_p -=360;
            if(ls_p<-180) ls_p +=360;

            ls_curvedata.t_magn.push_back(QString::number(ls_m));
            ls_curvedata.t_phase.push_back(QString::number(ls_p));
        }
    }
    if(ls_curvedata.t_magn.size() == ls_curvedata.t_phase.size() && ls_curvedata.t_magn.size() >0)
        m_curves.push_back(ls_curvedata);
    file.close();
    return m_curves;
}

void DataManage::StrToDouble(std::map<QString, std::map<int, QString> > &pdata, Task_Cmp &cmp, bool isdb)
{
    if(pdata.empty())   return;
    std::map<QString,std::map<int,QString> >::const_iterator c_iter = pdata.begin();

    while(c_iter != pdata.end())
    {
        if(c_iter->first.isEmpty()) continue;
        std::map<int,QString> ls_map = c_iter->second;
        std::map<int,QString>::const_iterator cm_iter = ls_map.begin();
        while(cm_iter != ls_map.end())
        {
            QString ls_str = ls_map[cm_iter->first];
            QStringList  ls_list = ls_str.split(QRegExp(","));
            if(ls_list.size() != 2) continue;
            if(isdb)
            {
                cmp[c_iter->first][cm_iter->first].first  = SPCS_dB::dB(genMagn(ls_list.at(0).toDouble(),ls_list.at(1).toDouble()));

                cmp[c_iter->first][cm_iter->first].second = genPhase(ls_list.at(0).toDouble(),ls_list.at(1).toDouble());
            }else
            {
                cmp[c_iter->first][cm_iter->first].first  = ls_list.at(0).toDouble(); //genMagn(ls_list.at(0).toDouble(),ls_list.at(1).toDouble());
                cmp[c_iter->first][cm_iter->first].second = ls_list.at(1).toDouble(); //genPhase(ls_list.at(0).toDouble(),ls_list.at(1).toDouble());
            }
            cm_iter++;
        }
        c_iter++;
    }
}


double DataManage::genMagn_w(double real, double imag)
{
    double num = (real * real + imag * imag)/50;
    if(num == 0)
        return 10 * log10(1.0) + 30;
    else
        return 10 * log10(num) + 30;
}

double DataManage::genMagn(double real, double imag)
{
    return sqrt(real * real + imag * imag);
}

double DataManage::genPhase(double real, double imag)
{
    return qAtan2(imag, real) / M_PI * 180;
}
