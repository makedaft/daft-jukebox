#pragma once
#include <Adafruit_ST7735.h>

#define TFT_CS 4    // CS
#define TFT_DC 12   // AO
#define TFT_RST 13  // RESET
#define TFT_MOSI 23 // SDA
#define TFT_SCLK 18 // SCK

namespace display {
static Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);
} // namespace display
