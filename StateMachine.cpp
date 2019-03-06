#include "StateMachine.hpp"
#include "LightsDriver.hpp"

StateMachine::StateMachine(LightsDriver *lightsDriver, int gradualTimespan) {
  this->_state = StateOff;
  this->lightsDriver = lightsDriver;
  this->gradualTimespan = gradualTimespan;
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

void StateMachine::switchGradual() {
  switch(this->_state) {
  case StateTurningOff:
  case StateOff:
    this->_state = StateTurningOn;
    this->lightsDriver->gradualOn(this->gradualTimespan);
    break;
  case StateTurningOn:
  case StateOn:
  case StateAnimating:
    this->_state = StateTurningOff;
    this->lightsDriver->gradualOff(this->gradualTimespan);
    break;
  default:
    // Do nothing
    break;
  }
}

void StateMachine::_switchAnimatingForTest() {
  this->_state = StateAnimating;
}
