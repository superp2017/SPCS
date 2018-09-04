#ifndef TELESWITCH_H
#define TELESWITCH_H
#include "tdevice.h"
#include "hda_global.h"
#include <QCoreApplication>


/*!
 * \file teleswitch.h
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
 * \brief 电子开关控制类
 */

/*!
 *  FSS电子开关控制单例可对单开关进行开关操作，亦可对所有开关进行开关操作
 *
 */

using namespace CVTS;
class HDASHARED_EXPORT TEleSwitch : public TDevice
{
protected:
    TEleSwitch();

public:

public:
    //! 单例创建
    static TEleSwitch* instance();
    //! 单例销毁
    static void destroy();

    //! 状态重置
    void reset();
    //!
    CVTS::CVTS_STATUS status();
    //!
    void turn_on(CVTS_Decetor sw);
    //!
    void turn_off(CVTS_Decetor sw);
    //!
    void turn_on_all();
    //!
    void turn_off_all();
    void close_dev();

private:
};

#endif // TELESWITCH_H
