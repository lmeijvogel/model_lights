#include "StateMachine.h"

StateMachine::StateMachine(AbstractLightController *lightController) {
  this->_state = StateOff;
  this->lightController = lightController;
  this->setState(StateOff);
}

State StateMachine::getState() {
  return this->_state;
}

void StateMachine::switchOn() {
  this->setState(StateOn);
  this->lightController->setOn();
}

void StateMachine::switchOff() {
  this->setState(StateOff);
  this->lightController->setOff();
}

void StateMachine::switchGradual(unsigned long currentTimeMs, unsigned long transitionTimeMs) {
  this->transitionStartMs = currentTimeMs;
  this->transitionTimeMs = transitionTimeMs;

  switch(this->_state) {
  case StateTurningOff:
  case StateOff:
    this->setState(StateTurningOn);
    this->lightController->gradualOn(currentTimeMs, transitionTimeMs);
    break;
  case StateTurningOn:
  case StateOn:
  case StateAnimating:
    this->setState(StateTurningOff);
    this->lightController->gradualOff(currentTimeMs, transitionTimeMs);
    break;
  default:
    // Do nothing
    break;
  }
}

void StateMachine::changeDelay(double factor) {
  this->delayFactor = factor;
}

void StateMachine::clockTick(unsigned long currentTimeMs) {
  if (_state != StateTurningOn && _state != StateTurningOff) {
    return;
  }

  unsigned long scaledTransitionTimeMs = transitionTimeMs * delayFactor;

  unsigned long transitionUntilMs = transitionStartMs + scaledTransitionTimeMs;

  if (transitionUntilMs < currentTimeMs) {
    switch(_state) {
    case StateTurningOn:
      this->setState(StateAnimating);
      this->lightController->setAnimating();
      break;
    case StateTurningOff:
      this->setState(StateOff);
      this->lightController->setOff();
      break;
    default:
      // do nothing
      break;
    }
  }
}

void StateMachine::_switchAnimatingForTest() {
  this->setState(StateAnimating);
}

void StateMachine::setState(State state) {
  this->_state = state;
  this->statusLedController->setState(state);
}
