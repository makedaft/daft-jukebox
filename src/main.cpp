#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <cstdlib>

#include "lib/logger.h"
#include "lib/utils.h"
#include "runners/audio.h"
#include "runners/controls.h"
#include "runners/display.h"
#include "runners/music_loader.h"

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

  audio::loop();
  controls::loop();
  display::loop();
}
