#ifndef TOOLS_H
#define TOOLS_H
#include "actions.h"
#include <QAction>
#include "toolbar.h"
#include "handlecontrol.h"
#include "m_stabletools.h"
#include "m_caldiffer_tools.h"
#include "combinetools.h"

/*!
 * \brief The Tools class
 * 工具菜单类
 */
class Tools : public Actions
{
    Q_OBJECT
public:
    explicit Tools(QObject *parent = 0);
    
signals:
    void P_show(QString name,bool isshow);
public slots:
    void on_coltrol();
    void on_cal();
    void on_stable();
    void on_differ();
    void on_combine();
    void portchange();
    virtual void register_actions();
private:
    QAction                  *m_control;
    QAction                  *m_cal_libs;
    QAction                  *m_stable_tools;
    QAction                  *m_caldiffer_tools;
    QAction                  *m_combine_tools;
    QAction                  *m_portchange_tools;
    ToolBar                  *toolbar;
    M_StableTools            m_stabletools;
    M_CalDiffer_tools        m_differ_tools;
    CombineTools             m_combine;
    
};

#endif // TOOLS_H
