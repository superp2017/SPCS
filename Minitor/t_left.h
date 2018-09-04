#ifndef T_LEFT_H
#define T_LEFT_H

#include <QtWidgets>

class T_Left : public QWidget
{
    Q_OBJECT
public:
    explicit T_Left(QWidget *parent = 0);
    
signals:
    
public slots:
    void Set_up_widget(QWidget *up_);
    void Set_down_widget(QWidget *down_);
private:
    void set_layout();
    QWidget         *m_up;
    QWidget         *m_down;
    QGridLayout     m_grid_layout;
};

#endif // T_LEFT_H
