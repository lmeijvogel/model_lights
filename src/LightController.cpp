#include "LightController.h"

LightController::LightController(Light *pLight, RandomGenerator *randomGenerator, int onTimeDuration, int offTimeDuration) {
  this->pLight = pLight;
  this->randomGenerator = randomGenerator;

  this->onTimeDuration = onTimeDuration;
  this->offTimeDuration = offTimeDuration;
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
      scheduleNextEvent(currentTimeMs, onTimeDuration);
    } else {
      scheduleNextEvent(currentTimeMs, offTimeDuration);
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
