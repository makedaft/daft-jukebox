#include "lib/Button.h"
#include "lib/logger.h"
#include "runners/screen_manager.h"

#include "controls.h"

namespace controls {
namespace {
static Button btnUp(PIN_CONTROL_UP);
static Button btnDown(PIN_CONTROL_DOWN);
static Button btnLeft(PIN_CONTROL_LEFT);
static Button btnRight(PIN_CONTROL_RIGHT);
static Button btnAction(PIN_CONTROL_ACTION);
} // namespace

bool isLocked = false;

bool setup() {
  btnUp.setup();
  btnDown.setup();
  btnLeft.setup();
  btnRight.setup();
  btnAction.setup();

  // Volume control setup
  pinMode(PIN_CONTROL_VOLUME, INPUT);
  analogReadResolution(10);

  return true;
}

void loop() {
  auto actionPressCount = btnAction.doublePressCount();
  if (actionPressCount == 2) {
    isLocked = !isLocked; // Toggle lock
    logger::debug(isLocked ? "Locked" : "Unlocked");
    return screen_manager::controlScheme().lock();
  }

  // Volume control
  audio::setVolume(analogRead(PIN_CONTROL_VOLUME) / 1024.);

  // If controls are locked, don't do anything
  // until the lock is released by double press
  if (isLocked)
    return;

  if (actionPressCount == 1)
    return screen_manager::controlScheme().action();

  if (btnUp.isPressed())
    return screen_manager::controlScheme().up();

  if (btnDown.isPressed())
    return screen_manager::controlScheme().down();

  if (btnLeft.isPressed())
    return screen_manager::controlScheme().left();

  if (btnRight.isPressed())
    return screen_manager::controlScheme().right();
}
} // namespace controls
