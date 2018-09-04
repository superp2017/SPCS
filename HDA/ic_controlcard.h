#ifndef IC_CONTROLCARD_H
#define IC_CONTROLCARD_H

#include <QObject>

class IC_ControlCard : public QObject
{
    Q_OBJECT
public:
    explicit IC_ControlCard(QObject *parent = 0);
    void turn_on_all();
    void turn_off_all();
    void turn_on(int pin);
    void turn_off(int pin);
signals:

public slots:
    void init();
    void close_dev();
private:
    bool        m_is_init;
};

#endif // IC_CONTROLCARD_H
