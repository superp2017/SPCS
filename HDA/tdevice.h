#ifndef TDEVICE_H
#define TDEVICE_H

#include "hda_global.h"
#include <QObject>
/*!
 * \file tdevice.h
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
 * \brief �豸����
 */

/*!
 *  �豸���࣬�ṩ״̬���
 *
 */

class HDASHARED_EXPORT TDevice
{
protected:
    TDevice();

    virtual ~TDevice();

public:
    virtual CVTS::CVTS_STATUS status()=0;
protected:
    CVTS::CVTS_STATUS   m_status;   /// ״̬��ʶ
};

#endif // TDEVICE_H
