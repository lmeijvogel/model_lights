#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include <random>

#include "AbstractLightController.hpp"
#include "Light.hpp"

class LightController : public AbstractLightController {
public:
  LightController(Light *pLight, std::default_random_engine *generator);
  virtual void setOn();
  virtual void setOff();
  virtual void setAnimating();
  virtual void gradualOn(int transitionUntilMs);
  virtual void gradualOff(int transitionUntilMs);
  virtual void clockTick(int currentTimeMs);

private:
  Light *pLight;
  std::default_random_engine *generator;

  bool lightIsOn = false;
  bool isAnimating = false;
  int nextEventTimeMs = 0;

  void handleAnimating(int currentTimeMs);

  void scheduleNextEvent(int currentTimeMs, int multiplier);
};
#endif
