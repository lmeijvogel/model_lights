#include "LightCollectionController.hpp"
#include "Light.hpp"

LightCollectionController::LightCollectionController(LightPtr lights[], int count) {
  this->lights = lights;
  this->count = count;
}

LightsState LightCollectionController::getState() {
  return state;
}

void LightCollectionController::setOn() {
  state = LightsOn;

  forEachLight([] (LightPtr pLight) { pLight->turnOn(); });
}

void LightCollectionController::setOff() {
  state = LightsOff;

  forEachLight([] (LightPtr pLight) { pLight->turnOff(); });
}

void LightCollectionController::setAnimating() {
}

void LightCollectionController::gradualOn(int transitionUntilMs) {
  state = LightsTurningOn;

  forEachLight([transitionUntilMs] (LightPtr pLight) { pLight->gradualOn(transitionUntilMs); });
}

void LightCollectionController::gradualOff(int transitionUntilMs) {
  state = LightsTurningOff;

  forEachLight([transitionUntilMs] (LightPtr pLight) { pLight->gradualOff(transitionUntilMs); });
}

void LightCollectionController::forEachLight(std::function<void (LightPtr)> callback) {
  for (int i = 0 ; i < count ; i++) {
    LightPtr pLight = lights[i];

    callback(pLight);
  }
}
