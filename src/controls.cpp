#include <esp32-hal-gpio.h>

#include "audio.cpp"

#define PIN_VOLUME_UP 21
#define PIN_VOLUME_DOWN 27

namespace controls {
static void setup() {
  pinMode(PIN_VOLUME_UP, INPUT_PULLUP);
  pinMode(PIN_VOLUME_DOWN, INPUT_PULLUP);
}

static inline void loop() {
  auto volume = audio::getVolume();
  // TODO: Use log scale increments?

  if (digitalRead(PIN_VOLUME_UP) == 0) {
    audio::setVolume(volume + 0.02);
  } else if (digitalRead(PIN_VOLUME_DOWN) == 0) {
    audio::setVolume(volume - 0.02);
  }
}

} // namespace controls
