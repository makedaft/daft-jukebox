#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <cstdint>
#include <functional>

#include "lib/display.h"
#include "lib/logger.cpp"
#include "lib/utils.h"
#include "runners/audio.h"
#include "runners/music_loader.h"
#include "runners/screen_manager.h"
#include "ui/QueueScreen.h"
#include "ui/_screen.h"

#include "ui/HomeScreen.h"
#include "ui/SongListScreen.h"
#include "ui/components/PlayState.h"
#include "ui/components/ProgressBar.h"

namespace ui {
HomeScreen::HomeScreen() {
  this->control.up = std::bind(&HomeScreen::listFiles, this);
  this->control.down = std::bind(&HomeScreen::openQueue, this);
  this->control.left = std::bind(&HomeScreen::previousSong, this);
  this->control.right = std::bind(&HomeScreen::nextSong, this);
  this->control.action1 = std::bind(&HomeScreen::playPause, this);

  auto w = display::tft.width();
  auto h = display::tft.height();
  int padx = 3;
  this->progressBar = new ui::component::ProgressBar(&display::tft, padx, h / 2,
                                                     w - 2 * padx, 6);

  this->playState = new ui::component::PlayState(&display::tft, w / 2, 53);
}

void HomeScreen::render() {
  display::tft.fillRect(0, 0, display::tft.width(),
                        FONT_HEIGHT + 8 + FONT_HEIGHT + 4, 0x0000);
  auto songInfo = music_loader::currentSong();
  display::tft.setTextWrap(false);
  display::tft.setTextSize(1);
  // Dir name
  display::tft.setTextColor(0x49d4);
  display::tft.setCursor(4, FONT_HEIGHT + 8);
  display::tft.print(songInfo.dirPath);
  // Name
  display::tft.setTextColor(0xFFFF);
  display::tft.setCursor(4, FONT_HEIGHT + 8 + FONT_HEIGHT + 4);
  display::tft.print(songInfo.name);

  this->playState->setPlayState(!audio::isPaused());
  this->playState->run();

  this->progressBar->setPercentage(60);
  this->progressBar->run();
}

long HomeScreen::dependencies() {
  return (utils::stringHash(music_loader::getSongPath().c_str()) * 100 +
          this->progressBar->dependencies()) *
             10 +
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
