#ifndef PHYSICAL_BUTTON_H
#define PHYSICAL_BUTTON_H

class PhysicalButton {
public:
  PhysicalButton(int buttonId);
  void clockTick(unsigned long currentTimeMs);
  boolean isPressed();
 private:
  int buttonId;

  int ledState;
  int state;
  int lastState;
  bool _isPressed = false;
  unsigned long lastDebounceTimeMs = 0;
  unsigned long debounceDelayMs = 50;

};

#endif
