#include "LightsDriver.hpp"
#include "Light.hpp"

LightsDriver::LightsDriver(LightPtr lights[], int count) {
  this->lights = lights;
  this->count = count;
}

LightsState LightsDriver::getState() {
  return state;
}

void LightsDriver::setOn() {
  state = LightsOn;

  forEachLight([] (LightPtr pLight) { pLight->turnOn(); });
}

void LightsDriver::setOff() {
  state = LightsOff;

  forEachLight([] (LightPtr pLight) { pLight->turnOff(); });
}

void LightsDriver::setAnimating() {
}

void LightsDriver::gradualOn(int transitionUntilMs) {
  state = LightsTurningOn;

  forEachLight([transitionUntilMs] (LightPtr pLight) { pLight->gradualOn(transitionUntilMs); });
}

void LightsDriver::gradualOff(int transitionUntilMs) {
  state = LightsTurningOff;

  forEachLight([transitionUntilMs] (LightPtr pLight) { pLight->gradualOff(transitionUntilMs); });
}

void LightsDriver::forEachLight(std::function<void (LightPtr)> callback) {
  for (int i = 0 ; i < count ; i++) {
    LightPtr pLight = lights[i];

    callback(pLight);
  }
}
