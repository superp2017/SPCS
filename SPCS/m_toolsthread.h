#ifndef M_TOOLSTHREAD_H
#define M_TOOLSTHREAD_H

#include <QThread>
#include "_global.h"
using namespace CVTS;

/*!
 * \brief The M_ToolsThread class
 * �߳��࣬�������ݲɼ����ȶ��Բ���
 */
class M_ToolsThread : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;
public:
    M_ToolsThread();

signals:
    void testend();
public slots:
    void  T_test(bool iscal);
    void  stop_test();
private:
   volatile bool  m_iscal;
};

#endif // M_TOOLSTHREAD_H
