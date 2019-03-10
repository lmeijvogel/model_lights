#include "Arduino.h"
#include "LedLight.h"

LedLight::LedLight(int pin) {
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void LedLight::turnOn()
{
  digitalWrite(pin, HIGH);
}

void LedLight::turnOff() {
  digitalWrite(pin, LOW);
}
