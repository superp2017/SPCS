#include "m_caldiffer_tools.h"
#include <QStringList>
#include "_global.h"

M_CalDiffer_tools::M_CalDiffer_tools(QWidget *parent) :
    QWidget(parent),
    m_layout(this)
{
    m_layout.addWidget(&m_view,0);
    m_layout.addWidget(&m_pane,1);
    m_layout.setStretch(0,6);
    m_layout.setStretch(1,1);
    m_view.init();
    setLayout(&m_layout);
    this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    connect(&m_pane,SIGNAL(compare(QString,QString)),this,SLOT(compare(QString,QString)));
    connect(&m_pane,SIGNAL(add_curve(QString)),this,SLOT(add_curve(QString)));
    connect(&m_pane,SIGNAL(add_s2p(QString)),this,SLOT(add_s2p(QString)));
    connect(&m_pane,SIGNAL(clear_view()),this,SLOT(clear_view()));
}

void M_CalDiffer_tools::compare(QString path1, QString path2)
{
    clear_view();
    std::vector<QString>                        m_freq_key;
    std::map<QString,std::pair<double,double> > ls_data1;
    std::map<QString,std::pair<double,double> > ls_data2;
    ParseFile(path1,ls_data1,m_freq_key,true);
    ParseFile(path2,ls_data2,m_freq_key);

    Curvedata ls_curve;

    for(size_t i =0;i<m_freq_key.size();++i)
    {
        QString cur_freq = m_freq_key.at(i);
        if(ls_data1.count(cur_freq)>0 && ls_data2.count(cur_freq))
        {
            double ls_db    = ls_data1[cur_freq].first - ls_data2[cur_freq].first;
            double ls_phase = ls_data1[cur_freq].second - ls_data2[cur_freq].second;
            ls_curve.t_id.push_back(cur_freq);
            ls_curve.t_magn.push_back(QString::number(ls_db,'f',9));
            ls_curve.t_phase.push_back(QString::number(ls_phase,'f',9));
            //   qDebug()<<cur_freq<<ls_db<<ls_phase;
        }
    }

    if(ls_curve.t_id.size()> 0 &&ls_curve.t_magn.size()>0&&ls_curve.t_phase.size()>0 )
    {
        ls_curve.t_date = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz");
        m_view.creatcurve(ls_curve);;
    }
}

void M_CalDiffer_tools::add_s2p(QString path)
{
    std::vector<QString>                          m_freq_key;
    std::map<QString,std::pair<QString,QString> > ls_data;
    m_parse.get_s2p(ls_data,m_freq_key,path);
    Curvedata ls_curve;
    QFileInfo ls_info(path);
    for(size_t i =0;i<m_freq_key.size();++i)
    {
        QString cur_freq = m_freq_key.at(i);
        if(ls_data.count(cur_freq))
        {
            QString ls_db    = ls_data[cur_freq].first;
            QString ls_phase = ls_data[cur_freq].second;
            ls_curve.t_id.push_back(cur_freq);
            ls_curve.t_magn.push_back(ls_db);
            ls_curve.t_phase.push_back(ls_phase);
        }
    }

    if(ls_curve.t_id.size()> 0 &&ls_curve.t_magn.size()>0&&ls_curve.t_phase.size()>0 )
    {
        ls_curve.t_date = ls_info.baseName()+"_"+QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz");
        m_view.creatcurve(ls_curve);;
    }
}


void M_CalDiffer_tools::add_curve(QString path)
{
    std::vector<QString>                        m_freq_key;
    std::map<QString,std::pair<double,double> > ls_data;
    ParseFile(path,ls_data,m_freq_key,true);
    QFileInfo ls_info(path);
    Curvedata ls_curve;
    for(size_t i =0;i<m_freq_key.size();++i)
    {
        QString cur_freq = m_freq_key.at(i);
        if(ls_data.count(cur_freq))
        {
            double ls_db    = ls_data[cur_freq].first;
            double ls_phase = ls_data[cur_freq].second;
            ls_curve.t_id.push_back(cur_freq);
            ls_curve.t_magn.push_back(QString::number(ls_db,'f',9));
            ls_curve.t_phase.push_back(QString::number(ls_phase,'f',9));
        }
    }

    if(ls_curve.t_id.size()> 0 &&ls_curve.t_magn.size()>0&&ls_curve.t_phase.size()>0 )
    {
        ls_curve.t_date = ls_info.baseName()+"_"+QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz");
        m_view.creatcurve(ls_curve);;
    }
}


void M_CalDiffer_tools::ParseFile(QString path, std::map<QString, std::pair<double, double> > &pdata, \
                                  std::vector<QString> &p_freqs, bool save)
{
    QString ls_path =  path;
    QFile ls_file(ls_path);
    if(!ls_file.open(QFile::ReadWrite|QFile::Text))
    {
        qDebug()<< ls_path << "open failed!";
        QMessageBox::information(NULL,tr("Message"),tr("file is not exist"));
        return;
    }

    while(!ls_file.atEnd())
    {
        QString line = ls_file.readLine();
        line = line.trimmed();
        if(line.isEmpty())
            continue;
        QStringList ls_list = line.split(QRegExp(":"));
        if(ls_list.at(0).trimmed() == "ElecSwitch") continue;
        ls_list = line.split(QRegExp(","));
        if(ls_list.size() == 3)
        {
            if(ls_list.at(0).trimmed() == "frequecy") continue;
            QString cur_freq = ls_list.at(0);
            if(save)
                p_freqs.push_back(cur_freq);
            double  db       = ls_list.at(1).toDouble();
            double  phase    = ls_list.at(2).toDouble();
            pdata[cur_freq]  = std::pair<double,double>(db,phase);
        }
    }
    ls_file.close();
}


void M_CalDiffer_tools::clear_view()
{
    m_view.reset();
}
