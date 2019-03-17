#include "WheelStateMachine.h"

#include <algorithm>
#include <cmath>

WheelStateMachine::WheelStateMachine(AbstractLightController* lightController, Delayable* stateMachine) {
  this->lightController = lightController;
  this->stateMachine = stateMachine;
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
  switch (state) {
  case StateCycling:
    lightController->cycle(steps);
    break;
  case StateSpeed:
    speedRotation = clipRotation(steps);

    double newDelayFactor = getNewDelayFactor();

    lightController->changeDelay(newDelayFactor);
    stateMachine->changeDelay(newDelayFactor);

    delayFactor = newDelayFactor;
    break;
  }
}

int WheelStateMachine::clipRotation(int steps) {
  return std::max(-30, std::min(speedRotation + steps, 30));
}

double WheelStateMachine::getNewDelayFactor() {
  // Rotation configures more speed, but the value is used as
  // a factor with which events are delayed, hence the negation of
  // speedRotation.
  return std::pow(1.1, -speedRotation);
}

int WheelStateMachine::getSpeedRotation() {
  return speedRotation;
}

double WheelStateMachine::getDelayFactor() {
  return delayFactor;
}
