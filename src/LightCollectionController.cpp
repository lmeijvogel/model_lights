#include "LightCollectionController.hpp"
#include "LightController.hpp"
#include "Light.hpp"

typedef LightController* LightControllerPtr;

#define forEachLightController(X) {for (int i = 0 ; i < count ; i++) { LightControllerPtr pLightController = lightControllers[i]; (X); }}

LightCollectionController::LightCollectionController(LightControllerPtr lightControllers[], int count) {
  this->lightControllers = lightControllers;
  this->count = count;
}

LightsState LightCollectionController::getState() {
  return state;
}

void LightCollectionController::setOn() {
  state = LightsOn;

  forEachLightController( pLightController->setOn());
}

void LightCollectionController::setOff() {
  state = LightsOff;

  forEachLightController( pLightController->setOff());
}

void LightCollectionController::setAnimating() {
  forEachLightController( pLightController->setAnimating());
}

void LightCollectionController::gradualOn(int transitionUntilMs) {
  state = LightsTurningOn;

  forEachLightController(pLightController->gradualOn(transitionUntilMs));
}

void LightCollectionController::gradualOff(int transitionUntilMs) {
  state = LightsTurningOff;

  forEachLightController(pLightController->gradualOff(transitionUntilMs));
}

void LightCollectionController::clockTick(int currentTimeMs) {
  forEachLightController(pLightController->clockTick(currentTimeMs));
}
