#ifndef LIGHTS_H
#define LIGHTS_H

class Light {
public:
  virtual void turnOn() = 0;
  virtual void turnOff() = 0;
  virtual void gradualOn(int transitionUntilMs) = 0;
  virtual void gradualOff(int transitionUntilMs) = 0;
};
#endif
