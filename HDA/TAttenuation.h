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
 * \brief 衰减器控制类
 */

/*!
 *  NI 8495G/H衰减器控制单例，包括状态检测，重置及10dB衰减步进
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
    //! 重置
    void reset();
    //! 状态检测
    CVTS::CVTS_STATUS status();
    //! 10dB步进衰减
    void attenuation(CVTS::NI_ANTENNA na);
    //!根据衰减控制采集卡PIN
    void AN_to_PIN(CVTS::NI_ANTENNA na);
};

#endif // HANTENNA_H
