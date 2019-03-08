#ifndef LIGHTS_DRIVER_H
#define LIGHTS_DRIVER_H

#include "AbstractLightsDriver.hpp"
#include "Light.hpp"

typedef Light* LightPtr;

class LightsDriver : public AbstractLightsDriver {
public:
  LightsDriver(LightPtr lights[], int count);
  virtual LightsState getState();

  virtual void setOn();
  virtual void setOff();
  virtual void gradualOn(int transitionTimeSeconds);
  virtual void gradualOff(int transitionTimeSeconds);

private:
  LightPtr *lights;
  int count;

  LightsState state = LightsStateUnknown;
};

#endif
