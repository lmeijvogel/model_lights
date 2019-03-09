#include "LightController.hpp"

const int ON_TIME_DURATION = 1200;
const int OFF_TIME_DURATION = 60;
LightController::LightController(Light *pLight, std::default_random_engine *generator) {
  this->pLight = pLight;
  this->generator = generator;
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

void LightController::gradualOn(int transitionUntilMs) {
  this->isAnimating = false;
}

void LightController::gradualOff(int transitionUntilMs) {
  this->isAnimating = false;
}

void LightController::clockTick(int currentTimeMs) {
  if (this->isAnimating) {
    handleAnimating(currentTimeMs);
  }
}

void LightController::handleAnimating(int currentTimeMs) {
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

void LightController::scheduleNextEvent(int currentTimeMs, int multiplier) {
  std::poisson_distribution<int> distribution(10);

  double timeFromNowMs = distribution(*generator) * multiplier;
  nextEventTimeMs = currentTimeMs + timeFromNowMs;
}
