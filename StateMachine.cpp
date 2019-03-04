#include "StateMachine.hpp"

StateMachine::StateMachine() {
  this->_state = StateOff;
}

State StateMachine::getState() {
  return this->_state;
}

void StateMachine::switchOn() {
  this->_state = StateOn;
}

void StateMachine::switchOff() {
  this->_state = StateOff;
}

void StateMachine::switchGradual() {
  switch(this->_state) {
  case StateOff:
    this->_state = StateTurningOn;
    break;
  case StateOn:
  case StateAnimating:
    this->_state = StateTurningOff;
    break;
  default:
    // Do nothing
    break;
  }
}

void StateMachine::_switchAnimatingForTest() {
  this->_state = StateAnimating;
}
