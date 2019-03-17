#ifndef MOCK_LIGHT_CONTROLLER_H
#define MOCK_LIGHT_CONTROLLER_H

#include "../src/AbstractLightController.h"

class MockLightController : public AbstractLightController {
public:
  virtual void setOn();
  virtual void setOff();
  virtual void setAnimating();
  virtual void gradualOn(unsigned long currentTimeMs, unsigned long transitionTimeMs);
  virtual void gradualOff(unsigned long currentTimeMs, unsigned long transitionTimeMs);
  virtual void cycle(int steps);
  virtual void changeDelay(double factor);

  virtual void clockTick(unsigned long currentTimeMs);

  bool receivedSetOn = false;
  bool receivedSetOff = false;
  bool receivedAnimating = false;
  int receivedGradualOn = 0;
  int receivedGradualOff = 0;
  int receivedCycle = 0;
  double receivedChangeDelay = 0;
};
#endif
