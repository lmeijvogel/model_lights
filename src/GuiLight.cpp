#include "GuiLight.h"

void GuiLight::turnOn() {
  this->isOn = true;
}

void GuiLight::turnOff() {
  this->isOn = false;
}

bool GuiLight::getState() {
  return this->isOn;
}
