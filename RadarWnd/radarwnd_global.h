#ifndef RADARWND_GLOBAL_H
#define RADARWND_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RADARWND_LIBRARY)
#  define RADARWNDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RADARWNDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RADARWND_GLOBAL_H
