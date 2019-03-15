#include "WheelStateMachine.h"

WheelStateMachine::WheelStateMachine(AbstractLightController* lightController) {
  this->lightController = lightController;
}

WheelState WheelStateMachine::getState() {
  return state;
}

void WheelStateMachine::wheelPressed() {
  switch (state) {
  case StateCycling:
    state = StateSpeed;
    break;
  case StateSpeed:
    state = StateCycling;
    break;
  }
}

void WheelStateMachine::wheelTurned(int steps) {
  lightController->cycle(steps);
}
