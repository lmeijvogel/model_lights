#include "LightController.hpp"

LightController::LightController(Light *pLight) {
  this->pLight = pLight;
}
void LightController::setOn() {
  pLight->turnOn();
}
void LightController::setOff() {
  pLight->turnOff();
}
void LightController::setAnimating() {}
void LightController::gradualOn(int transitionUntilMs) {}
void LightController::gradualOff(int transitionUntilMs) {}
