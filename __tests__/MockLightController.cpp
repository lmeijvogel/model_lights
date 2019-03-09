#include "MockLightController.hpp"

void MockLightController::setOn() {
    this->receivedSetOn = true;
}

void MockLightController::setOff() {
    this->receivedSetOff = true;
}

void MockLightController::setAnimating() {
  this->receivedAnimating = true;
}

void MockLightController::gradualOn(int transitionTimeSeconds) {
    this->receivedGradualOn = transitionTimeSeconds;
}

void MockLightController::gradualOff(int transitionTimeSeconds) {
    this->receivedGradualOff = transitionTimeSeconds;
}
