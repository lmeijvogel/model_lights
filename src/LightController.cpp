#include "LightController.hpp"

LightController::LightController(Light *pLight) {
  this->pLight = pLight;
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
