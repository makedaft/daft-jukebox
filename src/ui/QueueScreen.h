#pragma once

#include "ui/_screen.h"
#include "ui/components/QueueList.h"

namespace ui {
class QueueScreen : public ui::Screen {
  ::ui::component::QueueList *optionsMenu;

  void render() override;
  long dependencies() override;

public:
  QueueScreen();
  void initialize() override;

  ui::ControlScheme controlScheme() override;
};
} // namespace ui
