#pragma once
#include <Arduino.h>

#include "ui/_screen.h"

namespace screen_manager {
void openScreen(ui::Screen *t);

extern void render();

extern ui::ControlScheme controlScheme();
} // namespace screen_manager
