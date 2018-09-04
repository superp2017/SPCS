#ifndef TSWMATRIXS_H
#define TSWMATRIXS_H
#include "tdevice.h"
#include "hda_global.h"
#include <QCoreApplication>


/*!
 * \file TSWMatrixs.h
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
 * \brief ���ؾ��������
 */

/*!
 *  ���ؾ���NI87106B���Ƶ���������1/16
 *
 */

class HDASHARED_EXPORT TSWMatrixs : public TDevice
{
protected:
    TSWMatrixs();
public:
    static TSWMatrixs* instance();
    static void destroy();
    void reset();
    CVTS::CVTS_STATUS status();
    void turn_on(Matrix sw);
    void turn_off_all();

private:
};

#endif // TSWMATRIXS_H
