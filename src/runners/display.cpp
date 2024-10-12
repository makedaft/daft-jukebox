#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SPI.h>
#include <muMatrix8ptRegular.h>

#include "lib/display.cpp"
#include "lib/logger.cpp"
#include "runners/screen_manager.cpp"
#include "ui/SongListScreen.cpp"

#define FONT muMatrix8ptRegular
#define FONT_HEIGHT 8

namespace display {
const int HEIGHT = tft.height();
const int WIDTH = tft.width();

static bool setup() {
  tft.initR(INITR_BLACKTAB);

  tft.fillScreen(0x0000);
  tft.setFont(&FONT);
  tft.setTextColor(0xFFFF);
  tft.setTextSize(2);

  tft.setCursor(10, 20);
  tft.print("Owyn");

  screen_manager::openScreen(new ui::SongListScreen("/"));

  return true;
}

static inline void loop() { screen_manager::render(); }

} // namespace display
