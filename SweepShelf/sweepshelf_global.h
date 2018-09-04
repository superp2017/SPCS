#ifndef SWEEPSHELF_GLOBAL_H
#define SWEEPSHELF_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SWEEPSHELF_LIBRARY)
#  define SWEEPSHELFSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SWEEPSHELFSHARED_EXPORT Q_DECL_IMPORT
#endif
enum MOVESPEESD{SPEED_0_100,SPEED_100_300,SPEED_300_500,SPEED_500_1000,SPEED_1000_1500,SPEED_1500_};

#endif // SWEEPSHELF_GLOBAL_H
