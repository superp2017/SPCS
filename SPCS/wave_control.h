#ifndef WAVE_CONTROL_H
#define WAVE_CONTROL_H

#include "actions.h"
#include <QtWidgets>
#include "toolbar.h"
/*!
 * \brief The Wave_Control class
 * ²¨¿Ø·Ö»úActionÀà
 */
class Wave_Control : public Actions
{
    Q_OBJECT
public:
    explicit Wave_Control(QObject *parent = 0);
signals:
    void P_show(QString name,bool isshow);
public slots:
    virtual void register_actions();
    void manual_operation();

private:
    QAction         *m_unit_test_act;
    QAction         *m_manual_operation_act;
    ToolBar         *toolbar;
};

#endif // WAVE_CONTROL_H
