#include "MockStatusLedController.h"

MockStatusLedController::MockStatusLedController() {}

void MockStatusLedController::setState(State state) {
  this->state = state;
}
