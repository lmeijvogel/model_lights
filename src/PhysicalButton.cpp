#include "Arduino.h"
#include "PhysicalButton.h"

PhysicalButton::PhysicalButton(int buttonId) {
  this->buttonId = buttonId;

  pinMode(buttonId, INPUT_PULLUP);
}

boolean PhysicalButton::isPressed() {
  return _pressed;
}

void PhysicalButton::clockTick() {
  /* Use a form of Kuhn's algorithm for debouncing buttons:
   * Basically: Keep a counter that increases if a LOW (pressed)
   * signal is received from the button, and decreases otherwise.
   *
   * Whenever a boundary value is hit (0 or PRESS_THRESHOLD), change the
   * state to false (not pressed) resp. true (pressed).
   */
  int reading = digitalRead(buttonId);

  if (reading == LOW) {
    pressIntegrator++;
  } else {
    pressIntegrator--;
  }

  if (pressIntegrator <= 0) {
    pressIntegrator = 0;

    _pressed = false;
  }

  if (pressIntegrator > PRESS_THRESHOLD) {
    _pressed = true;
    pressIntegrator = PRESS_THRESHOLD;
  }
}
