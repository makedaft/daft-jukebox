#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SPI.h>

#include "lib/display.h"
#include "lib/logger.h"
#include "runners/music_loader.h"
#include "ui/_screen.h"
#include "ui/components/QueueList.h"

#include "ui/QueueScreen.h"

namespace ui {
void QueueScreen::render() { this->optionsMenu->render(); }

long QueueScreen::dependencies() { return this->optionsMenu->dependencies(); }

QueueScreen::QueueScreen() {
  this->optionsMenu = new ui::component::QueueList(display::tft);

  for (const auto &item : music_loader::currentQueue.queue) {
    this->optionsMenu->currentOptions.push_back({.path = item.path});
  }
}

inline ui::ControlScheme QueueScreen::controlScheme() {
  return this->optionsMenu->controlScheme;
}
} // namespace ui
