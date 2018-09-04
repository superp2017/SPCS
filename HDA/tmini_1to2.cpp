#include "tmini_1to2.h"
#include "pci_cardcent.h"

TMini_1TO2::TMini_1TO2()
{
}

void TMini_1TO2::turn_on_off(bool on)
{
    if(on)
        PCI_CardCent::instance()->turn_on(MINI);
    else
        PCI_CardCent::instance()->turn_off(MINI);
}

CVTS_STATUS TMini_1TO2::status()
{
    return m_status;
}
