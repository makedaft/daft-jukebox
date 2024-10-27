#pragma once
#include <Adafruit_SPITFT.h>
#include <climits>
#include <functional>

#include "lib/Renderable.h"
#include "lib/utils.h"

namespace ui {
struct ControlScheme {
  std::function<void()> up = &utils::noop;
  std::function<void()> down = &utils::noop;
  std::function<void()> left = &utils::noop;
  std::function<void()> right = &utils::noop;
  std::function<void()> action = &utils::noop;
  std::function<void()> lock = &utils::noop;
};

class Screen : public Renderable {
private:
  Adafruit_SPITFT *ctx;

public:
  virtual ControlScheme controlScheme() = 0;

  virtual void initialize() {}
};
} // namespace ui
