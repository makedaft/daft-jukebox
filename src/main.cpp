#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <cstdlib>

#include "lib/logger.cpp"
#include "lib/utils.cpp"
#include "runners/audio.cpp"
#include "runners/controls.cpp"
#include "runners/display.cpp"
#include "runners/music_loader.cpp"

void setup(void) {
  Serial.begin(BAUD_RATE);
  logger::debug("init.start");

  GUARD(music_loader::setup());
  logger::debug("init.music_loader");

  GUARD(audio::setup());
  logger::debug("init.audio");

  music_loader::loadDirIntoQueue("/tool", true);
  music_loader::loadSongDirIntoQueue("/ladedadedadeda.mp3", true);
  audio::startPlaying();

  GUARD(controls::setup());
  logger::debug("init.controls");

  GUARD(display::setup());
  logger::debug("init.display");

  logger::debug("init.end");
}

void loop() {
  if (utils::skipLoop())
    return;

  music_loader::loop();
  audio::loop();
  controls::loop();
  display::loop();
}
