#include "m_stabletools.h"

M_StableTools::M_StableTools(QWidget *parent) :
    QWidget(parent),
    m_layout(this)
{
    m_layout.addWidget(&m_view,0);
    m_layout.addWidget(&m_pane,1);
    m_layout.setStretch(0,8);
    m_layout.setStretch(1,1);
    m_view.init();
    setLayout(&m_layout);
    this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    connect(&m_pane,SIGNAL(loaddata(QString)),this,SLOT(LoadData(QString)));
    connect(&m_pane,SIGNAL(query(QString,QString,bool)),\
            this,SLOT(CheckoutData(QString,QString,bool)),Qt::QueuedConnection);
}

void M_StableTools::clear_data()
{
    m_s21.clear();
    m_s12.clear();
    m_s11.clear();
    m_s22.clear();
    m_freqs.clear();
    m_pane.clear_combox();
}

void M_StableTools::reset_view()
{
    m_view.reset();
}

void M_StableTools::reset()
{
    clear_data();
    reset_view();
}


void M_StableTools::CheckoutData(QString freq, QString type, bool isto0)
{
    std::vector< std::pair<double,double> > ls_data;
    Curvedata   ls_curve;

    if(type == "S11")
    {
        if(m_s11.size()>0)
        {
            if(m_s11.count(freq)>0)
            {
                ls_data  = m_s11[freq];
            }
        }
    }

    if(type == "S22")
    {
        if(m_s22.size()>0)
        {
            if(m_s22.count(freq)>0)
            {
                ls_data  = m_s22[freq];
            }
        }
    }
    if(type == "S12")
    {
        if(m_s12.size()>0)
        {
            if(m_s12.count(freq)>0)
            {
                ls_data  = m_s12[freq];
            }
        }
    }
    if(type == "S21")
    {
        if(m_s21.size()>0)
        {
            if(m_s21.count(freq)>0)
            {
                ls_data  = m_s21[freq];
            }
        }
    }
    reset_view();
    QFileInfo ls_info(m_path);
    if(ls_data.size()>0)
    {
        double min_db    = ls_data.at(0).first;
        double min_phase = ls_data.at(0).second;

        if(isto0)
        {
            for(size_t i =0;i<ls_data.size();++i)
            {
                if(ls_data.at(i).first < min_db)
                    min_db = ls_data.at(i).first;
                if(ls_data.at(i).second<min_phase)
                    min_phase = ls_data.at(i).second;
            }
        }

        for(size_t i =0;i<ls_data.size();++i)
        {
            std::pair<double,double> ls_pair = ls_data.at(i);
            ls_curve.t_id.push_back(QString("%1").arg(i));
            double ls_db = ls_pair.first;
            double ls_phase = ls_pair.second;
            if(isto0)
            {
                ls_db    -= min_db;
                ls_phase -= min_phase;
            }
            ls_curve.t_magn.push_back(QString::number(ls_db,'f',9));
            ls_curve.t_phase.push_back(QString::number(ls_phase,'f',9));
        }

        if(ls_curve.t_id.size()>0&&ls_curve.t_magn.size()>0&&ls_curve.t_phase.size()>0)
        {
            ls_curve.t_freq = freq;
            ls_curve.t_date = ls_info.baseName()+"_"+QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz");
            m_view.creat_curve(ls_curve);
        }
    }
}

void M_StableTools::LoadData(QString path)
{
    QString ls_path =  path;
    QFile ls_file(ls_path);
    if(ls_path.isEmpty()|| !ls_file.exists())
    {
        QMessageBox::information(this,tr("ERROR"),tr("File is not exist !"));
        return ;
    }
    if(!ls_file.open(QFile::ReadWrite|QFile::Text))
    {
        qDebug()<< ls_path << "open failed!";
        QMessageBox::information(NULL,tr("Message"),tr("file is not exist"));
        return;
    }
    m_path  =  path;
    clear_data();

    int index_s11 = -1;
    int index_s12 = -1;
    int index_s21 = -1;
    int index_s22 = -1;

    while(!ls_file.atEnd())
    {
        QString line = ls_file.readLine();
        line = line.trimmed();
        if(line.isEmpty())
            continue;


        QStringList ls_list = line.split(QRegExp(","));
        if(ls_list.at(0) == "frequecy")
        {
            for(int i =0;i<ls_list.size();++i)
            {
                QString cur = ls_list.at(i);
                if( cur== "S11")
                    index_s11 = 2*i-1;
                if(cur == "S12")
                    index_s12 = 2*i-1;
                if(cur == "S21")
                    index_s21 = 2*i-1;
                if(cur == "S22")
                    index_s22 = 2*i-1;
            }
        }

        int s_size=0;
        if(index_s11 >0) s_size +=1;
        if(index_s12 >0) s_size +=1;
        if(index_s21 >0) s_size +=1;
        if(index_s22 >0) s_size +=1;

        if(ls_list.size() == (s_size*2 +2))
        {
            QString cur_freq = ls_list.at(0);
            if(m_freqs.find(cur_freq) == m_freqs.end())
            {
                m_pane.add_item(cur_freq);
                m_freqs.insert(cur_freq);
            }
            if( index_s11>0)
                m_s11[cur_freq].push_back(std::pair<double,double>\
                                          (ls_list.at(index_s11).toDouble(),ls_list.at(index_s11+1).toDouble()));
            if(index_s12 >0)
                m_s12[cur_freq].push_back(std::pair<double,double>\
                                          (ls_list.at(index_s12).toDouble(),ls_list.at(index_s12+1).toDouble()));
            if(index_s21 >0)
                m_s21[cur_freq].push_back(std::pair<double,double>\
                                          (ls_list.at(index_s21).toDouble(),ls_list.at(index_s21+1).toDouble()));
            if(index_s22 >0)
                m_s22[cur_freq].push_back(std::pair<double,double>\
                                          (ls_list.at(index_s22).toDouble(),ls_list.at(index_s22+1).toDouble()));
        }
    }
     ls_file.close();
}
