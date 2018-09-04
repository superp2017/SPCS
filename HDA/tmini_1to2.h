#ifndef TMINI_1TO2_H
#define TMINI_1TO2_H
#include "tdevice.h"
#include "hda_global.h"
#include <QCoreApplication>


using namespace CVTS;

class HDASHARED_EXPORT TMini_1TO2 : public TDevice
{
protected:
    TMini_1TO2();
public:
  static TMini_1TO2 *instance()
   {
       static TMini_1TO2 *mini= new TMini_1TO2();
       return mini;
   }

  static void destory()
  {
      delete instance();
  }
  void turn_on_off(bool on);
   CVTS::CVTS_STATUS status();
};

#endif // TMINI_1TO2_H
