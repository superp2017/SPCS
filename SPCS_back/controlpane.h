#ifndef CONTROLPANE_H
#define CONTROLPANE_H

#include <QtWidgets>
#include "m_setfreqdlg.h"
/*!
 * \brief The ControlPane class
 * 主界面的控制面板
 *
 */
class ControlPane : public QWidget
{
    Q_OBJECT
protected:
    explicit ControlPane(QWidget *parent = 0);

public:
    static ControlPane* instance(QWidget *parent = 0)
    {
        static ControlPane* s_pane = new ControlPane(parent);
        return s_pane;
    }
    static void destroy()
    {
        delete instance();
    }
    
signals:
    void trouble_check();
    void face_analy();
    void face_import();
    void test_init();
    void freq_set();
    void setdev();
    void test_result();
    void begin();
    void pause(bool pause);
    void stoptest();
public slots: 
    void init();
    void inner_begin();
    void inner_stop();
    void inner_pause();
    void default_mode();
    void CreatNew_mode();
    void TestEnd_mode();
    void open_mode();
protected:
    void setbuttonsenable(bool enable);

private:
    QGridLayout         m_grid_layout;
    QPushButton         *m_array_set_btn;
    QPushButton         *m_test_init_btn;
    QPushButton         *m_an_btn;
    QPushButton         *m_freq_btn;
    QPushButton         *m_testresult_btn;
    QPushButton         *m_array_anay_btn;
    QPushButton         *m_unit_trouble_btn;
    QPushButton         *m_begin_btn;
    QPushButton         *m_pause_btn;
    QPushButton         *m_stop_btn;
    bool                m_paused;
};

#endif // CONTROLPANE_H
