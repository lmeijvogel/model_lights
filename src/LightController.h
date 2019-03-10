#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include "AbstractLightController.h"
#include "Light.h"
#include "RandomGenerator.h"

class LightController : public AbstractLightController {
public:
  LightController(Light *pLight, RandomGenerator *randomGenerator, int onTimeDuration, int offTimeDuration);

  virtual void setOn();
  virtual void setOff();
  virtual void setAnimating();
  virtual void gradualOn(unsigned long transitionUntilMs);
  virtual void gradualOff(unsigned long transitionUntilMs);

  virtual void clockTick(unsigned long currentTimeMs);

private:
  Light *pLight;
  RandomGenerator *randomGenerator;

  bool lightIsOn = false;
  bool isAnimating = false;

  int onTimeDuration;
  int offTimeDuration;

  unsigned long nextEventTimeMs = 0;

  void handleAnimating(unsigned long currentTimeMs);

  void scheduleNextEvent(unsigned long currentTimeMs, unsigned long multiplier);
};
#endif
