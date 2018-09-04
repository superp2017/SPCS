#include "m_calmanager.h"

M_CalManager::M_CalManager(QObject *parent) :
    QObject(parent)
{

}

M_CalManager *M_CalManager::instance()
{
    static M_CalManager *s_cal = new M_CalManager();
    return s_cal;
}

void M_CalManager::destory()
{
    delete instance();
}

QList<QString> M_CalManager::BaseLib()
{
      return get_files(CALBASEPATH);
}

QList<QString> M_CalManager::UserLib()
{
     return get_files(CALUSERPATH);
}

void M_CalManager::open_calibration(QString &file)
{
    QString p_path;
    QDir dir1(CALBASEPATH);
    QDir dir2(CALUSERPATH);
    bool exist  = dir1.exists(file);
    bool exist2 = dir2.exists(file);
    if(exist)
    {
        p_path = CALBASEPATH + file;
        open_file(p_path);
    }
    if(exist2)
    {
        p_path = CALUSERPATH + file;
        open_file(p_path);
    }else return;
}


QList<QString> M_CalManager::get_files(const char *path)
{
    QList<QString>  ls_res;
    QString dir_path = QString(path);
    QFileInfo file(dir_path);
    if(!file.isDir()) return  QList<QString>();
    QDir m_dir(dir_path);
    QStringList filters;
    filters << "*.cal";
    QFileInfoList list = m_dir.entryInfoList(filters,QDir::Files | QDir::Readable | QDir::NoSymLinks |QDir::Writable);
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo ls_file= list.at(i);
        if(ls_file.isFile())
        {
            ls_res.push_back(ls_file.fileName());
        }
    }
    return ls_res;
}

void M_CalManager::open_file(QString &path)
{
    QFileInfo fileinfo(path);
    bool ret =fileinfo.isFile();
    if(ret)
    {
        QString cmd_ =QString("notepad ") + path;
        bool complete= m_process.startDetached(cmd_);
        if(!complete) return;
    }else
        return;
}

void M_CalManager::rename_file(QString &path)
{
    QFileInfo fileinfo(path);
    bool ret =fileinfo.isFile();
    if(ret)
    {
        QFile file(path);
        QString  name =fileinfo.fileName() + ".bak";
        QString rename = QString("./BaseLib/") + name;
        file.rename(rename);
    }else
        return;
}
