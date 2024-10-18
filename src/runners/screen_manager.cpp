#include <Arduino.h>
#include <memory>

#include <ui/_screen.h>

#include "lib/display.h"
#include "runners/screen_manager.h"
#include "ui/HomeScreen.h"

namespace screen_manager {
namespace {
static std::unique_ptr<ui::Screen> currentScreen;
}

void setup() { screen_manager::openScreen(new ui::HomeScreen()); }

void loop() { currentScreen->run(); }

void openScreen(ui::Screen *t) {
  display::tft.fillScreen(0x0000);
  auto p = std::unique_ptr<ui::Screen>(t);
  currentScreen = std::move(p);
}

ui::ControlScheme controlScheme() { return currentScreen->controlScheme(); }
} // namespace screen_manager
