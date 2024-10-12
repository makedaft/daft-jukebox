#pragma once
#include <esp32-hal-gpio.h>
#include <esp32-hal.h>

#include "runners/audio.cpp"
#include "runners/screen_manager.cpp"

#define PIN_CONTROL_UP 21
#define PIN_CONTROL_DOWN 27
#define PIN_CONTROL_LEFT 32
#define PIN_CONTROL_RIGHT 33

namespace controls {
namespace {
static const int THROTTLE_INTERVAL = 80;
static unsigned long lastCheckTime = millis();
} // namespace

static bool setup() {
  pinMode(PIN_CONTROL_UP, INPUT_PULLUP);
  pinMode(PIN_CONTROL_DOWN, INPUT_PULLUP);
  pinMode(PIN_CONTROL_LEFT, INPUT_PULLUP);
  pinMode(PIN_CONTROL_RIGHT, INPUT_PULLUP);
  return true;
}

static inline void loop() {
  // TODO: Better throttling
  if (millis() - lastCheckTime <= THROTTLE_INTERVAL)
    return;

  lastCheckTime = millis();

  auto control = screen_manager::controlScheme();

  if (digitalRead(PIN_CONTROL_UP) == 0) {
    control.up();
    // audio::setVolume(audio::getVolume() + 0.02);
    return;
  }

  if (digitalRead(PIN_CONTROL_DOWN) == 0) {
    control.down();
    // audio::setVolume(audio::getVolume() - 0.02);
    return;
  }

  if (digitalRead(PIN_CONTROL_LEFT) == 0) {
    control.left();
    // music_loader::previousSong();
    // audio::startPlaying();
    return;
  }

  if (digitalRead(PIN_CONTROL_RIGHT) == 0) {
    control.right();
    // music_loader::nextSong();
    // audio::startPlaying();
    return;
  }
}

} // namespace controls
