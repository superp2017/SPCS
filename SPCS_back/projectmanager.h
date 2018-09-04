#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QObject>
#include <QtWidgets>
#include "_global.h"
#include <QApplication>
#include "paramsetmanager.h"
#include "m_setfreqdlg.h"
#include "m_setpnadlg.h"
#include "m_selectgallerydlg.h"
#include "m_testinitdlg.h"
#include "m_dampingdlg.h"
#include "statusoutput.h"
#include "m_plottestview.h"
#include "testbackgnd.h"
#include "eleswitch.h"
#include "testresult.h"
#include "datamanage.h"
/*!
 * \file projectmanager.h
 */

/*!
 * \copyright Copyright (C), 2007-2013, Hollywell Electronic System Co.
 */

/*!
 * \author mp
 */

/*!
 * \version 1.0.0
 */

/*!
 * \date 2013-11-25
 */

/*!
 * \brief 工程管理类
 */

/*!
 *  工程管理类：提供工程的创建、打开、保存
 *
 */

enum OPENMODE{ON_NEW,ON_OPEN,ON_DEF};

class ProjectManager : public QObject
{
    Q_OBJECT
protected:
    explicit ProjectManager(QObject *parent = 0);
    ~ProjectManager();
public:
    static ProjectManager *instance()
    {
        static ProjectManager *proj = new ProjectManager();
        return proj;
    }
    static void destory()
    {
        delete instance();
    }

    void on_new(QString path);
    void on_open(QString p_path);
    void on_save();
    void set_path(QString p_path);
    void set_name(QString t_name);
    void reset();
    QString &get_name();
    QString &get_path();
    void set_default_info();
    OPENMODE &get_mode()    {return m_mode;}
private:
    void set_info(QString p_path);
    void Creat_files(QString p_path, QString proj_name);
    void load_data(QString path,TDATA &p_data);
private:
    QString      m_cur_name;
    QString      m_proj_path; 
    DataManage   m_datamanage;
    OPENMODE     m_mode;

};

#endif // PROJECTMANAGER_H
