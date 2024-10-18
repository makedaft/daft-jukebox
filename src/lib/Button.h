#pragma once

#define DOUBLE_PRESS_INTERVAL 300

class Button {
private:
  int pin;
  int prevActive = 0;
  long lastPressTime = 0;

  bool active();

public:
  Button(int pin);

  void setup();
  void loop();

  bool isPressed();
  short doublePressCount();
};
