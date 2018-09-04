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
 * \brief ���ӿ��ؿ�����
 */

/*!
 *  FSS���ӿ��ؿ��Ƶ����ɶԵ����ؽ��п��ز�������ɶ����п��ؽ��п��ز���
 *
 */

using namespace CVTS;
class HDASHARED_EXPORT TEleSwitch : public TDevice
{
protected:
    TEleSwitch();

public:

public:
    //! ��������
    static TEleSwitch* instance();
    //! ��������
    static void destroy();

    //! ״̬����
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
