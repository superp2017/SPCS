#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>
#include "delaytask.h"

/*!
 * \brief The Actions class
 * 菜单栏的Action 的基类，用来做延时加载
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
