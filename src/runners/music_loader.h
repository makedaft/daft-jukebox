#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <vector>

#include "lib/SongQueue.h"

#define PIN_SD_CS 5 // chip select
#define PIN_SD_MOSI 23
#define PIN_SD_MISO 19
#define PIN_SD_SCLK 18

struct CurrentSongInfo {
  bool isAvailable;
  File file;
  String path;
  String name;
  String dirPath;
};

struct FileInfo {
  String name;
  String path;
  bool isDir;
};

namespace music_loader {
extern CurrentSongInfo currentSongInfo;
extern SongQueue currentQueue;

extern bool setup();

extern String getSongPath();
extern CurrentSongInfo &currentSong();

extern void nextSong();
extern void previousSong();

extern void addSongToEndOfQueue(String filePath);
extern void addSongToNextInQueue(String filePath);
extern void loadSong(const char *filePath);
extern void loadDirIntoQueue(String dirPath, boolean append);
extern void loadSongDirIntoQueue(String filePath, boolean append);
extern void loadPlaylistIntoQueue(String filePath, LoadType type);
extern bool isPlaylistFile(String filePath);
extern void clearQueue();

extern std::vector<struct FileInfo> listDirectory(const char *path);

} // namespace music_loader
