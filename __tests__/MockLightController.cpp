#include "MockLightController.h"

void MockLightController::setOn() {
    this->receivedSetOn = true;
}

void MockLightController::setOff() {
    this->receivedSetOff = true;
}

void MockLightController::setAnimating() {
  this->receivedAnimating = true;
}

void MockLightController::gradualOn(unsigned long, unsigned long transitionTimeMs) {
  this->receivedGradualOn = transitionTimeMs;
}

void MockLightController::gradualOff(unsigned long, unsigned long transitionTimeMs) {
  this->receivedGradualOff = transitionTimeMs;
}

void MockLightController::cycle(int steps) {
  this->receivedCycle = steps;
}

void MockLightController::changeDelay(double factor) {
  this->receivedChangeDelay = factor;
}

void MockLightController::clockTick(unsigned long currentTimeMs) { }
