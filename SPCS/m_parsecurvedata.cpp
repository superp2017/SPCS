#include "m_parsecurvedata.h"

M_ParseCurveData::M_ParseCurveData(QObject *parent) :
    QObject(parent)
{
}

M_ParseCurveData::~M_ParseCurveData()
{
    clean();
}

void M_ParseCurveData::parse(QString p_path, bool isdb, bool is360)
{
    clean();
    QFile ls_file(p_path);
    if(ls_file.exists())
    {
        QSettings settings(p_path,QSettings::IniFormat);
        ///频率
        settings.beginGroup("Freq");
        QString cur_freq =QString::number(settings.value("freq").toDouble());
        m_curve_data.t_freq= cur_freq;
        settings.endGroup();
        ///日期
        settings.beginGroup("Date");
        m_curve_data.t_date  = settings.value("date").toString();
        settings.endGroup();

        ///数据类型
        settings.beginGroup("DataType");
        QString pdb  = settings.value("IsdB").toString();
        QString pphase =settings.value("PhaseRange").toString();
        bool pisdb,p360;
        pisdb = (pdb=="true");
        p360  = (pphase=="0~360");
        settings.endGroup();

        ///数据
        settings.beginGroup("Data");
        QStringList ls_id =settings.allKeys();
        std::stable_sort(ls_id.begin(), ls_id.end(), Compare_id());
        for(int i = 0;i<ls_id.size();++i)
        {
            QString id = ls_id.at(i);
            m_curve_data.t_id.push_back(id);
            QStringList data = settings.value(id).toString().trimmed().split(QRegExp(","));
            if(data.size() == 4)
            {
                double  ls_m     = data.at(2).toDouble();
                double  ls_p     = data.at(3).toDouble();
                if(isdb&&!pisdb)
                    ls_m    = SPCS_dB::dB(ls_m);
                if(is360 && !p360&& ls_p <0)
                    ls_p   += 360;
                m_curve_data.t_magn.push_back(QString::number(ls_m));
                m_curve_data.t_phase.push_back(QString::number(ls_p));

            }else
            {
                QMessageBox::information(NULL, tr("Warning"),
                                         tr("Curve File Parse failed !"));
                clean();
                return;
            }
        }
        settings.endGroup();
    }else
        QMessageBox::information(NULL, tr("Warning"),
                                 tr("File is not exist!"));
}

void M_ParseCurveData::gen_file(QString &p_path, Curvedata &p_data)
{
    QSettings settings(p_path,QSettings::IniFormat);
    ///频率
    settings.beginGroup("Freq");
    settings.setValue("freq",p_data.t_freq);
    settings.endGroup();
    ///日期
    settings.beginGroup("Date");
    settings.setValue("date",p_data.t_date);
    settings.endGroup();
    ///数据
    settings.beginGroup("Data");
    if(p_data.t_magn.size()== p_data.t_phase.size() && p_data.t_magn.size()>0)
    {
        for(size_t i =0;i<p_data.t_magn.size();++i)
        {
            QString id = p_data.t_id.at(i);
            QString var = QString::number(p_data.t_magn.at(i).toDouble(),'f') + "," + QString::number(p_data.t_phase.at(i).toDouble(),'f');
            settings.setValue(id,var);
        }
    }
    settings.endGroup();
}

void M_ParseCurveData::gen_list(QString &filename, std::map<QString, QString> &p_filelist)
{
    QSettings settings(filename,QSettings::IniFormat);
    settings.beginGroup("List");
    std::map<QString, QString>::iterator iter = p_filelist.begin();
    while(iter != p_filelist.end())
    {
        QString key  = iter->first;
        QString var  = iter->second;
        settings.setValue(key,var);
        ++iter;
    }
    settings.endGroup();
}


Curvedata &M_ParseCurveData::get_curve_data()
{
    return m_curve_data;
}

void M_ParseCurveData::clean()
{
    m_curve_data.t_date.clear();
    m_curve_data.t_freq.clear();
    m_curve_data.t_id.clear();
    m_curve_data.t_magn.clear();
    m_curve_data.t_phase.clear();
}

