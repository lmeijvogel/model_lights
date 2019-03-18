#ifndef PHYSICAL_BUTTON_H
#define PHYSICAL_BUTTON_H

const int PRESS_THRESHOLD = 6;

class PhysicalButton {
public:
  PhysicalButton(int buttonId);
  void clockTick();
  boolean isPressed();
 private:
  int buttonId;

  int pressIntegrator = 0;

  bool _pressed = false;
};

#endif
