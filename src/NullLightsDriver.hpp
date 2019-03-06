#include "LightsDriver.hpp"

class NullLightsDriver : public LightsDriver {
  virtual void setOn();
  virtual void setOff();
  virtual void gradualOn(int transitionTimeSeconds);
  virtual void gradualOff(int transitionTimeSeconds);
};
