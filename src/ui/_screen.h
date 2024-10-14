#pragma once
#include <Adafruit_SPITFT.h>
#include <climits>
#include <functional>

#include "lib/utils.h"

namespace ui {
struct ControlScheme {
  std::function<void()> up = &utils::noop;
  std::function<void()> down = &utils::noop;
  std::function<void()> left = &utils::noop;
  std::function<void()> right = &utils::noop;
  std::function<void()> action1 = &utils::noop;
};

class Screen {
private:
  Adafruit_SPITFT *ctx;
  long previousDependency = LONG_MIN;

  virtual void renderScreen() = 0;
  virtual long dependencies() = 0;

protected:
  bool firstRender = true;

public:
  virtual ControlScheme controlScheme() = 0;

  void render();
};
} // namespace ui
