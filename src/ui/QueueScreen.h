#pragma once

#include "Adafruit_SPITFT.h"
#include "ui/_screen.h"
#include "ui/components/QueueList.h"

namespace ui {
class QueueScreen : public ui::Screen {
  ::ui::component::QueueList *optionsMenu;

  void render() override;
  long dependencies() override;

public:
  QueueScreen();

  ui::ControlScheme controlScheme() override;
};
} // namespace ui
