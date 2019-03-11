#include <stdio.h>
#include "LightController.h"

LightController::LightController(Light *pLight, RandomGenerator *randomGenerator, unsigned long onTimeDurationMs, unsigned long offTimeDurationMs) {
  this->pLight = pLight;
  this->randomGenerator = randomGenerator;

  this->onTimeDurationMs = onTimeDurationMs;
  this->offTimeDurationMs = offTimeDurationMs;
}

void LightController::setOn() {
  _turnOnLight();

  this->state = LightControllerOn;

  this->nextEventTimeMs = 0;
}

void LightController::setOff() {
  _turnOffLight();

  this->state = LightControllerOff;

  this->nextEventTimeMs = 0;
}

void LightController::setAnimating() {
  this->state = LightControllerAnimating;

  nextEventTimeMs = 0;
}

void LightController::gradualOn(unsigned long currentTimeMs, unsigned long transitionTimeMs) {
  nextEventTimeMs = 0;

  if (!lightIsOn) {
    this->state = LightControllerTurningOn;

    scheduleNextEvent(currentTimeMs, transitionTimeMs / 2);
  } else {
    this->state = LightControllerOn;
  }
}

void LightController::gradualOff(unsigned long currentTimeMs, unsigned long transitionTimeMs) {
  nextEventTimeMs = 0;

  if (lightIsOn) {
    this->state = LightControllerTurningOff;

    scheduleNextEvent(currentTimeMs, transitionTimeMs / 2);
  } else {
    this->state = LightControllerOff;
  }
}

void LightController::clockTick(unsigned long currentTimeMs) {
  if (this->state == LightControllerAnimating && nextEventTimeMs == 0) {
    if (lightIsOn) {
      scheduleNextEvent(currentTimeMs, onTimeDurationMs);
    } else {
      scheduleNextEvent(currentTimeMs, offTimeDurationMs);
    }
  }

  if ((nextEventTimeMs != 0) && (nextEventTimeMs < currentTimeMs)) {
    if (lightIsOn) {
      _turnOffLight();
    } else {
      _turnOnLight();
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

void LightController::_turnOnLight() {
  pLight->turnOn();

  lightIsOn = true;

  if (this->state == LightControllerTurningOn) {
    this->state = LightControllerAnimating;
  }
}

void LightController::_turnOffLight() {
  pLight->turnOff();

  lightIsOn = false;

  if (this->state == LightControllerTurningOff) {
    this->state = LightControllerOff;
  }
}
