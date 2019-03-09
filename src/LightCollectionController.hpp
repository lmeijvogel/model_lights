#ifndef LIGHTS_DRIVER_H
#define LIGHTS_DRIVER_H

#include <functional>

#include "AbstractLightController.hpp"
#include "Light.hpp"

typedef Light* LightPtr;

class LightCollectionController : public AbstractLightController {
public:
  LightCollectionController(LightPtr lights[], int count);
  virtual LightsState getState();

  virtual void setOn();
  virtual void setOff();
  virtual void setAnimating();
  virtual void gradualOn(int transitionUntilMs);
  virtual void gradualOff(int transitionUntilMs);

private:
  LightPtr *lights;
  int count;

  LightsState state = LightsStateUnknown;

  void forEachLight(std::function<void (LightPtr)> func);
};
#endif
