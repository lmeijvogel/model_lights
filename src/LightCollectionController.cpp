#include "LightCollectionController.h"
#include "LightController.h"
#include "Light.h"

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

void LightCollectionController::gradualOn(unsigned long currentTimeMs, unsigned long transitionTimeMs) {
  state = LightsTurningOn;

  forEachLightController(pLightController->gradualOn(currentTimeMs, transitionTimeMs));
}

void LightCollectionController::gradualOff(unsigned long currentTimeMs, unsigned long transitionTimeMs) {
  state = LightsTurningOff;

  forEachLightController(pLightController->gradualOff(currentTimeMs, transitionTimeMs));
}

void LightCollectionController::clockTick(unsigned long currentTimeMs) {
  forEachLightController(pLightController->clockTick(currentTimeMs));
}
