#include "StateMachine.h"

StateMachine::StateMachine(AbstractLightController *lightController) {
  this->_state = StateOff;
  this->lightController = lightController;
}

State StateMachine::getState() {
  return this->_state;
}

void StateMachine::switchOn() {
  this->_state = StateOn;
  this->lightController->setOn();
}

void StateMachine::switchOff() {
  this->_state = StateOff;
  this->lightController->setOff();
}

void StateMachine::switchGradual(int transitionUntilMs) {
  this->transitionUntilMs = transitionUntilMs;
  switch(this->_state) {
  case StateTurningOff:
  case StateOff:
    this->_state = StateTurningOn;
    this->lightController->gradualOn(transitionUntilMs);
    break;
  case StateTurningOn:
  case StateOn:
  case StateAnimating:
    this->_state = StateTurningOff;
    this->lightController->gradualOff(transitionUntilMs);
    break;
  default:
    // Do nothing
    break;
  }
}

void StateMachine::clockTick(int currentTimeMs) {
  if (_state != StateTurningOn && _state != StateTurningOff) {
    return;
  }

  if (transitionUntilMs < currentTimeMs) {
    switch(_state) {
    case StateTurningOn:
      this->_state = StateAnimating;
      this->lightController->setAnimating();
      break;
    case StateTurningOff:
      this->_state = StateOff;
      this->lightController->setOff();
      break;
    default:
      // do nothing
      break;
    }
  }
}

void StateMachine::_switchAnimatingForTest() {
  this->_state = StateAnimating;
}
