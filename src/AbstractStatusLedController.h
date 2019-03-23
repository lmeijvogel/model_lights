#ifndef ABSTRACT_STATUS_LED_CONTROLLER_H
#define ABSTRACT_STATUS_LED_CONTROLLER_H

#include "State.h"

class AbstractStatusLedController {
public:
  virtual void setState(State state) = 0;
};

#endif
