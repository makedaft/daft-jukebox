#include <Arduino.h>

#include "Button.h"
#include "lib/logger.h"

bool Button::active() { return digitalRead(this->pin) == 0; }

Button::Button(int pin) { this->pin = pin; }

void Button::setup() { pinMode(this->pin, INPUT_PULLUP); }

bool Button::isPressed() {
  bool active = this->active();
  bool pressed = active && !this->prevActive;

  this->prevActive = active;

  return pressed;
}

void Button::loop() {}

short Button::doublePressCount() {
  bool active = this->active();
  bool pressed = active && !this->prevActive;
  this->prevActive = active;

  if (!pressed) {
    if (this->lastPressTime != 0 &&
        millis() - this->lastPressTime > DOUBLE_PRESS_INTERVAL) {
      this->lastPressTime = 0;
      return 1;
    }

    return 0;
  }

  if (millis() - this->lastPressTime > DOUBLE_PRESS_INTERVAL) {
    this->lastPressTime = millis();
    return 0;
  }

  this->lastPressTime = 0;

  return 2;
}
