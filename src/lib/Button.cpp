#pragma once
#include "esp32-hal-gpio.h"

#define THROTTLE_INTERVAL 100

class Button {
private:
  int pin;
  int lastCheckTime = 0;
  int lastValue = 0;

  bool active() { return digitalRead(this->pin) == 0; }

public:
  Button(int pin) { this->pin = pin; }

  void setup() { pinMode(this->pin, INPUT_PULLUP); }

  inline bool isPressed() {
    if (millis() - this->lastCheckTime <= THROTTLE_INTERVAL) {
      return false;
    }

    this->lastCheckTime = millis();

    bool active = digitalRead(this->pin) == 0;
    bool pressed = active && this->lastValue != active;

    this->lastValue = active;

    return pressed;
  }
};
