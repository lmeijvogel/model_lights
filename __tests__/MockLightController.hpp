#ifndef MOCK_LIGHT_CONTROLLER_H
#define MOCK_LIGHT_CONTROLLER_H

#include "../src/AbstractLightController.hpp"

class MockLightController : public AbstractLightController {
public:
  virtual void setOn();
  virtual void setOff();
  virtual void setAnimating();
  virtual void gradualOn(int transitionTimeSeconds);
  virtual void gradualOff(int transitionTimeSeconds);

  bool receivedSetOn = false;
  bool receivedSetOff = false;
  bool receivedAnimating = false;
  int receivedGradualOn = 0;
  int receivedGradualOff = 0;
};
#endif
