#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SPI.h>

#include "lib/display.h"
#include "runners/screen_manager.h"

#include "runners/display.h"

namespace display {
bool setup() {
  display::tft.initR(INITR_BLACKTAB);
  display::tft.fillScreen(0x0000);
  display::tft.setFont(&FONT);
  display::tft.setTextColor(0xFFFF);
  display::tft.setTextSize(1);

  screen_manager::setup();

  return true;
}

void loop() { screen_manager::loop(); }
} // namespace display
