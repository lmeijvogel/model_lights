#include "Arduino.h"
#include "PhysicalButton.h"

PhysicalButton::PhysicalButton(int buttonId) {
  this->buttonId = buttonId;
  this->state = HIGH;
  this->lastState = HIGH;

  pinMode(buttonId, INPUT_PULLUP);
  ledState = LOW;
}

boolean PhysicalButton::isPressed() {
  boolean value = _isPressed;

  _isPressed = false;

  return value;
}

void PhysicalButton::clockTick(unsigned long currentTimeMs) {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonId);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastState) {
    // reset the debouncing timer
    lastDebounceTimeMs = currentTimeMs;
  }

  if ((currentTimeMs - lastDebounceTimeMs) > debounceDelayMs) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != state) {
      state = reading;

      // only toggle the LED if the new button state is LOW (pressed with INPUT_PULLUP)
      if (state == LOW) {
        _isPressed = true;
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastState = reading;
}
