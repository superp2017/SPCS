#include "pci_cardcent.h"
#include "test_comm.h"
#include <QSettings>


PCI_CardCent::PCI_CardCent(QObject *parent) :
    QObject(parent)
{   
    init_IC_card();

    m_card_1.init(0);
    m_card_2.init(1);


}

PCI_CardCent::~PCI_CardCent()
{
}

void PCI_CardCent::init_IC_card()
{
    connect(&m_thread,SIGNAL(started()),&m_card_0,SLOT(init()));
    m_card_0.moveToThread(&m_thread);
    m_thread.start();
}

void PCI_CardCent::turn_on(int n)
{
    if(n >= 0 && n<=CARD_PIN_NUMS)
        m_card_0.turn_on(n);
    else if(n > CARD_PIN_NUMS && n< CARD_PIN_NUMS*2)
        m_card_1.turn_on(n-CARD_PIN_NUMS);
    else if(n >= CARD_PIN_NUMS*2 && n< CARD_PIN_NUMS*3)
        m_card_2.turn_on(n-CARD_PIN_NUMS*2);
    else return;
}

void PCI_CardCent::turn_off(int n)
{
    if(n >= 0 && n<CARD_PIN_NUMS)
        m_card_0.turn_off(n);
    else if(n >= CARD_PIN_NUMS && n< CARD_PIN_NUMS*2)
        m_card_1.turn_off(n-CARD_PIN_NUMS);
    else if(n >= CARD_PIN_NUMS*2 && n< CARD_PIN_NUMS*3)
        m_card_2.turn_off(n-CARD_PIN_NUMS*2);
    else return;
}

void PCI_CardCent::turn_off_all(CARDINDEX index)
{
    if(index == CARD_0 )
        m_card_0.turn_off_all();
    if(index == CARD_1 )
        m_card_1.turn_off_all();
    if(index == CARD_2 )
        m_card_2.turn_off_all();
}

void PCI_CardCent::turn_on_all(CARDINDEX index)
{
    if(index == CARD_0 )
        m_card_0.turn_on_all();
    if(index == CARD_1 )
        m_card_1.turn_on_all();
    if(index == CARD_2 )
        m_card_2.turn_on_all();
}

void PCI_CardCent::setDevice(CARDINDEX index)
{
    //    if(index == CARD_0 )
    //        m_card_0.setDeviceDO();
    if(index == CARD_1 )
        m_card_1.setDeviceDO();
    if(index == CARD_2 )
        m_card_2.setDeviceDO();
}

void PCI_CardCent::close_ICCard()
{
    m_card_0.close_dev();
}

