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
#include "ui/_screen.h"

#include "ui/HomeScreen.h"
#include "ui/SongListScreen.h"
#include "ui/components/ProgressBar.h"

namespace ui {
HomeScreen::HomeScreen() {
  this->control.up = std::bind(&HomeScreen::playPause, this);
  this->control.down = std::bind(&HomeScreen::listFiles, this);
  this->control.left = std::bind(&HomeScreen::previousSong, this);
  this->control.right = std::bind(&HomeScreen::nextSong, this);
  this->control.action1 = std::bind(&HomeScreen::playPause, this);

  auto w = display::tft.width();
  auto h = display::tft.height();
  int padx = 3;
  this->progressBar =
      new ui::component::ProgressBar(padx, h / 2, w - 2 * padx, 6);
}

void HomeScreen::render() {
  int16_t w = display::tft.width();
  int16_t h = display::tft.height();

  display::tft.fillScreen(0x0000);
  display::tft.setTextSize(1);
  display::tft.setTextWrap(false);

  auto songPath = new String(music_loader::getSongPath());
  auto lastSlashI = songPath->lastIndexOf('/');
  auto dirName = songPath->substring(0, lastSlashI) + "/";
  auto songName = songPath->substring(lastSlashI + 1);
  songName.replace(".mp3", "");
  // Dir name
  display::tft.setTextColor(0x49d4);
  display::tft.setCursor(4, FONT_HEIGHT + 8);
  display::tft.print(dirName);
  // Name
  display::tft.setTextColor(0xFFFF);
  display::tft.setCursor(4, FONT_HEIGHT + 8 + FONT_HEIGHT + 4);
  display::tft.print(songName);

  int sc = 18;
  int st = sc * 95 / 100;
  int xc = w / 2;
  int yc = 53;
  int xt = xc - st / 3 - 2;
  int yt = yc;
  display::tft.fillCircle(xc, yc, sc, 0xFFFF);
  display::tft.fillTriangle(xt + st, yt, xt, yt - st / 2, xt, yt + st / 2,
                            0x0000);
  // display::tft.fillCircle(w / 4, yc, sc / 2, 0xDDDD);
  // display::tft.drawLine(w / 4 + st / 2, yt, w / 4, yt - st / 4, 0x0000);
  // display::tft.drawLine(w / 4 + st / 2, yt, w / 4, yt + st / 4, 0x0000);
  // display::tft.fillCircle(w * 3 / 4, yc, sc / 2, 0xDDDD);
  // display::tft.drawLine(w * 3 / 4 + st / 2, yt, w * 3 / 4, yt - st / 4,
  // 0x0000);
  // display::tft.drawLine(w * 3 / 4 + st / 2, yt, w * 3 / 4, yt + st /
  // 4, 0x0000);

  this->progressBar->setPercentage(60);
  this->progressBar->run();
}

long HomeScreen::dependencies() {
  // TODO: Memoize hashed value
  return utils::stringHash(music_loader::getSongPath().c_str()) * 100 +
         this->progressBar->dependencies();
}

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

void HomeScreen::playPause() { audio::pauseToggle(); }

ui::ControlScheme HomeScreen::controlScheme() { return this->control; }
} // namespace ui
