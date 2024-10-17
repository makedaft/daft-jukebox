#pragma once

#include "Adafruit_SPITFT.h"
#include "ui/_screen.h"
#include "ui/components/QueueList.h"

namespace ui {
class QueueScreen : public ui::Screen {
  ::ui::component::QueueList *optionsMenu;

  void render();
  long dependencies();

public:
  QueueScreen();

  ui::ControlScheme controlScheme();
};
} // namespace ui
