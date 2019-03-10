#ifndef GUI_LIGHT_H
#define GUI_LIGHT_H

#include "Light.h"

class GuiLight : public Light {
public:
  virtual void turnOn();
  virtual void turnOff();

  bool getState();
private:
  bool isOn = false;
};

#endif
