#include <Arduino.h>

#include "Button.h"

bool Button::active() { return digitalRead(this->pin) == 0; }

Button::Button(int pin) { this->pin = pin; }

void Button::setup() { pinMode(this->pin, INPUT_PULLUP); }

bool Button::isPressed() {
  if (millis() - this->lastCheckTime <= THROTTLE_INTERVAL) {
    return false;
  }

  this->lastCheckTime = millis();

  bool active = this->active();
  bool pressed = active && !this->prevActive;

  this->prevActive = active;

  return pressed;
}
