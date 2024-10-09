#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <cstdlib>

#include "audio.cpp"
#include "controls.cpp"
#include "display.cpp"
#include "log.cpp"
#include "music_loader.cpp"
#include "utils.cpp"

void setup(void) {
  logger::setup();
  logger::debug("init.start");

  GUARD(music_loader::setup());
  logger::debug("init.music_loader");

  utils::printDirectory(SD.open("/"), 1);

  GUARD(audio::setup());
  logger::debug("init.audio");

  audio::playMp3("/ladedadedadeda.mp3");

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
