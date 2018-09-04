#ifndef PORTCHANGETHREAD_H
#define PORTCHANGETHREAD_H

#include <QThread>

class PortChangeThread : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;
protected:
    PortChangeThread();
  public :
    static PortChangeThread * instance()
    {
        static PortChangeThread *tread = new PortChangeThread;
        return tread;
    }
    static void destory()
    {
        delete instance();
    }

signals:
    void testend();
public slots:
    void  T_test();
};


#endif // PORTCHANGETHREAD_H
