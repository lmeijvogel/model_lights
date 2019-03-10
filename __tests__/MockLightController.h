#ifndef MOCK_LIGHT_CONTROLLER_H
#define MOCK_LIGHT_CONTROLLER_H

#include "../src/AbstractLightController.h"

class MockLightController : public AbstractLightController {
public:
  virtual void setOn();
  virtual void setOff();
  virtual void setAnimating();
  virtual void gradualOn(unsigned long transitionTimeSeconds);
  virtual void gradualOff(unsigned long transitionTimeSeconds);
  virtual void clockTick(unsigned long currentTimeMs);

  bool receivedSetOn = false;
  bool receivedSetOff = false;
  bool receivedAnimating = false;
  int receivedGradualOn = 0;
  int receivedGradualOff = 0;
};
#endif