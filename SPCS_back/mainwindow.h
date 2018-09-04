#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "testbackgnd.h"
#include <map>
#include <set>
#include <list>
#include "projectmanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    static MainWindow* instance(MainWindow* mainWindow = 0)
    {
        static MainWindow *s_mainWindow = mainWindow;
        return s_mainWindow;
    }

    void register_menu(const QString &menu, QAction *act);
    void register_menu(const QString &menu_pa, const QString &menu);
    void insertSeparator(const QString &menu, QAction *act);
    void register_tool(QAction *act);
    void register_ToolBar(QString name, QAction *act,QToolBar* toolbar);
    void close_progress();
    void show_bar(QString p_name, bool checked);
    bool isQuit(){return m_quit;}
protected:
    virtual void closeEvent(QCloseEvent *e);
    void ALl_destory();
private:
    TestBackgnd                                     m_bkgnd;
    std::map<QString, QMenu*>                       m_menus;
    std::map<QString, QToolBar*>                    m_toolbars;
    std::set<QAction*>                              m_tools;
    bool                                            m_quit;
};

#endif // MAINWINDOW_H
