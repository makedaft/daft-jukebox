#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <vector>

#include "lib/SongQueue.cpp"
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

struct FileInfo {
  String name;
  String path;
  bool isDir;
};

static Song _currentSong = {.isAvailable = false};

static SongQueue _currentQueue;

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

static String getSongPath() { return _currentQueue.current(); }

static void nextSong() { _currentQueue.next(); }

static void previousSong() { _currentQueue.previous(); }

static Song &currentSong() { return _currentSong; }

static void loadSongWithQueue(String filePath, boolean append = false) {
  auto parentIndex = filePath.lastIndexOf('/');
  auto dirPath = filePath.substring(0, parentIndex);
  dirPath = dirPath.isEmpty() ? "/" : dirPath;
  _currentQueue.loadFromDir(SD, dirPath.c_str(), append);
  _currentQueue.setCurrentAs(filePath.c_str());
}

static std::vector<struct FileInfo> listSongFiles(const char *path) {
  std::vector<struct FileInfo> list;

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
