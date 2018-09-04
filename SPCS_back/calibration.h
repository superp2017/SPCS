#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "actions.h"
#include <QtWidgets>
#include "toolbar.h"

class Calibration : public Actions
{
    Q_OBJECT
public:
    explicit Calibration(QObject *parent = 0);
    
signals:
     void P_show(QString name,bool isshow);
public slots:
    
public slots:
    virtual void register_actions();
    void show_cal_manger_dlg();
    void magn_manager();
    void phase_manager();
    void magn_phase_manager();

private:
    QAction         *m_cal_manager_act;
    QAction         *m_cal_magn_act;
    QAction         *m_cal_phase_act;
    QAction         *m_cal_magn_phase_act;
    ToolBar         *toolbar;

};

#endif // CALIBRATION_H
