#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <vector>

#include "logger.cpp"
#include "utils.cpp"

#define PIN_SD_CS 5 // chip select
#define PIN_SD_MOSI 23
#define PIN_SD_MISO 19
#define PIN_SD_SCLK 18

namespace music_loader {
struct Song {
  bool isAvailable;
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

  // For debugging
  utils::printDirectory(SD.open("/"), 1);

  return isReady;
}

static void loadSong(const char *filePath) {
  if (_currentSong.isAvailable) {
    _currentSong.isAvailable = false;
    _currentSong.file.close();
  }

  _currentSong.file = SD.open(filePath, FILE_READ, false);
  _currentSong.isAvailable = true;
}

static String nextSong() {
  // TODO: Implement
  if (_currentSong.isAvailable) {
    return _currentSong.file.path();
  }
  return "/ladedadedadeda.mp3";
}

static String previousSong() {
  // TODO: Implement
  if (_currentSong.isAvailable) {
    return _currentSong.file.path();
  }
  return "/ladedadedadeda.mp3";
}

static Song &currentSong() { return _currentSong; }

struct BasicSongInfo {
  String name;
  String path;
  bool isDir;
};

static std::vector<BasicSongInfo> listSongs(const char *path) {
  std::vector<BasicSongInfo> list;

  File root = SD.open(path);
  if (!root.isDirectory()) {
    logger::error("Not a directory");
    return list;
  }

  while (true) {
    boolean isDir;
    String filePath = root.getNextFileName(&isDir);

    if (filePath.isEmpty())
      break;

    list.push_back({.name = filePath, .path = filePath, .isDir = isDir});
  }

  return list;
}

} // namespace music_loader
