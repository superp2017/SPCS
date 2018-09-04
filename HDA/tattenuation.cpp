#include "tattenuation.h"

TAttenuation::TAttenuation()
{
}

TAttenuation *TAttenuation::instance()
{
    static TAttenuation* s_atten = new TAttenuation;
    return s_atten;
}

void TAttenuation::destroy()
{
    delete instance();
}


void TAttenuation::attenuation(NI_ANTENNA na)
{
    AN_to_PIN(na);
}


void TAttenuation::AN_to_PIN(NI_ANTENNA na)
{
    for(int i =0;i<(ANNUMS-AN_1);++i)
    {
        PCI_CardCent::instance()->turn_off(i + AN_1);
    }

    if(na == AN_ZERO)
    {
        PCI_CardCent::instance()->turn_off(AN_1);
        PCI_CardCent::instance()->turn_off(AN_2);
        PCI_CardCent::instance()->turn_off(AN_3);
    }
    if(na == AN_10)
    {
        PCI_CardCent::instance()->turn_on(AN_1);
        PCI_CardCent::instance()->turn_off(AN_2);
        PCI_CardCent::instance()->turn_off(AN_3);
    }
    if(na == AN_20)
    {
        PCI_CardCent::instance()->turn_off(AN_1);
        PCI_CardCent::instance()->turn_on (AN_2);
        PCI_CardCent::instance()->turn_off(AN_3);
    }
    if(na == AN_30)
    {
        PCI_CardCent::instance()->turn_on(AN_1);
        PCI_CardCent::instance()->turn_on (AN_2);
        PCI_CardCent::instance()->turn_off(AN_3);
    }
    if(na == AN_40)
    {
        PCI_CardCent::instance()->turn_off(AN_1);
        PCI_CardCent::instance()->turn_off(AN_2);
        PCI_CardCent::instance()->turn_on(AN_3);
    }
    if(na == AN_50)
    {
        PCI_CardCent::instance()->turn_on(AN_1);
        PCI_CardCent::instance()->turn_off(AN_2);
        PCI_CardCent::instance()->turn_on(AN_3);

    }
    if(na == AN_60)
    {
        PCI_CardCent::instance()->turn_off(AN_1);
        PCI_CardCent::instance()->turn_on(AN_2);
        PCI_CardCent::instance()->turn_on(AN_3);
    }
    if(na == AN_70)
    {
        PCI_CardCent::instance()->turn_on(AN_1);
        PCI_CardCent::instance()->turn_on(AN_2);
        PCI_CardCent::instance()->turn_on(AN_3);
    }
    PCI_CardCent::instance()->setDevice(CARD_2);
}


void TAttenuation::reset()
{    
    attenuation(AN_ZERO);
}

CVTS::CVTS_STATUS TAttenuation::status()
{
    return m_status;
}
