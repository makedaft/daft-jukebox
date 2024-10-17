#include <cstdint>

#include "Adafruit_SPITFT.h"

#include "ProgressBar.h"
#include "lib/logger.cpp"

namespace ui {
namespace component {
void ProgressBar::setPercentage(int percentage) {
  this->percentage = percentage;
}

ProgressBar::ProgressBar(Adafruit_SPITFT *ctx, int x, int y, int width,
                         int height) {
  this->ctx = ctx;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}

long ProgressBar::dependencies() { return percentage; }

void ProgressBar::render() {
  auto bar_w = (width - 2) * percentage / 100;

  // Clear empty side
  this->ctx->fillRect(width - bar_w - 1, y + 1, width - 2, height - 2, 0x0000);

  this->ctx->fillRect(x + 1, y + 1, bar_w, height - 2, 0x49d4);
  this->ctx->drawRect(x, y, width, height, 0x2947);
}
} // namespace component
} // namespace ui
