#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <vector>

#include "log.cpp"

#define PIN_SD_CS 5 // chip select
#define PIN_SD_MOSI 23
#define PIN_SD_MISO 19
#define PIN_SD_SCLK 18

namespace music_loader {
struct Song {
  bool isAvailable;
  String filePath;
  File file;
};

static Song _currentSong = {.isAvailable = false};

static bool setup() {
  // NOTE: This is relevant to display as well
  SPI.begin(PIN_SD_SCLK, PIN_SD_MISO, PIN_SD_MOSI, PIN_SD_CS);
  SPI.setDataMode(SPI_MODE0);
  delay(500);

  bool isReady = false;
  for (int i = 0; i < 5; i++) {
    if (SD.begin(PIN_SD_CS)) {
      isReady = true;
      break;
    }
    delay(400);
  }

  if (!isReady) {
    logger::error("SD Card Mount Failed");
  }

  return isReady;
}

static void loadSong(const char *filePath) {
  if (_currentSong.isAvailable) {
    _currentSong.isAvailable = false;
    _currentSong.file.close();
  }

  _currentSong.file = SD.open(filePath, FILE_READ, false);
  _currentSong.filePath = filePath;
  _currentSong.isAvailable = true;
}

static Song &currentSong() { return _currentSong; }

} // namespace music_loader
