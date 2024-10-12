#pragma once
#include <Arduino.h>
#include <memory>

#include <ui/_screen.cpp>

namespace screen_manager {
static std::unique_ptr<ui::Screen> currentScreen;

template <typename T> void openScreen(T *t) {
  auto p = std::unique_ptr<T>(t);
  currentScreen = std::move(p);
}

inline void render() { currentScreen->render(); }

inline ui::ControlScheme controlScheme() {
  return currentScreen->controlScheme();
}
} // namespace screen_manager
