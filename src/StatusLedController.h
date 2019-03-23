#ifndef STATUS_LED_CONTROLLER_H
#define STATUS_LED_CONTROLLER_H

#include "Light.h"
#include "State.h"
#include "AbstractStatusLedController.h"

class StatusLedController : public AbstractStatusLedController {
public:
  StatusLedController(Light* offLight, Light* gradualLight, Light* onLight);
  virtual void setState(State state);
private:
  Light* offLight;
  Light* gradualLight;
  Light* onLight;
};

#endif
