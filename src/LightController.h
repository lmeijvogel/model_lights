#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include "AbstractLightController.h"
#include "Light.h"
#include "RandomGenerator.h"

class LightController : public AbstractLightController {
public:
  LightController(Light *pLight, RandomGenerator *randomGenerator, unsigned long onTimeDurationMs, unsigned long offTimeDurationMs);

  virtual void setOn();
  virtual void setOff();
  virtual void setAnimating();
  virtual void gradualOn(unsigned long currentTimeMs, unsigned long transitionTimeMs);
  virtual void gradualOff(unsigned long currentTimeMs, unsigned long transitionTimeMs);

  virtual void clockTick(unsigned long currentTimeMs);

private:
  Light *pLight;
  RandomGenerator *randomGenerator;

  bool lightIsOn = false;
  bool isAnimating = false;

  unsigned long onTimeDurationMs;
  unsigned long offTimeDurationMs;

  unsigned long nextEventTimeMs = 0;

  void handleAnimating(unsigned long currentTimeMs);

  void scheduleNextEvent(unsigned long currentTimeMs, unsigned long meanDurationMs);
};
#endif
