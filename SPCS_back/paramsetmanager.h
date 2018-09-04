#ifndef PARAMSETMANAGER_H
#define PARAMSETMANAGER_H

#include <QObject>
#include <QString>
#include <QSettings>
#include "_global.h"
#include <QStringList>


using namespace CVTS;


/*!
 * \file paramsetmanager.h
 */

/*!
 * \copyright Copyright (C), 2007-2013, Hollywell Electronic System Co.
 */

/*!
 * \author Mp
 */

/*!
 * \version 1.0.0
 */

/*!
 * \date 2013-11-18
 */

/*!
 * \brief �������ù�����
 */

/*!
 *  �ṩ��ȡ��ǰ���в���,�������,ָ���ļ���ȡ��Ӧ�Ĳ���,���ز��� ��;
 *
 */
class ParamSetManager : public QObject
{
    Q_OBJECT
protected:
    explicit ParamSetManager(QObject *parent = 0);
    ~ParamSetManager();
public:
    static ParamSetManager *instance()
    {
        static ParamSetManager  *param = new ParamSetManager();
        return param;
    }
    static void destory()
    {
        delete instance();
    }
public slots:
    void Save(QString path);
    void Read(QString p_path,Param_sets &set);
    void Reload(Param_sets &set);
    Param_sets &get_Param();
private slots:
    void fill_param();
private:
    Param_sets      m_param;
};

#endif // PARAMSETMANAGER_H
