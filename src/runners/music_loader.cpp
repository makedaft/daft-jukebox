#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <vector>

#include "lib/SongQueue.cpp"
#include "lib/logger.cpp"
#include "lib/utils.cpp"

#define PIN_SD_CS 5 // chip select
#define PIN_SD_MOSI 23
#define PIN_SD_MISO 19
#define PIN_SD_SCLK 18

struct CurrentSongInfo {
  bool isAvailable;
  File file;
};

struct FileInfo {
  String name;
  String path;
  bool isDir;
};

namespace music_loader {
namespace {
static CurrentSongInfo currentSongInfo = {.isAvailable = false};
static SongQueue currentQueue;
} // namespace

static bool setup() {
  // NOTE: This is relevant to display as well
  SPI.begin(PIN_SD_SCLK, PIN_SD_MISO, PIN_SD_MOSI, PIN_SD_CS);
  SPI.setDataMode(SPI_MODE0);
  delay(200);

  bool isReady = false;
  for (int i = 0; i < 5; i++) {
    if (SD.begin(PIN_SD_CS)) {
      isReady = true;
      break;
    }
    delay(200);
  }

  if (!isReady) {
    logger::error("SD Card Mount Failed");
  }

  // For debugging
  utils::printDirectory(SD.open("/"), 1);

  return isReady;
}

static inline void loop() {}

static void loadSong(const char *filePath) {
  if (currentSongInfo.isAvailable) {
    currentSongInfo.isAvailable = false;
    currentSongInfo.file.close();
  }

  currentSongInfo.file = SD.open(filePath, FILE_READ, false);
  currentSongInfo.isAvailable = true;
}

static String getSongPath() { return currentQueue.current(); }

static void nextSong() { currentQueue.next(); }

static void previousSong() { currentQueue.previous(); }

static CurrentSongInfo &currentSong() { return currentSongInfo; }

static void loadDirIntoQueue(String dirPath, boolean append = false) {
  dirPath = dirPath.isEmpty() ? "/" : dirPath;
  currentQueue.loadFromDir(SD, dirPath.c_str(), append);
}

static void loadSongDirIntoQueue(String filePath, boolean append = false) {
  auto parentIndex = filePath.lastIndexOf('/');
  auto dirPath = filePath.substring(0, parentIndex);
  loadDirIntoQueue(dirPath, append);
  currentQueue.setCurrentAs(filePath.c_str());
}

static std::vector<struct FileInfo> listDirectory(const char *path) {
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
