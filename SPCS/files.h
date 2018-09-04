#ifndef FILES_H
#define FILES_H
#include "actions.h"
#include <QtWidgets>
#include <QFile>
#include <QFileDialog>
#include "toolbar.h"
#include "projectmanager.h"
#include "controlpane.h"

/*!
 * \brief The Files class
 * 文件菜单类
 */

class Files : public Actions
{
    Q_OBJECT
public:
    explicit Files(QObject *parent = 0);   
signals:
    void P_show(QString name,bool isshow);
public slots:
    void on_new();
    void on_open();
    void on_save();
    void on_exit();
    virtual void register_actions();
private:
    QAction     *m_new_act;
    QAction     *m_open_act;
    QAction     *m_save_act;
    QAction     *m_exit_act;
    ToolBar     *toolbar;    
};

#endif // FILES_H
