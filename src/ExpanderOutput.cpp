#include "ExpanderOutput.h"

ExpanderOutput::ExpanderOutput(Expander *expander, int port) {
  this->expander = expander;

  this->port = port;
}

void ExpanderOutput::turnOn() {
  this->expander->set(port);
}

void ExpanderOutput::turnOff() {
  this->expander->clear(port);
}
