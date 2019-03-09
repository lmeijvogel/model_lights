#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include "AbstractLightController.hpp"
#include "Light.hpp"

class LightController : public AbstractLightController {
public:
  LightController(Light *pLight);
  virtual void setOn();
  virtual void setOff();
  virtual void setAnimating();
  virtual void gradualOn(int transitionUntilMs);
  virtual void gradualOff(int transitionUntilMs);

private:
  Light *pLight;

  bool lightIsOn = false;
  bool isAnimating = false;
};
#endif
