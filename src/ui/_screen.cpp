#pragma once
#include "Adafruit_SPITFT.h"
#include <functional>

namespace ui {
struct ControlScheme {
  std::function<void()> up;
  std::function<void()> down;
  std::function<void()> left;
  std::function<void()> right;
};

class Screen {
private:
  virtual void renderScreen() = 0;
  virtual boolean shouldRender() = 0;

protected:
  Adafruit_SPITFT *drawCtx;

  Screen(Adafruit_SPITFT &drawCtx) { this->drawCtx = &drawCtx; }

public:
  virtual ControlScheme controlScheme() = 0;

  void render() {
    if (!shouldRender())
      return;

    renderScreen();
  }
};
} // namespace ui
