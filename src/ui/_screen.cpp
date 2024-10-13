#include "ui/_screen.h"

namespace ui {
void Screen::render() {
  if (this->dependencies() == this->previousDependency)
    return;
  if (this->firstRender) {
    this->firstRender = false;
  }

  this->previousDependency = this->dependencies();

  renderScreen();
}
} // namespace ui
