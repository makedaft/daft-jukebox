#include <Arduino.h>
#include <memory>

#include <ui/_screen.h>

#include "lib/display.h"
#include "lib/logger.h"
#include "runners/screen_manager.h"
#include "ui/HomeScreen.h"

namespace screen_manager {
namespace {
// TODO: Screen queue?
static std::unique_ptr<ui::Screen> previousScreen;
static std::unique_ptr<ui::Screen> currentScreen;
} // namespace

void setup() { screen_manager::openScreen(new ui::HomeScreen()); }

void loop() { currentScreen->run(); }

void openScreen(ui::Screen *t) {
  display::tft.fillScreen(0x0000);
  previousScreen = std::move(currentScreen);
  auto p = std::unique_ptr<ui::Screen>(t);
  currentScreen = std::move(p);
  currentScreen->rerender();
}

void goBack() {
  display::tft.fillScreen(0x0000);
  currentScreen = std::move(previousScreen);
  currentScreen->rerender();
}

ui::ControlScheme controlScheme() { return currentScreen->controlScheme(); }
} // namespace screen_manager
