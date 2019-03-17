#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "AbstractLightController.h"
#include "Delayable.h"

enum State {
             StateOff,
             StateTurningOn,
             StateAnimating,
             StateOn,
             StateTurningOff,
};

class StateMachine : public Delayable {
public:
  StateMachine(AbstractLightController *lightController);

  State getState();

  void switchOff();
  void switchOn();

  void switchGradual(unsigned long currentTimeMs, unsigned long transitionTimeMs);

  virtual void changeDelay(double factor);
  void clockTick(unsigned long currentTimeMs);

  void _switchAnimatingForTest();

private:
  State _state;
  AbstractLightController *lightController;
  unsigned long transitionStartMs = 0;
  unsigned long transitionTimeMs = 0;
  double delayFactor = 1.0;
};
#endif
