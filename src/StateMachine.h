#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "AbstractLightController.h"

enum State {
             StateOff,
             StateTurningOn,
             StateAnimating,
             StateOn,
             StateTurningOff
};

class StateMachine {
public:
  StateMachine(AbstractLightController *lightController);

  State getState();

  void switchOff();
  void switchOn();
  void switchGradual(int transitionUntilMs);

  void clockTick(int currentTimeMs);

  void _switchAnimatingForTest();

private:
  State _state;
  AbstractLightController *lightController;
  int transitionUntilMs;
};
#endif
