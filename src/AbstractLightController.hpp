#ifndef ABSTRACT_LIGHTS_DRIVER_H
#define ABSTRACT_LIGHTS_DRIVER_H

enum LightsState {
                  LightsStateUnknown,
                  LightsTurningOn,
                  LightsTurningOff,
                  LightsOn,
                  LightsOff
};

class AbstractLightController {
public:
  virtual void setOn() = 0;
  virtual void setOff() = 0;
  virtual void setAnimating() = 0;
  virtual void gradualOn(int transitionUntilMs) = 0;
  virtual void gradualOff(int transitionUntilMs) = 0;

  virtual void clockTick(int currentTimeMs) = 0;
};

#endif
