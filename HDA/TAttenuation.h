#ifndef HANTENNA_H
#define HANTENNA_H
#include "tdevice.h"
#include "hda_global.h"
#include "pci_cardcent.h"



/*!
 * \file tattenuation.h
 */

/*!
 * \copyright Copyright (C), 2007-2013, Hollywell Electronic System Co.
 */

/*!
 * \author mengzhaofeng
 */

/*!
 * \version 1.0.0
 */

/*!
 * \date 2013-08-29
 */


/*!
 * \brief ˥����������
 */

/*!
 *  NI 8495G/H˥�������Ƶ���������״̬��⣬���ü�10dB˥������
 *
 */
using namespace CVTS;
class HDASHARED_EXPORT TAttenuation : public TDevice
{
protected:
    TAttenuation();
public:
    static TAttenuation* instance();
    static void destroy();
    //! ����
    void reset();
    //! ״̬���
    CVTS::CVTS_STATUS status();
    //! 10dB����˥��
    void attenuation(CVTS::NI_ANTENNA na);
    //!����˥�����Ʋɼ���PIN
    void AN_to_PIN(CVTS::NI_ANTENNA na);
};

#endif // HANTENNA_H
