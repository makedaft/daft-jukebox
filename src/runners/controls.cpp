#include <Arduino.h>

#include "lib/Button.h"
#include "lib/display.h"
#include "lib/logger.h"
#include "runners/audio.h"
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
  // Volume control setup
  analogReadResolution(ADC_RESOLUTION);
  pinMode(PIN_CONTROL_VOLUME, INPUT);

  // TODO: Temporary. Move display control somewhere else
  display::setDisplayState(true);

  btnAction.setup();
  btnAction.debounce = 300;
  btnAction.onDoublePress([]() {
    isLocked = !isLocked; // Toggle lock
    logger::debug(isLocked ? "Locked" : "Unlocked");
    display::setDisplayState(!isLocked);
    screen_manager::controlScheme().lock();
  });
  btnAction.onPress([]() {
    if (!isLocked)
      screen_manager::controlScheme().action();
  });

  btnUp.setup();
  btnUp.onPress([]() { screen_manager::controlScheme().up(); });

  btnDown.setup();
  btnDown.onPress([]() { screen_manager::controlScheme().down(); });

  btnLeft.setup();
  btnLeft.onPress([]() { screen_manager::controlScheme().left(); });

  btnRight.setup();
  btnRight.onPress([]() { screen_manager::controlScheme().right(); });

  return true;
}

void loop() {
  btnAction.loop();

  // Volume control
  audio::setVolume(analogRead(PIN_CONTROL_VOLUME) /
                   (1. * (1 << ADC_RESOLUTION)));

  // If controls are locked, don't do anything
  // until the lock is released by double press
  if (isLocked)
    return;

  btnUp.loop();
  btnDown.loop();
  btnLeft.loop();
  btnRight.loop();
}
} // namespace controls
