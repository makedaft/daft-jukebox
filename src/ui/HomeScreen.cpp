#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <cstdint>
#include <functional>

#include "lib/display.h"
#include "lib/logger.cpp"
#include "runners/audio.h"
#include "runners/music_loader.h"
#include "runners/screen_manager.h"
#include "ui/_screen.h"

#include "ui/HomeScreen.h"
#include "ui/SongListScreen.h"

namespace ui {
HomeScreen::HomeScreen() {
  this->control.up = std::bind(&HomeScreen::listFiles, this);
  this->control.down = std::bind(&HomeScreen::listFiles, this);
  this->control.left = std::bind(&HomeScreen::previousSong, this);
  this->control.right = std::bind(&HomeScreen::nextSong, this);
  this->control.action1 = std::bind(&HomeScreen::listFiles, this);
}

void HomeScreen::renderScreen() {
  int16_t w = display::tft.width();
  int16_t h = display::tft.height();

  auto songPath = music_loader::getSongPath();
  display::tft.setTextColor(0xFFFF);
  display::tft.setTextSize(1);
  display::tft.setTextWrap(true);
  display::tft.setCursor(6, FONT_HEIGHT + 10);
  display::tft.print(songPath);

  int sc = 24;
  int st = sc * 95 / 100;
  int x = w / 2;
  int y = h / 2 - 20;
  int xt = x - st / 3 - 2;
  int yt = y;
  display::tft.fillCircle(x, y, sc, 0xFFFF);
  display::tft.fillTriangle(xt + st, yt, xt, yt - st / 2, xt, yt + st / 2,
                            0x0000);
}

long HomeScreen::dependencies() { return this->firstRender; }

void HomeScreen::listFiles() {
  screen_manager::openScreen(new SongListScreen("/"));
}

void HomeScreen::nextSong() {
  music_loader::nextSong();
  audio::startPlaying();
}
void HomeScreen::previousSong() {
  music_loader::previousSong();
  audio::startPlaying();
}

ui::ControlScheme HomeScreen::controlScheme() { return this->control; }
} // namespace ui
