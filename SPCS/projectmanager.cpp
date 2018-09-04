#include "projectmanager.h"
#include "radarface.h"
#include <QApplication>
#include "taskcenter_607.h"
#include "BackHandle.h"
#include "datamanage.h"
#include "configphase.h"
#include "tarray.h"
#include "m_setdev.h"
#include "m_setpulse.h"
#include "m_set_times.h"
#include "configerexcel.h"
#include  "datamanage.h"
#include "m_cfg_status_dlg.h"


ProjectManager::ProjectManager(QObject *parent) :
    QObject(parent)
{

}

ProjectManager::~ProjectManager()
{

}

void ProjectManager::reset()
{
    M_SetPNAdlg::instance()->reset();
    EleSwitch::instance()->reset();
    M_SelectGallerydlg::instance()->reset();
    M_TestInitDlg::instance()->reset();
    StatusOutput::instance()->reset();
    M_Dampingdlg::instance()->reset();
    M_SetFreqdlg::instance()->reset();
    TestResult::instance()->reset();
    RadarFace::instance()->reset();
    RadarAnaly::instance()->reset();
    TArray::instance()->reset();
    M_SetPulse::instance()->default_setting();
    M_SetDev::instance()->init();
    M_Set_Times::instance()->init();
    TaskCenter_607::instance()->reset();
}

////////////////
/// \brief ProjectManager::on_new
/// \param path
///新建
void ProjectManager::on_new(QString path)
{
    reset();
    QFileInfo ls_file(path);
    QString propath = ls_file.absolutePath() + "/"+ls_file.baseName();
    QDir ls_dir(propath);
    if(!ls_dir.exists())
        ls_dir.mkpath(propath);
    QString filename = propath + "/" +ls_file.fileName();
    set_info(filename);
    StatusOutput::instance()->update_proj_name(m_cur_name);
    m_mode = ON_NEW;
    on_save();
}

