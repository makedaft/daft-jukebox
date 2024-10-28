#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <cstdint>
#include <functional>

#include "lib/display.h"
#include "lib/logger.h"
#include "lib/utils.h"
#include "runners/audio.h"
#include "runners/music_loader.h"
#include "runners/screen_manager.h"
#include "ui/QueueScreen.h"
#include "ui/_screen.h"

#include "ui/HomeScreen.h"
#include "ui/SongListScreen.h"
#include "ui/components/PlayState.h"

namespace ui {
HomeScreen::HomeScreen() {
  this->control.up = std::bind(&HomeScreen::listFiles, this);
  this->control.down = std::bind(&HomeScreen::openQueue, this);
  this->control.left = std::bind(&HomeScreen::previousSong, this);
  this->control.right = std::bind(&HomeScreen::nextSong, this);
  this->control.action = std::bind(&HomeScreen::playPause, this);
}

void HomeScreen::initialize() {
  auto w = display::tft.width();
  auto h = display::tft.height();
  this->playState = new ui::component::PlayState(&display::tft, w / 2, h - 40);
}

void HomeScreen::render() {
  auto songInfo = music_loader::currentSong();
  auto subtitle = songInfo.dirPath;
  auto title = songInfo.name;
  if (!songInfo.isAvailable) {
    title = "";
    subtitle = music_loader::currentQueue.empty() ? ":::: Queue is empty ::::"
                                                  : ":::: Cant play song ::::";
  }

  auto w = display::tft.width();
  auto h = display::tft.height();

  // Header
  display::tft.fillRect(0, 0, w, FONT_HEIGHT + 8 + FONT_HEIGHT + 6,
                        0x0000); // Clear
  display::tft.setTextWrap(false);
  display::tft.setTextSize(1);
  // Dir name
  display::tft.setTextColor(0x49d4);
  display::tft.setCursor(4, FONT_HEIGHT + 8);
  display::tft.print(subtitle);
  // Name
  display::tft.setTextColor(0xFFFF);
  display::tft.setCursor(4, FONT_HEIGHT + 8 + FONT_HEIGHT + 4);
  display::tft.print(title);

  this->playState->setPlayState(!audio::isPaused());
  this->playState->run();

  int xt = w / 2;
  int yt = h - 5;
  int st = 6;
  display::tft.drawLine(xt - st, yt - st / 2, xt, yt, 0x5aab);
  display::tft.drawLine(xt + st, yt - st / 2, xt, yt, 0x5aab);
}

long HomeScreen::dependencies() {
  return utils::stringHash(music_loader::getSongPath().c_str()) * 10 +
         this->playState->dependencies() + audio::isPaused();
}

void HomeScreen::listFiles() {
  screen_manager::openScreen(new SongListScreen("/"));
}
void HomeScreen::openQueue() { screen_manager::openScreen(new QueueScreen()); }

void HomeScreen::nextSong() {
  music_loader::nextSong();
  audio::startPlaying();
}
void HomeScreen::previousSong() {
  music_loader::previousSong();
  audio::startPlaying();
}

void HomeScreen::playPause() { audio::pauseToggle(); }

ui::ControlScheme HomeScreen::controlScheme() { return this->control; }
} // namespace ui
