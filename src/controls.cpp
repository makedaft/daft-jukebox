#include <Arduino.h>

#define PIN_VOLUME_UP 21
#define PIN_VOLUME_DOWN 34

#include "audio.cpp"

namespace controls {
static void setup() {
  pinMode(PIN_VOLUME_UP, INPUT);
  pinMode(PIN_VOLUME_DOWN, INPUT);
}

static inline void loop() {
  auto volume = audio::getVolume();

  if (digitalRead(PIN_VOLUME_UP) > 0) {
    audio::setVolume(volume + 0.01);
  } else if (digitalRead(PIN_VOLUME_DOWN) > 0) {
    audio::setVolume(volume - 0.01);
  }
}

} // namespace controls
