#include <stdio.h>
#include "LightController.h"

LightController::LightController(Light *pLight, RandomGenerator *randomGenerator, unsigned long onTimeDurationMs, unsigned long offTimeDurationMs) {
  this->pLight = pLight;
  this->randomGenerator = randomGenerator;

  this->onTimeDurationMs = onTimeDurationMs;
  this->offTimeDurationMs = offTimeDurationMs;
}

void LightController::setOn() {
  pLight->turnOn();

  this->nextEventTimeMs = 0;

  this->lightIsOn = true;
  this->isAnimating = false;
}

void LightController::setOff() {
  pLight->turnOff();

  this->nextEventTimeMs = 0;

  this->lightIsOn = false;
  this->isAnimating = false;
}

void LightController::setAnimating() {
  this->isAnimating = true;

  nextEventTimeMs = 0;
}

void LightController::gradualOn(unsigned long currentTimeMs, unsigned long transitionTimeMs) {
  this->isAnimating = false;
  nextEventTimeMs = 0;

  if (!lightIsOn) {
    scheduleNextEvent(currentTimeMs, transitionTimeMs / 2);
  }
}

void LightController::gradualOff(unsigned long currentTimeMs, unsigned long transitionTimeMs) {
  this->isAnimating = false;
  nextEventTimeMs = 0;

  if (lightIsOn) {
    scheduleNextEvent(currentTimeMs, transitionTimeMs / 2);
  }
}

void LightController::clockTick(unsigned long currentTimeMs) {
  if (this->isAnimating && nextEventTimeMs == 0) {
    if (lightIsOn) {
      scheduleNextEvent(currentTimeMs, onTimeDurationMs);
    } else {
      scheduleNextEvent(currentTimeMs, offTimeDurationMs);
    }
  }

  if ((nextEventTimeMs != 0) && (nextEventTimeMs < currentTimeMs)) {
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

void LightController::scheduleNextEvent(unsigned long currentTimeMs, unsigned long meanDurationMs) {
  // Get a factor with which to multiply the mean duration
  double factor = randomGenerator->getNextPoisson(10) * 10.0;

  double timeFromNowMs = factor * meanDurationMs;

  nextEventTimeMs = currentTimeMs + timeFromNowMs;
}
