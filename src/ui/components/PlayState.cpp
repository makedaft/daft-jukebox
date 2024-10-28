#include "Adafruit_SPITFT.h"

#include "PlayState.h"
#include "lib/logger.h"

namespace ui {
namespace component {
void PlayState::setPlayState(bool playing) { this->playing = playing; }

PlayState::PlayState(Adafruit_SPITFT *ctx, int x, int y) {
  this->ctx = ctx;
  this->x = x;
  this->y = y;
}

long PlayState::dependencies() { return playing; }

void PlayState::render() {
  this->renderPlay();
  this->renderNext();
  this->renderPrev();
}

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

void PlayState::renderNext() {
  int sc = 9;
  int xc = this->x + 2 * sc + 20;
  int yc = this->y;
  int st = 6;
  int xt = xc;
  int yt = yc;
  this->ctx->fillCircle(xc, yc, sc, 0x0000);
  this->ctx->drawCircle(xc, yc, sc, 0xFFFF);
  this->ctx->drawLine(xt + st / 3, yt, xt - st / 3, yt - st / 2, 0xFFFF);
  this->ctx->drawLine(xt + st / 3, yt, xt - st / 3, yt + st / 2, 0xFFFF);
}

void PlayState::renderPrev() {
  int sc = 9;
  int xc = this->x - 2 * sc - 20;
  int yc = this->y;
  int st = 6;
  int xt = xc;
  int yt = yc;
  this->ctx->fillCircle(xc, yc, sc, 0x0000);
  this->ctx->drawCircle(xc, yc, sc, 0xFFFF);
  this->ctx->drawLine(xt - st / 3, yt, xt + st / 3, yt - st / 2, 0xFFFF);
  this->ctx->drawLine(xt - st / 3, yt, xt + st / 3, yt + st / 2, 0xFFFF);
}

} // namespace component
} // namespace ui
