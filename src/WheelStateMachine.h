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

  int getSpeedRotation();
  double getDelayFactor();
private:
  AbstractLightController* lightController;
  WheelState state = StateCycling;

  int speedRotation = 0;

  double delayFactor = 1.0;

  double getNewDelayFactor();

  int clipRotation(int steps);
};

#endif
