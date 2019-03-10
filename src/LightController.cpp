#include "LightController.h"

const int ON_TIME_DURATION = 1200;
const int OFF_TIME_DURATION = 60;
LightController::LightController(Light *pLight, RandomGenerator *randomGenerator) {
  this->pLight = pLight;
  this->randomGenerator = randomGenerator;
}

void LightController::setOn() {
  pLight->turnOn();

  this->lightIsOn = true;
  this->isAnimating = false;
}

void LightController::setOff() {
  pLight->turnOff();

  this->lightIsOn = true;
  this->isAnimating = false;
}

void LightController::setAnimating() {
  this->isAnimating = true;
}

void LightController::gradualOn(unsigned long transitionUntilMs) {
  this->isAnimating = false;
}

void LightController::gradualOff(unsigned long transitionUntilMs) {
  this->isAnimating = false;
}

void LightController::clockTick(unsigned long currentTimeMs) {
  if (this->isAnimating) {
    handleAnimating(currentTimeMs);
  }
}

void LightController::handleAnimating(unsigned long currentTimeMs) {
  if (nextEventTimeMs == 0) {
    if (lightIsOn) {
      scheduleNextEvent(currentTimeMs, ON_TIME_DURATION);
    } else {
      scheduleNextEvent(currentTimeMs, OFF_TIME_DURATION);
    }
  } else {
    if (nextEventTimeMs < currentTimeMs) {
      if (lightIsOn) {
        pLight->turnOff();

        lightIsOn = false;
      } else {
        pLight->turnOn();

        lightIsOn = true;
      }

      nextEventTimeMs = 0;
    }
  }
}

void LightController::scheduleNextEvent(unsigned long currentTimeMs, unsigned long multiplier) {
  unsigned long nextRandom = randomGenerator->getNextPoisson(10) * 200;

  double timeFromNowMs = nextRandom * multiplier;
  nextEventTimeMs = currentTimeMs + timeFromNowMs;
}
