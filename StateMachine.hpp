#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

enum State {
             StateOff,
             StateTurningOn,
             StateAnimating,
             StateOn,
             StateTurningOff
};

class StateMachine {
public:
  StateMachine();

  State getState();

  void switchOff();
  void switchOn();
  void switchGradual();

  void _switchAnimatingForTest();

private:
  State _state;
};
#endif
