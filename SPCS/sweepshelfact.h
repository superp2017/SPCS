#ifndef SWEEPSHELFACT_H
#define SWEEPSHELFACT_H

#include "actions.h"
#include <QtWidgets>
#include "toolbar.h"
#include "sweepshelfcontrol.h"


/*!
 * \brief The SweepShelfAct class
 * …®√Ëº‹Action
 */
class SweepShelfAct : public Actions
{
    Q_OBJECT
public:
    explicit SweepShelfAct(QObject *parent = 0);
    
signals:
    void P_show(QString name,bool isshow);
public slots:
    void P_reset();
    void p_control();
public slots:
    virtual void register_actions();
    
private:
    QAction             *m_reset_act;
    QAction             *m_control_act;
    ToolBar             *toolbar;
    SweepShelfControl    m_control;
};

#endif // SWEEPSHELFACT_H
