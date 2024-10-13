#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SPI.h>

#include "lib/display.h"
#include "lib/logger.cpp"
#include "runners/music_loader.h"
#include "ui/_screen.h"
#include "ui/components/SongList.h"

#include "ui/SongListScreen.h"

namespace ui {
void SongListScreen::renderScreen() {
  display::tft.setCursor(50, 50);
  display::tft.print("Yaho");
  this->optionsMenu->render();
}

bool SongListScreen::shouldRender() {
  return this->optionsMenu->shouldRender();
}

SongListScreen::SongListScreen(const char *dir) {
  this->optionsMenu = new ui::component::SongList(display::tft);
  this->optionsMenu->currentOptions = music_loader::listDirectory(dir);
  this->optionsMenu->dir = dir;
}

inline ui::ControlScheme SongListScreen::controlScheme() {
  return this->optionsMenu->controlScheme;
}
} // namespace ui
