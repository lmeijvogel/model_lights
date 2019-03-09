#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "AbstractLightsDriver.hpp"

enum State {
             StateOff,
             StateTurningOn,
             StateAnimating,
             StateOn,
             StateTurningOff
};

class StateMachine {
public:
  StateMachine(AbstractLightsDriver *lightsDriver);

  State getState();

  void switchOff();
  void switchOn();
  void switchGradual(int transitionUntilMs);

  void clockTick(int currentTimeMs);

  void _switchAnimatingForTest();

private:
  State _state;
  AbstractLightsDriver *lightsDriver;
  int transitionUntilMs;
};
#endif
