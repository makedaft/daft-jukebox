#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>

#include "ui/_screen.h"
#include "ui/components/PlayState.h"
#include "ui/components/ProgressBar.h"

namespace ui {
class HomeScreen : public ui::Screen {
  ::ui::component::ProgressBar *progressBar;
  ::ui::component::PlayState *playState;

  void render();
  long dependencies();

  void listFiles();
  void openQueue();
  void nextSong();
  void previousSong();
  void playPause();

public:
  ControlScheme control;
  ui::ControlScheme controlScheme();

  HomeScreen();
};
} // namespace ui
