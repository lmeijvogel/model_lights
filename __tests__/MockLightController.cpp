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

void MockLightController::gradualOn(unsigned long transitionTimeSeconds) {
    this->receivedGradualOn = transitionTimeSeconds;
}

void MockLightController::gradualOff(unsigned long transitionTimeSeconds) {
    this->receivedGradualOff = transitionTimeSeconds;
}

void MockLightController::clockTick(unsigned long currentTimeMs) { }
