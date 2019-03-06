#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "LightsDriver.hpp"

enum State {
             StateOff,
             StateTurningOn,
             StateAnimating,
             StateOn,
             StateTurningOff
};

class StateMachine {
public:
  StateMachine(LightsDriver *lightsDriver, int gradualTimespan);

  State getState();

  void switchOff();
  void switchOn();
  void switchGradual();

  void _switchAnimatingForTest();

private:
  State _state;
  LightsDriver *lightsDriver;
  int gradualTimespan;
};
#endif
