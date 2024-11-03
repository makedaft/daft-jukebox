#pragma once
#include <Arduino.h>

#define DOUBLE_PRESS_INTERVAL 300

class Button {
  int pin;
  int prevActive = 0;
  long lastPressTime = 0;

  bool active() { return digitalRead(this->pin) == 0; }

public:
  Button(int pin) { this->pin = pin; }

  void setup() { pinMode(this->pin, INPUT_PULLUP); }
  void loop() {}

  bool isPressed() {
    bool isActive = this->active();
    bool pressed = isActive && !this->prevActive;

    this->prevActive = isActive;

    return pressed;
  }

  short doublePressCount() {
    bool isActive = this->active();
    bool pressed = isActive && !this->prevActive;
    unsigned long currentTime = millis();
    this->prevActive = isActive;

    if (!pressed) {
      if (this->lastPressTime != 0 &&
          currentTime - this->lastPressTime > DOUBLE_PRESS_INTERVAL) {
        this->lastPressTime = 0;
        return 1;
      }

      return 0;
    }

    if (currentTime - this->lastPressTime > DOUBLE_PRESS_INTERVAL) {
      this->lastPressTime = currentTime;
      return 0;
    }

    this->lastPressTime = 0;

    return 2;
  }
};
