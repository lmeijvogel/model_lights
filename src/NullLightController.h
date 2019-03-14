#ifndef NULL_LIGHT_CONTROLLER_H
#define NULL_LIGHT_CONTROLLER_H

#include "AbstractLightController.h"

class NullLightController : public AbstractLightController {
public:
  virtual void setOn();
  virtual void setOff();
  virtual void setAnimating();
  virtual void gradualOn(unsigned long currentTimeMs, unsigned long transitionTimeMs);
  virtual void gradualOff(unsigned long currentTimeMs, unsigned long transitionTimeMs);
  virtual void cycle(int);

  virtual void clockTick(unsigned long currentTimeMs);
};

#endif
