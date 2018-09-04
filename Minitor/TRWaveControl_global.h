#ifndef TRWAVECONTROL_GLOBAL_H
#define TRWAVECONTROL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TRWAVECONTROL_LIBRARY)
#  define TRWAVECONTROLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TRWAVECONTROLSHARED_EXPORT Q_DECL_IMPORT
#endif
#define  DELATYTIME             1000

#define PACKAGE_NUMS            20

#define HEAD_1                  0x55
#define HEAD_2                  0xaa

#define TAIL_1                  0xff
#define TAIL_2                  0xff

#define UDPTEST                 0x0
#define ANTE_INIT               0x1
#define SWITCH_CONTROL          0x2
#define ANTENNA_DATA            0x3
#define DOWN_POWER              0x4
#define MAGNPHASE_C             0x5

typedef struct _TRontrol
{
    qint8          t_col;
    qint8          t_row;
    qint8          t_magn_s;
    qint8          t_phase_s;
    qint8          t_magn_r;
    qint8          t_phase_r;
    bool           t_status;
}TRontrol;


typedef struct _PACK
{
    uchar     t_pack[PACKAGE_NUMS];
}PACKAGE;



#endif // TRWAVECONTROL_GLOBAL_H
