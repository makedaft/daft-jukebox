#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <vector>

#include "lib/SongQueue.cpp"
#include "lib/logger.cpp"
#include "lib/utils.cpp"

#include "runners/music_loader.h"

namespace music_loader {
CurrentSongInfo currentSongInfo = {.isAvailable = false};
SongQueue currentQueue;

bool setup() {
  // NOTE: This is relevant to display as well
  SPI.begin(PIN_SD_SCLK, PIN_SD_MISO, PIN_SD_MOSI, PIN_SD_CS);
  SPI.setDataMode(SPI_MODE0);
  delay(100);

  bool isReady = false;
  for (int i = 0; i < 5; i++) {
    if (SD.begin(PIN_SD_CS)) {
      isReady = true;
      break;
    }
    delay(100);
  }

  if (!isReady) {
    logger::error("SD Card Mount Failed");
  }

  // For debugging
  logger::msg("/");
  utils::printDirectory(SD.open("/"));
  logger::msg("-----");

  return isReady;
}

void loadSong(const char *filePath) {
  if (currentSongInfo.isAvailable) {
    currentSongInfo.isAvailable = false;
    currentSongInfo.file.close();
  }

  currentSongInfo.file = SD.open(filePath, FILE_READ, false);
  currentSongInfo.isAvailable = true;
}

String getSongPath() { return currentQueue.current(); }

void nextSong() { currentQueue.next(); }

void previousSong() { currentQueue.previous(); }

CurrentSongInfo &currentSong() { return currentSongInfo; }

void loadDirIntoQueue(String dirPath, boolean append = false) {
  dirPath = dirPath.isEmpty() ? "/" : dirPath;
  currentQueue.loadFromDir(SD, dirPath.c_str(), append);
}

void loadSongDirIntoQueue(String filePath, boolean append = false) {
  auto parentIndex = filePath.lastIndexOf('/');
  auto dirPath = filePath.substring(0, parentIndex);
  loadDirIntoQueue(dirPath, append);
  currentQueue.setCurrentAs(filePath.c_str());
}

std::vector<struct FileInfo> listDirectory(const char *path) {
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
