#include "AbstractLightsDriver.hpp"

class NullLightsDriver : public AbstractLightsDriver {
  virtual void setOn();
  virtual void setOff();
  virtual void gradualOn(int transitionTimeSeconds);
  virtual void gradualOff(int transitionTimeSeconds);
};
