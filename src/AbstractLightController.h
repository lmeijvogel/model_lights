#ifndef ABSTRACT_LIGHT_CONTROLLER_H
#define ABSTRACT_LIGHT_CONTROLLER_H

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
  virtual void gradualOn(unsigned long currentTimeMs, unsigned long transitionTimeMs) = 0;
  virtual void gradualOff(unsigned long currentTimeMs, unsigned long transitionTimeMs) = 0;

  virtual void cycle(int steps) = 0;
  virtual void changeDelay(double factor) = 0;

  virtual void clockTick(unsigned long currentTimeMs) = 0;
};

#endif
