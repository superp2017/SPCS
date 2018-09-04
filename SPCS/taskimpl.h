#ifndef TASKIMPL_H
#define TASKIMPL_H

#include <QtWidgets>
#include <map>
#include "m_cfg_status_dlg.h"


/*!
 * \brief The TaskImpl class
 * 测试流程的线程
 */
class TaskImpl : public QThread
{
    Q_OBJECT
    enum ImplStatus{RUNNing, Paused, Stoped};

    void run() Q_DECL_OVERRIDE;
protected:
    explicit TaskImpl(QThread *parent = 0);
    ~TaskImpl();
public:
    static TaskImpl* instance();
    static void destroy();


    void reset();
    bool is_paused();
signals:
    void task_impl_finish();
    void trigger_monitor();
    void Panebeign();
    void test_stop();

public slots:
    void begin();
    void stop();
    void pause(bool is_pause);
    void continue_run();
    void show_monitor();
    void show_array();
    void wave_connect_failed();
    void VNA_connect_failed();
    void SHOW_CAL_STATUS();
    void Serialport_connect_failed();

private:
    ImplStatus                                  m_status;
    int                                         m_begin_id;
    int                                         m_stop_id;
    int                                         m_paused;
    QMutex                                      m_mutex;
    bool                                        m_isconnect;

};

#endif // TASKIMPL_H
