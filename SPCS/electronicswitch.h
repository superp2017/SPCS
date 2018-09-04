#ifndef ELECTRONICSWITCH_H
#define ELECTRONICSWITCH_H
#include "actions.h"
#include <QtWidgets>
 #include "toolbar.h"
#include "controlelecswitch.h"


/*!
 * \brief The ElectronicSwitch class
 * 电子开关的菜单类
 */
class ElectronicSwitch : public Actions
{
    Q_OBJECT
public:
    explicit ElectronicSwitch(QObject *parent = 0);

signals:
    void P_show(QString name,bool isshow);
public slots:


public slots:
    virtual void register_actions();
    void settings();

private:
    QAction             *m_close_all_act;
    QAction             *m_control_act;
    ToolBar             *toolbar;
};

#endif // ELECTRONICSWITCH_H
