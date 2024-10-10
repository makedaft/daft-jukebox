#include <esp32-hal-gpio.h>

#include "audio.cpp"

#define PIN_CONTROL_UP 21
#define PIN_CONTROL_DOWN 27
#define PIN_CONTROL_LEFT 32
#define PIN_CONTROL_RIGHT 33

namespace controls {
static void setup() {
  pinMode(PIN_CONTROL_UP, INPUT_PULLUP);
  pinMode(PIN_CONTROL_DOWN, INPUT_PULLUP);
  pinMode(PIN_CONTROL_LEFT, INPUT_PULLUP);
  pinMode(PIN_CONTROL_RIGHT, INPUT_PULLUP);
}

static inline void loop() {
  auto volume = audio::getVolume();
  // TODO: Use log scale increments?

  if (digitalRead(PIN_CONTROL_UP) == 0) {
    audio::setVolume(volume + 0.02);
  } else if (digitalRead(PIN_CONTROL_DOWN) == 0) {
    audio::setVolume(volume - 0.02);
  } else if (digitalRead(PIN_CONTROL_LEFT) == 0) {
    music_loader::previousSong();
    audio::playMp3(music_loader::getSongPath().c_str());
  } else if (digitalRead(PIN_CONTROL_RIGHT) == 0) {
    music_loader::nextSong();
    audio::playMp3(music_loader::getSongPath().c_str());
  }
}

} // namespace controls
