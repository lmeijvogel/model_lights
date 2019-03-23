#ifndef MOCK_STATUS_LED_CONTROLLER_H
#define MOCK_STATUS_LED_CONTROLLER_H

#include "../src/AbstractStatusLedController.h"

class MockStatusLedController : public AbstractStatusLedController {
public:
  MockStatusLedController();
  virtual void setState(State state);

  State state;
};
#endif
