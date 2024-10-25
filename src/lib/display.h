#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SPI.h>
#include <muMatrix8ptRegular.h>

#define TFT_CS 4    // CS
#define TFT_DC 12   // AO
#define TFT_RST 13  // RESET
#define TFT_MOSI 23 // SDA
#define TFT_SCLK 18 // SCK
#define TFT_BACKLIGHT 25

#define FONT muMatrix8ptRegular
#define FONT_HEIGHT 8

namespace display {
extern Adafruit_ST7735 tft;

extern void setDisplayState(bool isOn);
} // namespace display
