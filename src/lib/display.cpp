#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SPI.h>

#include "esp32-hal-gpio.h"
#include "lib/display.h"

namespace display {
Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

void setDisplayState(bool isOn) { digitalWrite(TFT_BACKLIGHT, isOn); }
} // namespace display
