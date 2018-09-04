#ifndef VNAACTION_H
#define VNAACTION_H

#include "actions.h"
#include <QtWidgets>
#include "_global.h"
#include <QDebug>
#include "toolbar.h"

/*!
 * \brief The VNAAction class
 *失网菜单类，目前没有使用
 */
class VNAAction : public Actions
{
    Q_OBJECT
public:
    explicit VNAAction(QObject *parent = 0);
    
signals:
  void P_show(QString name,bool isshow);
public slots:
    virtual void register_actions();
//    void show_current_machine(CVTS::MACHINE_TYPE& type);
//    void sel_RS();
//    void sel_Aglient();
private slots:
    void show_PNA_setting_dlg();
    void show_Test_PNA_dlg();
private:
    QAction         *m_setting;
  //  QAction         *m_RS;
  //  QAction         *m_agilent;
  //  QAction         *m_test;
    ToolBar         *toolbar;
};

#endif // VNADAPTER_H
