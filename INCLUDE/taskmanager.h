#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QtCore/qglobal.h>

#if defined(TASKMANAGER_LIBRARY)
#  define TASKMANAGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TASKMANAGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#include <boost/asio.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/container/deque.hpp>
#include <vector>
#include <boost/asio.hpp>
#include <QAtomicInt>

/*!
 * \brief 任务管理器
 */

/*!
 * \file taskmanager.h
 */

/*!
 * \copyright Copyright (C), 2008-2013, Hollywell Electronic System Co.
 */

/*!
 * \author mengzhaofeng
 */

/*!
 * \version 1.0.0
 */

/*!
 * \date 2013-04-09
 */

/*!
 * \brief 任务管理器类
 */

/*!
 * 可以接受一般函数、成员函数、静态函数，函数内资源同步由使用者维护，管理器不做函数的同步控制。
 */

/*!
 * \brief The Handler class
 */
class Handler
{
public:
    virtual void operator()() = 0;
};

/*!
 * \brief The TaskHandler class
 */
template<class _T>
class TaskHandler : public Handler
{
public:
    typedef typename _T     Handler;
    typedef TaskHandler     Self;
    TaskHandler(Handler &handler): t_op(handler){}
    void operator()()
    {
        t_op();
    }
    Handler     t_op;
};



/*!
 * \brief The TaskManager class
 */
class TASKMANAGERSHARED_EXPORT TaskManager
{
    typedef boost::mutex                                    mutex;
    typedef boost::mutex::scoped_lock                       scoped_lock;
    typedef boost::try_mutex                                try_mutex;
    typedef boost::try_mutex::scoped_try_lock               try_scoped_lock;
    struct TaskNode
    {
        try_mutex                                           t_mutex;
        boost::container::deque<Handler*>                   t_task_queue;
        ~TaskNode()
        {
            scoped_lock(t_mutex);
            boost::container::deque<Handler*>::iterator ls_iter = t_task_queue.begin();
            while(ls_iter != t_task_queue.end())
            {
                delete *ls_iter;
                ls_iter++;
            }
            t_task_queue.clear();
        }
    };
private:
    TaskManager(int pn);
    ~TaskManager();

public:
    static TaskManager* instance(int pn = 4)
    {
        static TaskManager s_task(pn);
        return &s_task;
    }
    void start();
    void stop();

    Handler* get_job();

    void do_job();

    template<class _T>
    void post(_T p_handler)
    {
        typedef TaskHandler<_T> THandler;
        THandler *p = new THandler(p_handler);
        post_task(p);
    }

protected:
    void post_task(Handler *handler);
    void run();

private:
    boost::asio::io_service             m_services;
    std::vector<TaskNode*>              m_task_vector;
    QAtomicInt                          m_task_num;
    int                                 m_pn;
    QAtomicInt                          m_cur_id;
    boost::asio::io_service             m_io_service;
    boost::condition                    m_condition;
    mutex                               m_mutex;
    bool                                m_running;
    boost::thread                       *m_main_thread;
};

#endif // TASKMANAGER_H
