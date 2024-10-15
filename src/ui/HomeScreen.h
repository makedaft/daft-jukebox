#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>

#include "ui/_screen.h"

namespace ui {
class HomeScreen : public ui::Screen {
  void render();
  long dependencies();

  void listFiles();
  void nextSong();
  void previousSong();
  void playPause();

public:
  ControlScheme control;
  ui::ControlScheme controlScheme();

  HomeScreen();
};
} // namespace ui
