#include <esp32-hal-gpio.h>
#include <esp32-hal.h>

#include "lib/Button.cpp"
#include "runners/screen_manager.h"

#include "controls.h"

#define PIN_CONTROL_UP 21
#define PIN_CONTROL_DOWN 27
#define PIN_CONTROL_LEFT 32
#define PIN_CONTROL_RIGHT 33
#define PIN_CONTROL_ACTION1 35

namespace controls {
namespace {
static Button btnUp(PIN_CONTROL_UP);
static Button btnDown(PIN_CONTROL_DOWN);
static Button btnLeft(PIN_CONTROL_LEFT);
static Button btnRight(PIN_CONTROL_RIGHT);
// static Button btnAction1(PIN_CONTROL_ACTION1);
} // namespace

bool setup() {
  btnUp.setup();
  btnDown.setup();
  btnLeft.setup();
  btnRight.setup();
  // btnAction1.setup();
  return true;
}

void loop() {
  if (btnUp.isPressed())
    return screen_manager::controlScheme().up();

  if (btnDown.isPressed())
    return screen_manager::controlScheme().down();

  if (btnLeft.isPressed())
    return screen_manager::controlScheme().left();

  if (btnRight.isPressed())
    return screen_manager::controlScheme().right();

  // if (btnAction1.isPressed())
  //   return screen_manager::controlScheme().action1();
}
} // namespace controls
