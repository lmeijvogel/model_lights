#ifndef LIGHTS_DRIVER_H
#define LIGHTS_DRIVER_H

enum LightsState {
                  LightsOn,
                  LightsOff
};

class LightsDriver {
public:
  virtual void setOn() = 0;
  virtual void setOff() = 0;
  virtual void gradualOn(int transitionTimeSeconds) = 0;
  virtual void gradualOff(int transitionTimeSeconds) = 0;
};

#endif
