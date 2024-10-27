#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <vector>

#include "lib/SongQueue.h"
#include "lib/logger.h"
#include "lib/utils.h"

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

  auto songPath = new String(filePath);
  if (songPath->isEmpty()) {
    currentSongInfo.isAvailable = false;
    return;
  }

  auto lastSlashI = songPath->lastIndexOf('/');
  auto dirPath = songPath->substring(0, lastSlashI) + "/";
  auto songName = songPath->substring(lastSlashI + 1);
  songName.replace(".mp3", "");
  currentSongInfo.name = songName;
  currentSongInfo.dirPath = dirPath;
  currentSongInfo.path = *songPath;
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

void addSongToEndOfQueue(String filePath) {
  if (isPlaylistFile(filePath)) {
    loadPlaylistIntoQueue(filePath, LOAD_APPEND);
    return;
  }

  currentQueue.append(filePath.c_str());
}

void addSongToNextInQueue(String filePath) {
  if (isPlaylistFile(filePath)) {
    loadPlaylistIntoQueue(filePath, LOAD_NEXT);
    return;
  }

  currentQueue.insertNext(filePath.c_str());
}

void loadSongDirIntoQueue(String filePath, boolean append = false) {
  if (isPlaylistFile(filePath)) {
    loadPlaylistIntoQueue(filePath, append ? LOAD_APPEND : LOAD_CLEAR);
    return;
  }

  auto parentIndex = filePath.lastIndexOf('/');
  auto dirPath = filePath.substring(0, parentIndex);
  loadDirIntoQueue(dirPath, append);
  currentQueue.setCurrentAs(filePath.c_str());
}

void loadPlaylistIntoQueue(String filePath, LoadType type) {
  currentQueue.loadFromPlaylistFile(SD, filePath.c_str(), type);
}

bool isPlaylistFile(String filePath) { return filePath.endsWith(".playlist"); }

void clearQueue() {
  if (currentSongInfo.isAvailable)
    currentSongInfo.file.close();
  currentSongInfo.name = "";
  currentSongInfo.dirPath = "";
  currentSongInfo.isAvailable = false;

  currentQueue.clear();
}

std::vector<struct FileInfo> listDirectory(const char *path) {
  std::vector<struct FileInfo> list;

  File root = SD.open(path);
  if (!root.isDirectory()) {
    logger::error("Not a directory");
    return list;
  }

  boolean isDir;
  String filePath;
  while (true) {
    filePath = root.getNextFileName(&isDir);
    if (filePath.isEmpty()) // If empty, no more files left
      break;

    if (filePath.startsWith("/") && SD.exists(filePath.c_str())) {
      list.push_back({.name = filePath, .path = filePath, .isDir = isDir});
    }
  }

  return list;
}

} // namespace music_loader
