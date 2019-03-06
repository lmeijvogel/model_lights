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
  StateMachine(AbstractLightsDriver *lightsDriver, int gradualTimespan);

  State getState();

  void switchOff();
  void switchOn();
  void switchGradual();

  void _switchAnimatingForTest();

private:
  State _state;
  AbstractLightsDriver *lightsDriver;
  int gradualTimespan;
};
#endif
