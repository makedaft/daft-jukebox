#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SPI.h>

#include "lib/display.h"
#include "runners/music_loader.h"
#include "ui/_screen.h"
#include "ui/components/SongList.h"

#include "ui/SongListScreen.h"

namespace ui {
void SongListScreen::render() { this->optionsMenu->render(); }

long SongListScreen::dependencies() {
  return this->optionsMenu->dependencies();
}

SongListScreen::SongListScreen(const char *dir) {
  this->optionsMenu = new ui::component::SongList(display::tft);
  this->optionsMenu->currentOptions = music_loader::listDirectory(dir);
  this->optionsMenu->dir = dir;
}

inline ui::ControlScheme SongListScreen::controlScheme() {
  return this->optionsMenu->controls;
}
} // namespace ui
