#ifndef M_CFG_STATUS_THREAD_H
#define M_CFG_STATUS_THREAD_H

#include <QThread>

/*!
 * \brief The m_CFG_STATUS_THread class
 * 线程类,用于人工修改基准值界面
 */
class m_CFG_STATUS_THread : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;
public:
    explicit m_CFG_STATUS_THread(QObject *parent = 0);
    
signals:
    
public slots:
    void CALC(bool pismagn);
private:
      volatile bool  m_ismagn;
};

#endif // M_CFG_STATUS_THREAD_H
