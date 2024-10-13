#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <cstdint>
#include <functional>
#include <vector>

#include "lib/display.h"
#include "lib/logger.cpp"
#include "lib/utils.cpp"
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
  this->_rendered = true;

  int16_t w = display::tft.width();
  int16_t h = display::tft.height();
  display::tft.fillScreen(0x0000);

  display::tft.fillCircle(w / 2, h / 2, 50, 0xFFFF);
  int x = w / 2;
  int y = h / 2;
  display::tft.fillTriangle(x + 20, y, x - 20, y - 20, x - 20, y + 20, 0x0000);

  display::tft.setTextColor(0xFFFF);
  display::tft.setTextSize(2);
  display::tft.setTextWrap(true);
  display::tft.setCursor(10, 20);
  display::tft.print("Owyn home");
}

bool HomeScreen::shouldRender() { return !this->_rendered; }

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
