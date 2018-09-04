#ifndef CONFIGPHASE_GLOBAL_H
#define CONFIGPHASE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CONFIGPHASE_LIBRARY)
#  define CONFIGPHASESHARED_EXPORT Q_DECL_EXPORT
#else
#  define CONFIGPHASESHARED_EXPORT Q_DECL_IMPORT
#endif

#define UP_DB   -20
#define DOWN_DB -80
#define DELTMAG_PATH "/config/delt_mag.res"

#endif // CONFIGPHASE_GLOBAL_H
