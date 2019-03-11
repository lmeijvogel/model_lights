#ifndef NULL_LIGHT_CONTROLLER_H
#define NULL_LIGHT_CONTROLLER_H

#include "AbstractLightController.h"

class NullLightController : public AbstractLightController {
  virtual void setOn();
  virtual void setOff();
  virtual void gradualOn(int transitionTimeSeconds);
  virtual void gradualOff(int transitionTimeSeconds);
};

#endif
