#ifndef LIGHTS_H
#define LIGHTS_H

class Light {
public:
  virtual void turnOn() = 0;
  virtual void turnOff() = 0;
};
#endif
