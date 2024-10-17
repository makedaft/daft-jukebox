#include "Adafruit_SPITFT.h"

#include "PlayState.h"
#include "lib/logger.cpp"

namespace ui {
namespace component {
void PlayState::setPlayState(bool playing) { this->playing = playing; }

PlayState::PlayState(Adafruit_SPITFT *ctx, int x, int y) {
  this->ctx = ctx;
  this->x = x;
  this->y = y;
}

long PlayState::dependencies() { return playing; }

void PlayState::render() { this->renderPlay(); }

void PlayState::renderPlay() {
  int sc = 18;
  int xc = this->x;
  int yc = this->y;
  this->ctx->fillCircle(xc, yc, sc, 0xFFFF);

  if (this->playing) {
    int sr = sc * 97 / 100;
    int yr = yc + sc / 2 - sr;
    int w = 5;
    this->ctx->fillRect(xc - 3 - w, yr, w, sr, 0x00000);
    this->ctx->fillRect(xc + 3, yr, w, sr, 0x00000);
  } else {
    int st = sc * 95 / 100;
    int xt = xc - st / 3 - 2;
    int yt = yc;
    this->ctx->fillTriangle(xt + st, yt, xt, yt - st / 2, xt, yt + st / 2,
                            0x0000);
  }
}

// void PlayState::renderNext() {}
// void PlayState::renderPrev() {}

// display::tft.fillCircle(w / 4, yc, sc / 2, 0xDDDD);
// display::tft.drawLine(w / 4 + st / 2, yt, w / 4, yt - st / 4, 0x0000);
// display::tft.drawLine(w / 4 + st / 2, yt, w / 4, yt + st / 4, 0x0000);
// display::tft.fillCircle(w * 3 / 4, yc, sc / 2, 0xDDDD);
// display::tft.drawLine(w * 3 / 4 + st / 2, yt, w * 3 / 4, yt - st / 4,
// 0x0000);
// display::tft.drawLine(w * 3 / 4 + st / 2, yt, w * 3 / 4, yt + st /
// 4, 0x0000);
} // namespace component
} // namespace ui
