#include "StateMachine.hpp"

StateMachine::StateMachine(AbstractLightsDriver *lightsDriver) {
  this->_state = StateOff;
  this->lightsDriver = lightsDriver;
}

State StateMachine::getState() {
  return this->_state;
}

void StateMachine::switchOn() {
  this->_state = StateOn;
  this->lightsDriver->setOn();
}

void StateMachine::switchOff() {
  this->_state = StateOff;
  this->lightsDriver->setOff();
}

void StateMachine::switchGradual(int transitionUntilMs) {
  this->transitionUntilMs = transitionUntilMs;
  switch(this->_state) {
  case StateTurningOff:
  case StateOff:
    this->_state = StateTurningOn;
    this->lightsDriver->gradualOn(transitionUntilMs);
    break;
  case StateTurningOn:
  case StateOn:
  case StateAnimating:
    this->_state = StateTurningOff;
    this->lightsDriver->gradualOff(transitionUntilMs);
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
      this->lightsDriver->setAnimating();
      break;
    case StateTurningOff:
      this->_state = StateOff;
      this->lightsDriver->setOff();
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
