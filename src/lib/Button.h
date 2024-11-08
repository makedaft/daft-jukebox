#pragma once
#include <Arduino.h>
#include <functional>

#include "lib/logger.h"
#include "lib/utils.h"

#define DEBOUNCE_DELAY 50

void call(std::function<void()> fn) { fn(); }

class Button {
  int pin;
  int prevPressed = 0;
  long lastActiveTime = 0;

  long lastDebouncedCheckTime = 0;

  utils::Optional<std::function<void()>> pressCallback;
  utils::Optional<std::function<void()>> doublePressCallback;

  inline bool isPressed() { return digitalRead(pin) == LOW; }

  inline bool checkIsActive() {
    unsigned long currentTime = millis();
    if (currentTime - lastDebouncedCheckTime <= DEBOUNCE_DELAY)
      return false;
    lastDebouncedCheckTime = currentTime;

    bool pressed = isPressed();
    bool active = !pressed && this->prevPressed;
    this->prevPressed = pressed;
    return active;
  }

public:
  unsigned int debounce = 100;
  Button(int pin) { this->pin = pin; }

  void setup() { pinMode(pin, INPUT_PULLUP); }

  void onPress(std::function<void()> callback) {
    pressCallback.update(callback);
  }

  void onDoublePress(std::function<void()> callback) {
    doublePressCallback.update(callback);
  }

  void loop() {
    bool pressed = isPressed();
    bool active = checkIsActive();
    unsigned long currentTime = millis();

    bool isWaitingForSecondPress = currentTime - lastActiveTime <= debounce;

    if (active) {
      if (lastActiveTime != 0 && isWaitingForSecondPress) {
        lastActiveTime = 0;
        doublePressCallback.withValue(&call);
      } else {
        lastActiveTime = currentTime;
      }
      return;
    }

    if (lastActiveTime != 0 && !isWaitingForSecondPress) {
      lastActiveTime = 0;
      pressCallback.withValue(&call);
    }
  }
};
