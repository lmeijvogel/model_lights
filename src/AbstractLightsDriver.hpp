#ifndef ABSTRACT_LIGHTS_DRIVER_H
#define ABSTRACT_LIGHTS_DRIVER_H

enum LightsState {
                  LightsStateUnknown,
                  LightsOn,
                  LightsOff
};

class AbstractLightsDriver {
public:
  virtual void setOn() = 0;
  virtual void setOff() = 0;
  virtual void setAnimating() = 0;
  virtual void gradualOn(int transitionUntilMs) = 0;
  virtual void gradualOff(int transitionUntilMs) = 0;
};

#endif
