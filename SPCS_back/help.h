#ifndef HELP_H
#define HELP_H

#include "actions.h"
#include <QtWidgets>
#include <QMessageBox>


/*!
 * \brief The Help class
 * ∞Ô÷˙≤Àµ•¿‡
 */
class Help : public Actions
{
    Q_OBJECT
public:
    explicit Help(QObject *parent = 0);
    
signals:

public slots:
    virtual void register_actions();
    void on_Version();
    void on_UserMannual();
    void on_install();
private:
    QAction         *m_version_act;
    QAction         *m_user_mannul_act;
    QAction         *m_install_mannul;
};

#endif // HELP_H
