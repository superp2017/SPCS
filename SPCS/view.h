#ifndef VIEW_H
#define VIEW_H
#include <QtWidgets>
#include "actions.h"
#include "_global.h"
#include "mainwindow.h"

/*!
 * \brief The View class
 *  ”Õº≤Àµ•¿‡
 */
class View : public Actions
{
    Q_OBJECT
public:
    explicit View(QObject *parent = 0);

public slots:
    virtual void register_actions();
    void    Set_act_checked(QString t_name,bool checked);
private slots:
    void          on_show_file();
    void          on_show_elecswitch();
    void          on_show_scanning();
    void          on_show_selectgallery();
    void          on_show_wave();
private:
    QAction       *m_show_file;
    QAction       *m_show_elecswitch;
    QAction       *m_scanning;
    QAction       *m_selectgallery;
    QAction       *m_wave;
    QString       SView;
    QString       Sfile;
    QString       Svna;
    QString       Selec;
    QString       Sscanning;
    QString       Sgallery;
    QString       Swvae;
    std::map<QString,QAction*> m_actions;
};

#endif // VIEW_H
