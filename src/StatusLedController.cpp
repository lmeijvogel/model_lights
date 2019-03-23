#include "StatusLedController.h"

StatusLedController::StatusLedController(Light* offLight, Light* gradualLight, Light* onLight) {
  this->offLight = offLight;
  this->gradualLight = gradualLight;
  this->onLight = onLight;
  this->setState(StateOff);
}

void StatusLedController::setState(State state) {
  switch (state) {
  case StateOff:
    this->offLight->turnOn();
    this->gradualLight->turnOff();
    this->onLight->turnOff();
    break;
  case StateTurningOn:
    this->offLight->turnOff();
    this->gradualLight->turnOn();
    this->onLight->turnOn();
    break;
  case StateAnimating:
    this->offLight->turnOff();
    this->gradualLight->turnOn();
    this->onLight->turnOff();
    break;
  case StateOn:
    this->offLight->turnOff();
    this->gradualLight->turnOff();
    this->onLight->turnOn();
    break;
  case StateTurningOff:
    this->offLight->turnOn();
    this->gradualLight->turnOn();
    this->onLight->turnOff();
    break;

  }

}