////////////
/// \brief ProjectManager::on_open
/// \param p_path
/// 打开工程
void ProjectManager::on_open(QString p_path)
{
    reset();
    set_info(p_path);
    Param_sets set;
    QFileInfo ls_info(p_path);
    QString param_name = ls_info.absolutePath() + PARAM_PATH + "/" +ls_info.baseName() + INI_Suffix;
    if(QFile(param_name).exists())
    {
        ParamSetManager::instance()->Read(param_name,set);
        ParamSetManager::instance()->Reload(set);
        StatusOutput::instance()->update_proj_name(m_cur_name);

        //////加载原始测试数据
        QString mapfile   = m_proj_path + PARAM_PATH+"/"+ m_cur_name +".map";
        QString arrayfile = m_proj_path + PARAM_PATH+"/"+ m_cur_name +".array";
        if(TaskCenter_607::instance()->init_map(mapfile))
        {
            if(TaskCenter_607::instance()->init_array(arrayfile))
            {
                //////////初始化测试参数
                TaskCenter_607::instance()->init_freq(set.t_fre_pts);
                TaskCenter_607::instance()->init_test_type(set.t_test_type,set.t_status);

                //////////////////////加载原始数据
                TDATA               ls_org_data;
                std::map<int,TDATA> ls_cfg_m_p_data;
                std::map<int,TDATA> ls_cfg_mp_Data;
                TaskCenter_607::instance()->Creat_Buffer(ls_org_data,ls_cfg_mp_Data,\
                                                         ls_cfg_m_p_data,set.t_test_time.t_cfg_mp_times.toInt(),\
                                                         set.t_test_time.t_cfg_m_mp_times.toInt());

                //////////////加载原始数据
                {
                    QString org_save_path = m_proj_path + ORG_PATH;
                    load_data(org_save_path,ls_org_data);
                }
#if 0
                TaskCenter_607::instance()->init_freq(set.t_fre_pts);
                TaskCenter_607::instance()->init_data();
                TaskCenter_607::instance()->load_cal_s21(QApplication::applicationDirPath(),false);
                TaskCenter_607::instance()->CALC_CFG(ls_org_data,true);

                TaskCenter_607::instance()->SAVE_CAL_DATA(ls_org_data,TaskCenter_607::instance()->get_freqs()\
                                                          ,TaskCenter_607::instance()->get_id()\
                                                          ,m_proj_path);
#endif

#if 1

                int ls_cfg_mp_times = set.t_test_time.t_cfg_mp_times.toInt();
                int ls_cfg_m_p_times = set.t_test_time.t_cfg_m_mp_times.toInt();
                QString cfg_mp_save_path  = m_proj_path + CFG_MP_PATH;
                QString cfg_m_p_save_path = m_proj_path + CFG_M_MP_PATH;

                ////////////加载幅度相位一起配的数据
                for(int i=0;i<ls_cfg_mp_times;++i)
                {
                    QString path = cfg_mp_save_path+ QString("/%1").arg(i+1);
                    load_data(path,ls_cfg_mp_Data[i]);
                }

                ////////////加载幅度相位分开配的数据
                for(int i=0;i<ls_cfg_m_p_times*2;++i)
                {
                    int index = i/2 +1;
                    QString path = cfg_m_p_save_path+ QString("/%1").arg(index);
                    load_data(path,ls_cfg_m_p_data[i]);
                }
                QString calpath = m_proj_path +DATA_PATH +  QString(CALDATA)+  CAL_MP_SUFFIX;
                Task_Cmp caldata =   m_datamanage.ReadFromFile_cmp(calpath);


                BackHandle::instance()->DATA_Manage(ls_org_data,ls_cfg_mp_Data,\
                                                    ls_cfg_m_p_data,caldata,\
                                                    TaskCenter_607::instance()->get_id(),\
                                                    TaskCenter_607::instance()->get_freqs(),\
                                                    TaskCenter_607::instance()->get_radars());

#endif

#if 0
                std::map<QString,std::pair<double,double> > ls_base;
                QString cur_freq ="9000000000";
                ls_base[cur_freq] = std::pair<double,double>(3.8,-179);
                cur_freq ="10000000000";
                ls_base[cur_freq] = std::pair<double,double>(3.8,-179);
                cur_freq ="11000000000";
                ls_base[cur_freq] = std::pair<double,double>(3.8,-179);

                 TaskCenter_607::instance()->load_delt_mag();

                 double db = -0.5;
                m_cfg_status_dlg::instance()->init_data(ls_org_data.t_cfg_magnphase,\
                                                        ls_org_data.t_cfg_mp_1,\
                                                        set.t_fre_pts,
                                                        TaskCenter_607::instance()->get_delt_mag(),\
                                                        db,ls_base,\
                                                        TaskCenter_607::instance()->get_id());
                if(m_cfg_status_dlg::instance()->exec() == 0 )
                {
                    QString path = QApplication::applicationDirPath() +"/888888888888.txt";
                    m_datamanage.SaveToFile( m_cfg_status_dlg::instance()->get_org_cal(),set.t_fre_pts,path);
                    ls_base =     m_cfg_status_dlg::instance()->get_base_mp();
                    qDebug()<<"ls_base"<<ls_base["9000000000"].first<<ls_base["9000000000"].second;
                    qDebug()<<"ls_base"<<ls_base["10000000000"].first<<ls_base["10000000000"].second;
                    qDebug()<<"ls_base"<<ls_base["11000000000"].first<<ls_base["11000000000"].second;
                }
#endif

            }else
                qDebug()<<"init array error!";
        }else
            qDebug()<<"init map error!";
    }
    m_mode = ON_OPEN;
}

////////////
/// \brief ProjectManager::load_data
/// \param path
/// \param p_data
/// 加载数据
void ProjectManager::load_data(QString path, TDATA &p_data)
{
    QString   ls_path =  path + "/"+ p_data.t_s11_Fname + ORG_SUFFIX;
//    p_data.t_task_s11 =  m_datamanage.ReadFromFile_org(ls_path);

//    ls_path =  path + "/"+ p_data.t_s22_Fname + ORG_SUFFIX;
//    p_data.t_task_s22      =   m_datamanage.ReadFromFile_org(ls_path);

    ls_path =  path + "/"+ p_data.t_s21_Fname + ORG_SUFFIX;
    p_data.t_task_s21      =   m_datamanage.ReadFromFile_org(ls_path);

    ls_path = path +  "/" + p_data.t_mp_Fname   + CAL_MP_SUFFIX ;
    p_data.t_cfg_magnphase =   m_datamanage.ReadFromFile_cmp(ls_path);

    ls_path = path + "/" +  p_data.t_mp_1_Fname + CAL_MP_1_SUFFIC ;
    p_data.t_cfg_mp_1      =   m_datamanage.ReadFromFile_cmp(ls_path);
}

