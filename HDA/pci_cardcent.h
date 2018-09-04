#ifndef PCI_CARDCENT_H
#define PCI_CARDCENT_H

#include <QObject>
#include  "rebpci2323.h"
#include "ic_controlcard.h"
#include <QThread>

class HDASHARED_EXPORT PCI_CardCent : public QObject
{
    Q_OBJECT
protected:
    explicit PCI_CardCent(QObject *parent = 0);
    ~PCI_CardCent();
public:
    static PCI_CardCent * instance()
    {
        static PCI_CardCent* cent = new PCI_CardCent();
        return cent;
    }
    static void destory()
    {
        delete instance();
    }
    void turn_on(int n);
    void turn_off(int n);
    void turn_off_all(CARDINDEX index);
    void turn_on_all(CARDINDEX index);
    void setDevice(CARDINDEX index);
    void close_ICCard();
private:
    void init_IC_card();
signals:
    
public slots:
private:
    IC_ControlCard            m_card_0;
 // RebPCI2323                m_card_0;
    RebPCI2323                m_card_1;
    RebPCI2323                m_card_2;
    QThread                   m_thread;

    
};

#endif // PCI_CARDCENT_H
