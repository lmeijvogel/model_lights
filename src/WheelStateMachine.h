#ifndef WHEEL_STATE_MACHINE_H
#define WHEEL_STATE_MACHINE_H

#include "AbstractLightController.h"

enum WheelState {
                 StateSpeed,
                 StateCycling
};

class WheelStateMachine {
public:
  WheelStateMachine(AbstractLightController* lightController);
  WheelState getState();

  void wheelPressed();
  void wheelTurned(int steps);

private:
  AbstractLightController* lightController;
  WheelState state = StateCycling;
};

#endif
