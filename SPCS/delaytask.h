#ifndef DELAYTASK_H
#define DELAYTASK_H

#include <QObject>
/*!
 * \brief The DelayTask class
 *
 * 做延时任务的加载
 */
class DelayTask : public QObject
{
    Q_OBJECT
protected:
    explicit DelayTask(QObject *parent = 0);
    
public:
    static DelayTask* instance()
    {
        static DelayTask* s_task = new DelayTask();
        return s_task;
    }
    static void destroy()
    {
        delete instance();
    }
public:
    void do_delay_task();
signals:
    void tigger_delay_task();
public slots:
    
};

#endif // DELAYTASK_H
