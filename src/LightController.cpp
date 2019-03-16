#include <stdio.h>
#include "LightController.h"

LightController::LightController(Light *pLight, RandomGenerator *randomGenerator, unsigned long onTimeDurationMs, unsigned long offTimeDurationMs) {
  this->pLight = pLight;
  this->randomGenerator = randomGenerator;

  this->onTimeDurationMs = onTimeDurationMs;
  this->offTimeDurationMs = offTimeDurationMs;

  this->nextEvent = new LightControllerEvent;
  this->nextEvent->state = LightControllerOff;
  this->nextEvent->referenceTimestampMs = 0;
  this->nextEvent->periodAfterReferenceMs = 0;
}

LightController::~LightController() {
  delete this->nextEvent;
}

void LightController::setOn() {
  _turnOnLight();

  this->state = LightControllerOn;

  this->clearNextEvent();
}

void LightController::setOff() {
  _turnOffLight();

  this->state = LightControllerOff;

  this->clearNextEvent();
}

void LightController::setAnimating() {
  this->state = LightControllerAnimating;

  clearNextEvent();
}

void LightController::gradualOn(unsigned long currentTimeMs, unsigned long transitionTimeMs) {
  clearNextEvent();

  if (!lightIsOn) {
    this->state = LightControllerTurningOn;

    scheduleNextEvent(LightControllerOn, currentTimeMs, transitionTimeMs / 3);
  } else {
    this->state = LightControllerOn;
  }
}

void LightController::gradualOff(unsigned long currentTimeMs, unsigned long transitionTimeMs) {
  clearNextEvent();

  if (lightIsOn) {
    this->state = LightControllerTurningOff;

    scheduleNextEvent(LightControllerOff, currentTimeMs, transitionTimeMs / 3);
  } else {
    this->state = LightControllerOff;
  }
}

void LightController::cycle(int) {
  // Do nothing
}

void LightController::clockTick(unsigned long currentTimeMs) {
  bool nextEventScheduled = isNextEventScheduled();

  if (this->state == LightControllerAnimating && !nextEventScheduled) {
    if (lightIsOn) {
      scheduleNextEvent(LightControllerOff, currentTimeMs, onTimeDurationMs);
    } else {
      scheduleNextEvent(LightControllerOn, currentTimeMs, offTimeDurationMs);
    }
  }

  if (nextEventScheduled) {
    unsigned long nextEventTimeMs = nextEvent->referenceTimestampMs + nextEvent->periodAfterReferenceMs;

    if (nextEventTimeMs < currentTimeMs) {
      if (nextEvent->state == LightControllerOn) {
        _turnOffLight();
      } else if (nextEvent->state == LightControllerOff) {
        _turnOnLight();
      }

      clearNextEvent();
    }
  }
}

void LightController::scheduleNextEvent(LightControllerState state, unsigned long currentTimeMs, unsigned long meanDurationMs) {
  // Get a factor with which to multiply the mean duration
  double factor = randomGenerator->getNextPoisson(10) * 10.0;

  unsigned long timeFromNowMs = factor * meanDurationMs;

  nextEvent->state = state;
  nextEvent->referenceTimestampMs = currentTimeMs;
  nextEvent->periodAfterReferenceMs = timeFromNowMs;
}

bool LightController::isNextEventScheduled() {
  return nextEvent->referenceTimestampMs > 0;
}

void LightController::clearNextEvent() {
  nextEvent->referenceTimestampMs = 0;
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

LightControllerEvent LightController::_nextEventForTests() {
  return *(this->nextEvent);
}
