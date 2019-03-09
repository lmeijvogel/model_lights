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

  for (int i = 0 ; i < count ; i++) {
    LightPtr pLight = lights[i];

    pLight->turnOn();
  }
}

void LightsDriver::setOff() {
  state = LightsOff;

  for (int i = 0 ; i < count ; i++) {
    LightPtr pLight = lights[i];

    pLight->turnOff();
  }
}

void LightsDriver::setAnimating() {
}

void LightsDriver::gradualOn(int transitionTimeSeconds) { }
void LightsDriver::gradualOff(int transitionTimeSeconds) { }
