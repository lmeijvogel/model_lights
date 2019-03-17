#ifndef EXPANDER_OUTPUT_H
#define EXPANDER_OUTPUT_H

#include "Light.h"
#include "Expander.h"

class ExpanderOutput : public Light {
public:
  ExpanderOutput(Expander *expander, int port);

  virtual void turnOn();
  virtual void turnOff();

private:
  Expander *expander;
  int port;
};

#endif
