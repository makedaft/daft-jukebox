#pragma once

#include "Adafruit_SPITFT.h"
#include "lib/Renderable.h"

namespace ui {
namespace component {
class ProgressBar : public Renderable {
  Adafruit_SPITFT *ctx;
  int percentage = 0;
  int width, height;
  int x, y;

public:
  void setPercentage(int percentage);
  ProgressBar(Adafruit_SPITFT *ctx, int x, int y, int width, int height);
  long dependencies() override;

private:
  void render() override;
};
} // namespace component
} // namespace ui
