#ifndef MULTISWITCH_H
#define MULTISWITCH_H

#include "actions.h"
#include <QtWidgets>
#include "toolbar.h"

/*!
 * \brief The MultiSwitch class
 *多路开关Action 类
 */
class MultiSwitch : public Actions
{
    Q_OBJECT
public:
    explicit MultiSwitch(QObject *parent = 0);
    
signals:
    void P_show(QString name,bool isshow);
public slots:
    

public slots:
    virtual void register_actions();
    void show_SelectGallery_dlg();
    void init_dlg();

private:
    QAction             *m_channel_act;
    QAction             *m_close_all_act;
    ToolBar             *toolbar;
};

#endif // MULTISWITCH_H
