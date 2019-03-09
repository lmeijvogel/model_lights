#include "LightCollectionController.hpp"
#include "Light.hpp"

LightCollectionController::LightCollectionController(LightControllerPtr lightControllers[], int count) {
  this->lightControllers = lightControllers;
  this->count = count;
}

LightsState LightCollectionController::getState() {
  return state;
}

void LightCollectionController::setOn() {
  state = LightsOn;

  forEachLight([] (LightControllerPtr pLightController) { pLightController->setOn(); });
}

void LightCollectionController::setOff() {
  state = LightsOff;

  forEachLight([] (LightControllerPtr pLightController) { pLightController->setOff(); });
}

void LightCollectionController::setAnimating() {
  forEachLight([] (LightControllerPtr pLightController) { pLightController->setAnimating(); });
}

void LightCollectionController::gradualOn(int transitionUntilMs) {
  state = LightsTurningOn;

  forEachLight([transitionUntilMs] (LightControllerPtr pLightController) { pLightController->gradualOn(transitionUntilMs); });
}

void LightCollectionController::gradualOff(int transitionUntilMs) {
  state = LightsTurningOff;

  forEachLight([transitionUntilMs] (LightControllerPtr pLightController) { pLightController->gradualOff(transitionUntilMs); });
}

void LightCollectionController::clockTick(int currentTimeMs) {
  forEachLight([currentTimeMs] (LightControllerPtr pLightController) { pLightController->clockTick(currentTimeMs); });
}

void LightCollectionController::forEachLight(std::function<void (LightControllerPtr)> callback) {
  for (int i = 0 ; i < count ; i++) {
    LightControllerPtr pLightController = lightControllers[i];

    callback(pLightController);
  }
}
