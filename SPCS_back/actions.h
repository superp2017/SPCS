#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>
#include "delaytask.h"

/*!
 * \brief The Actions class
 * �˵�����Action �Ļ��࣬��������ʱ����
*/
class Actions : public QObject
{
    Q_OBJECT
public:
    explicit Actions(QObject *parent = 0);
    
signals:
    
public slots:
    virtual void register_actions()=0;
};

#endif // ACTIONS_H
