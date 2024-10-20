#pragma once
#include <Arduino.h>

#include "ui/_screen.h"

namespace screen_manager {
extern void openScreen(ui::Screen *t);
extern void goBack();

extern void setup();
extern void loop();

extern ui::ControlScheme controlScheme();
} // namespace screen_manager
