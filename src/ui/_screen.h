#pragma once
#include <Adafruit_SPITFT.h>
#include <functional>

#include "lib/utils.cpp"

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

  virtual void renderScreen() = 0;
  virtual bool shouldRender() = 0;

public:
  virtual ControlScheme controlScheme() = 0;

  void render();
};
} // namespace ui
