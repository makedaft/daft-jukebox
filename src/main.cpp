#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <cstdlib>

#include "audio.cpp"
#include "controls.cpp"
#include "display.cpp"
#include "logger.cpp"
#include "music_loader.cpp"
#include "utils.cpp"

void setup(void) {
  logger::setup();
  logger::debug("init.start");

  GUARD(music_loader::setup());
  logger::debug("init.music_loader");

  GUARD(audio::setup());
  logger::debug("init.audio");

  music_loader::loadSongWithQueue("/tool/hooker.mp3");
  music_loader::loadSongWithQueue("/ladedadedadeda.mp3");
  audio::playMp3(music_loader::getSongPath().c_str());

  controls::setup();
  logger::debug("init.controls");

  delay(500);
  GUARD(display::setup());
  logger::debug("init.display");

  logger::debug("init.end");
}

void loop() {
  if (utils::skipLoop())
    return;

  audio::loop();
  controls::loop();
  display::loop();
}
