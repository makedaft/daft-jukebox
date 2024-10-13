#pragma once

#include "ui/_screen.h"

namespace ui {
void Screen::render() {
  if (!shouldRender())
    return;

  renderScreen();
}
} // namespace ui
