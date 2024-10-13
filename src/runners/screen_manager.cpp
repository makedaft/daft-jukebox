#pragma once
#include <Arduino.h>
#include <memory>

#include <ui/_screen.h>

#include "screen_manager.h"
#include "ui/HomeScreen.h"
#include "ui/SongListScreen.h"

namespace screen_manager {
namespace {
static std::unique_ptr<ui::Screen> currentScreen;
}

void openScreen(ui::Screen *t) {
  auto p = std::unique_ptr<ui::Screen>(t);
  currentScreen = std::move(p);
}

void render() { currentScreen->render(); }

ui::ControlScheme controlScheme() { return currentScreen->controlScheme(); }
} // namespace screen_manager
