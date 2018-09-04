#ifndef HDA_GLOBAL_H
#define HDA_GLOBAL_H

#include <QtCore/qglobal.h>
#include "_global.h"
#include <QDebug>

#if defined(HDA_LIBRARY)
#  define HDASHARED_EXPORT Q_DECL_EXPORT
#else
#  define HDASHARED_EXPORT Q_DECL_IMPORT
#endif

#define CARD_PIN_NUMS      16
#define ALL_PIN_NUMS       45

using namespace CVTS ;

enum CARDINDEX{CARD_0,CARD_1,CARD_2};


#endif // HDA_GLOBAL_H
