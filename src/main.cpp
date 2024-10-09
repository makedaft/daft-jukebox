#include <Arduino.h>
#include <FS.h>
#include <SD.h>

#include "audio.cpp"
#include "display.cpp"
#include "log.cpp"

#define PIN_VOLUME_UP 21
#define PIN_VOLUME_DOWN 34

void setup(void) {
  logger::setup();

  pinMode(PIN_VOLUME_UP, INPUT);
  pinMode(PIN_VOLUME_DOWN, INPUT);

  if (!audio::setup())
    return;

  audio::playMp3("/day-goes-on.mp3");

  if (!display::setup())
    return;
}

void loop() {
  audio::loop();

  auto volume = audio::getVolume();
  if (digitalRead(PIN_VOLUME_UP) > 0) {
    audio::setVolume(volume + 0.01);
  } else if (digitalRead(PIN_VOLUME_DOWN) > 0) {
    audio::setVolume(volume - 0.01);
  }

  display::loop();
}
