#include "teleswitch.h"
#include "pci_cardcent.h"

TEleSwitch::TEleSwitch()
{

}

TEleSwitch *TEleSwitch::instance()
{
    static TEleSwitch *s_ele_switch = new TEleSwitch;
    return s_ele_switch;
}

void TEleSwitch::destroy()
{
    delete instance();
}

void TEleSwitch::reset()
{
    //    for(int i =0;i<CD_NUMS;++i)
    //    {
    //        PCI_CardCent::instance()->turn_off(i);
    //    }
    //    PCI_CardCent::instance()->setDevice(CARD_0);
    //    PCI_CardCent::instance()->setDevice(CARD_1);
    PCI_CardCent::instance()->turn_off_all(CARD_0);
}

CVTS::CVTS_STATUS TEleSwitch::status()
{
    return m_status;
}

void TEleSwitch::turn_on(CVTS_Decetor sw)
{
    PCI_CardCent::instance()->turn_on(sw);
    //    if(sw == CD_17)
    //        PCI_CardCent::instance()->setDevice(CARD_1);
    //    else
    //        PCI_CardCent::instance()->setDevice(CARD_0);
}

void TEleSwitch::turn_off(CVTS_Decetor sw)
{
    PCI_CardCent::instance()->turn_off(sw);
    //    if(sw == CD_17)
    //        PCI_CardCent::instance()->setDevice(CARD_1);
    //    else
    //        PCI_CardCent::instance()->setDevice(CARD_0);
}

void TEleSwitch::turn_on_all()
{
    //    for(int i =0;i<CD_NUMS;++i)
    //    {
    //        PCI_CardCent::instance()->turn_on(i);
    //    }
    //    PCI_CardCent::instance()->setDevice(CARD_0);
    //    PCI_CardCent::instance()->setDevice(CARD_1);

    PCI_CardCent::instance()->turn_on_all(CARD_0);
}

void TEleSwitch::turn_off_all()
{
    reset();
}

void TEleSwitch::close_dev()
{
    PCI_CardCent::instance()->close_ICCard();
}


