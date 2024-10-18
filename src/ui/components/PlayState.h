#pragma once

#include "Adafruit_SPITFT.h"
#include "lib/Renderable.h"

namespace ui {
namespace component {
class PlayState : public Renderable {
  Adafruit_SPITFT *ctx;
  bool playing = false;
  int x, y;

public:
  void setPlayState(bool playing);
  PlayState(Adafruit_SPITFT *ctx, int x, int y);
  long dependencies() override;

private:
  void render() override;
  void renderPlay();
  // void renderNext();
  // void renderPrev();
};
} // namespace component
} // namespace ui
