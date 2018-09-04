#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QtWidgets>


/*!
 * \brief The StatusBar class
 * ������״̬��
 */
class StatusBar : public QStatusBar
{
    Q_OBJECT
protected:
    explicit StatusBar(QWidget *parent = 0);

public:
    static StatusBar* instance();
    static void destroy();
    
signals:
    
public slots:

protected:
    virtual void paintEvent(QPaintEvent *);
    
};

#endif // STATUSBAR_H
