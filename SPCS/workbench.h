#ifndef WORKBENCH_H
#define WORKBENCH_H

#include <QtWidgets>
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>


/*!
 * \brief The WorkBench class
 * 工作区域类，用于加载不同的界面
 */
class WorkBench : public QWidget
{
    Q_OBJECT
protected:
    explicit WorkBench(QWidget *parent = 0);
    
public:
    static WorkBench* instance()
    {
        static WorkBench* s_bench = new WorkBench();
        return s_bench;
    }

    static void destroy()
    {
        delete instance();
    }
signals:
    void change_btn_full();
    void change_btn_normal();

public slots:
    void show_radar_face();
    void show_result_area();
    void show_radar_analy();
    void show_init_dlg();
    void show_dev();
    void show_setfreq_dlg();
    void show_result_fullscreen();
    void show_result_normal();
    void init_widget();
    void trouble_check();
protected:
    void keyPressEvent(QKeyEvent *e);
    void show_workarea(QWidget *widget);


private:
    QWidget         *m_widget;
};

#endif // WORKBENCH_H
