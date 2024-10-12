#pragma once
#include <esp32-hal-gpio.h>
#include <esp32-hal.h>

#include "lib/Button.cpp"
#include "runners/screen_manager.cpp"

#define PIN_CONTROL_UP 21
#define PIN_CONTROL_DOWN 27
#define PIN_CONTROL_LEFT 32
#define PIN_CONTROL_RIGHT 33

namespace controls {
namespace {
static Button btnUp(PIN_CONTROL_UP);
static Button btnDown(PIN_CONTROL_DOWN);
static Button btnLeft(PIN_CONTROL_LEFT);
static Button btnRight(PIN_CONTROL_RIGHT);
} // namespace

static bool setup() {
  btnUp.setup();
  btnDown.setup();
  btnLeft.setup();
  btnRight.setup();
  return true;
}

static inline void loop() {
  auto control = screen_manager::controlScheme();

  if (btnUp.isPressed())
    return control.up();

  if (btnDown.isPressed())
    return control.down();

  if (btnLeft.isPressed())
    return control.left();

  if (btnRight.isPressed())
    return control.right();
}
} // namespace controls
