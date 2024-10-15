#pragma once

#include "Adafruit_SPITFT.h"
#include "ui/_screen.h"
#include "ui/components/SongList.h"

namespace ui {
class SongListScreen : public ui::Screen {
  ui::component::SongList *optionsMenu;

  void render();
  long dependencies();

public:
  SongListScreen(const char *dir);

  ui::ControlScheme controlScheme();
};
} // namespace ui
