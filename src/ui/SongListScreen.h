#pragma once

#include "Adafruit_SPITFT.h"
#include "ui/_screen.h"
#include "ui/components/SongList.h"

namespace ui {
class SongListScreen : public ui::Screen {
  ui::component::SongList *optionsMenu;

  void render() override;
  long dependencies() override;

public:
  SongListScreen(const char *dir);
  void initialize() override;

  ui::ControlScheme controlScheme() override;
};
} // namespace ui
