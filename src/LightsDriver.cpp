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

void LightsDriver::gradualOn(int transitionTimeSeconds) { }
void LightsDriver::gradualOff(int transitionTimeSeconds) { }

void LightsDriver::forEachLight(std::function<void (LightPtr)> callback) {
  for (int i = 0 ; i < count ; i++) {
    LightPtr pLight = lights[i];

    callback(pLight);
  }
}
