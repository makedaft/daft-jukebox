#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SPI.h>
// #include <muHeavy8ptBold.h>
#include <memory>
#include <muMatrix8ptRegular.h>
#include <vector>

#include "lib/logger.cpp"
#include "runners/screen_manager.cpp"
#include "ui/SongListScreen.cpp"
#include "ui/_screen.cpp"

#define TFT_CS 4    // CS
#define TFT_DC 12   // AO
#define TFT_RST 13  // RESET
#define TFT_MOSI 23 // SDA
#define TFT_SCLK 18 // SCK

#define FONT muMatrix8ptRegular
#define FONT_HEIGHT 8

namespace display {
static Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

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

  screen_manager::openScreen(new ui::SongListScreen(tft, "/"));

  return true;
}

static inline void loop() { screen_manager::render(); }

} // namespace display
