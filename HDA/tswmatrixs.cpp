#include "pci_cardcent.h"
#include "tswmatrixs.h"

TSWMatrixs::TSWMatrixs()
{

}

TSWMatrixs *TSWMatrixs::instance()
{
    static TSWMatrixs* s_sw_matrix = new TSWMatrixs;
    return s_sw_matrix;
}

void TSWMatrixs::destroy()
{
    delete instance();
}

void TSWMatrixs::reset()
{
    for(int i =S_1;i<SWNum;++i)
    {
        PCI_CardCent::instance()->turn_off(SwitchMatrix(i));
    }
    PCI_CardCent::instance()->setDevice(CARD_1);
    PCI_CardCent::instance()->setDevice(CARD_2);
}


CVTS::CVTS_STATUS TSWMatrixs::status()
{
    return m_status;
}

void TSWMatrixs::turn_on(Matrix sw)
{
    reset();

    if(sw>=0 && sw <3)
    {
        PCI_CardCent::instance()->turn_on(S_1);
    }
    else  if(sw >=3 && sw <6)
    {
        PCI_CardCent::instance()->turn_on(S_20);
    }
    else if(sw >=6 && sw <9)
    {
        PCI_CardCent::instance()->turn_on(S_1);
    }
    else if(sw >=9 && sw <12)
    {
        PCI_CardCent::instance()->turn_on(S_20);
    }
    else if(sw >= 12 && sw < M_NUMS)
    {
        PCI_CardCent::instance()->turn_on(S_3);
    }else{qDebug()<<"Matrix switch turn on failed  !" ;
        return ;
    }

    PCI_CardCent::instance()->turn_on(S_1 + sw + 3);

   // if(sw >11)
        PCI_CardCent::instance()->setDevice(CARD_2);
   // else
        PCI_CardCent::instance()->setDevice(CARD_1);
}


void TSWMatrixs::turn_off_all()
{
    reset();
    PCI_CardCent::instance()->turn_on(S_2);
    PCI_CardCent::instance()->setDevice(CARD_2);
  //  PCI_CardCent::instance()->turn_off(S_20);
   // PCI_CardCent::instance()->setDevice(CARD_2);
}


