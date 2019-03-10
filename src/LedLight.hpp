#ifndef LED_LIGHT_H
#define LED_LIGHT_H

#include "Light.hpp"

class LedLight : public Light {
public:
  LedLight(int pin);

  virtual void turnOn();
  virtual void turnOff();

private:
  int pin;
};
#endif
