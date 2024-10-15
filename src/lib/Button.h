#pragma once

#define THROTTLE_INTERVAL 80

class Button {
private:
  int pin;
  int lastCheckTime = 0;
  int prevActive = 0;

  bool active();

public:
  Button(int pin);

  void setup();

  bool isPressed();
};
