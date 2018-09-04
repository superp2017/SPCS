#ifndef TESTIMPL_H
#define TESTIMPL_H
#include "vnaaction.h"
#include "electronicswitch.h"
#include "sweepshelfact.h"
#include "multiswitch.h"
#include "calibration.h"
#include "help.h"
#include "wave_control.h"
#include "view.h"
#include <QObject>
#include "files.h"
#include "tools.h"


/*!
 * \brief The TestImpl class
 * 此类用于加载每个菜单项
 */
class TestImpl : public QObject
{
    Q_OBJECT
protected:
    TestImpl(QObject *w = 0);

public:
    static TestImpl* instance();
    static void destroy();
public slots:
    void Set_act(QString p_name,bool flag);
public:
    void start();
    void init_attenuator();
    void init_electronic_switch();
    void init_multi_switch();
    void init_radar_controller();
    void set_vna();
    void set_attenuator();
    void set_antenna();
    void set_electronic_switch();
    void set_multi_switch();
    void set_sweep_shelf();
    void check_vna_net();
    void check_antenna_s11();
    void check_detector_s11();
    void valid_sweep_order();
    void before_test();
    void begin_test();
    void after_test();
    void valid_config_phase();
    void stop();
protected:
    void config_phase();
    void gen_before_config_phase_graphice();
    void gen_after_config_phase_graphice();

private:
    Files                   m_files;
    View                    m_view;
    ElectronicSwitch        m_ele_switch;
    SweepShelfAct           m_Shelf;
    MultiSwitch             m_multi_switch;
    Wave_Control            m_control;
    Tools                   m_tools;
    Help                    m_help;

};

#endif // TESTIMPL_H