//////////
/// \brief ProjectManager::on_save
/// 保存
void ProjectManager::on_save()
{
    QString param_name = m_proj_path + PARAM_PATH + "/"+ m_cur_name + INI_Suffix;
    QString pro_Name = m_proj_path + "/" + m_cur_name + PROJ_Suffix;
    QFile  file(pro_Name);
    if( file.open(QFile::Append|QFile::Text))
    {
        QTextStream out(&file);
        out<<"";
    }else
        return ;
    if(m_mode != ON_OPEN)
        ParamSetManager::instance()->Save(param_name);
}


/////////////
/// \brief ProjectManager::set_info
/// \param p_path
/// 创建文件夹、设置工程名和路径
void ProjectManager::set_info(QString p_path)
{
    QFileInfo ls_info(p_path);
    QString path = ls_info.absolutePath();
    QString name = ls_info.baseName();
    set_path(path);
    set_name(name);
    Creat_files(path,name);
}

void ProjectManager::set_default_info()
{
    QString path = QApplication::applicationDirPath() + PROJ_PATH;
    QDir pro_dir(path);
    if(!pro_dir.exists())
    {
        pro_dir.mkpath(path);
    }

    path += DEFAULT_PROJ;
    QDir default_dir(path);
    if(!default_dir.exists())
    {
        default_dir.mkpath(path);
    }

    QString proj_name = DEFAULT_PROJ ;
    proj_name += PROJ_Suffix;
    QString full_name = path + proj_name;
    set_info(full_name);
    on_save();
    StatusOutput::instance()->update_proj_name(m_cur_name);
    m_mode = ON_DEF;
}

/////////
/// \brief ProjectManager::Creat_files
/// \param p_path
/// \param proj_name
/// 创建文件夹
void ProjectManager::Creat_files(QString p_path,QString proj_name)
{
    QDir ls_dir(p_path);
    QString param                   = p_path + PARAM_PATH;
    QString data                    = p_path + DATA_PATH;

    QString oRg                     = p_path + ORG_PATH;
    QString cfgmp                   = p_path + CFG_MP_PATH;
    QString cfgmmp                  = p_path + CFG_M_MP_PATH;

    QString file  = p_path + "/" + proj_name + PROJ_Suffix;

    QDir param_(param);
    QDir data_(data);
    QDir ORGDIR(oRg);
    QDir CFGMPDIR(cfgmp);
    QDir CFGMMPDIR(cfgmmp);


    QFile ls_file(file);
    if(!param_.exists())
        ls_dir.mkpath(param);

    if(!data_.exists())
        ls_dir.mkpath(data);

    if(!ORGDIR.exists())
    {
        ls_dir.mkpath(oRg);
    }

    if(!CFGMPDIR.exists())
    {
        ls_dir.mkpath(cfgmp);
    }
    if(!CFGMMPDIR.exists())
    {
        ls_dir.mkpath(cfgmmp);
    }

    ls_file.open(QFile::WriteOnly|QFile::Text);
    QTextStream out(&ls_file);
    QString name = CVTS::GBKToUnicode::toUnicode("工程名：");
    QString time = CVTS::GBKToUnicode::toUnicode("测试时间:");
    QString parame = CVTS::GBKToUnicode::toUnicode("参数文件、阵面文件及映射文件:");
    QString orgdata = CVTS::GBKToUnicode::toUnicode("原始测试数据:");
    QString cfgMP = CVTS::GBKToUnicode::toUnicode("幅度相位一起陪测试数据:");
    QString cfg_M = CVTS::GBKToUnicode::toUnicode("幅相分开配测试数据:");
    QString caldata = CVTS::GBKToUnicode::toUnicode("最终校准文件:");

    out << name<<proj_name<<endl;
    out << time<<QDateTime::currentDateTime().toString("yyyy:MM:dd hh:mm:ss:zzz")<<endl;
    out << parame<<PARAM_PATH<<endl;
    out << orgdata<<PRINTIVE<<endl;
    out << cfgMP<<CFG_MP_PATH<<endl;
    out << cfg_M<<CFG_MP_PATH<<endl;
    out << caldata<<DATA_PATH<<endl;
}



void ProjectManager::set_name(QString t_name)
{
    m_cur_name = t_name;
}


QString &ProjectManager::get_name()
{
    return m_cur_name;
}

void ProjectManager::set_path(QString p_path)
{
    m_proj_path = p_path;
}

QString &ProjectManager::get_path()
{
    return m_proj_path;
}
