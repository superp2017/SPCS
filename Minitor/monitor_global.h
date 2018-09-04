#ifndef MONITOR_GLOBAL_H
#define MONITOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MONITOR_LIBRARY)
#  define MONITOR_EXPORT Q_DECL_EXPORT
#else
#  define MONITOR_EXPORT Q_DECL_IMPORT
#endif


#endif // MONITOR_GLOBAL_H
