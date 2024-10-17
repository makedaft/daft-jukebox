#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <vector>

#include "lib/SongQueue.cpp"

#define PIN_SD_CS 5 // chip select
#define PIN_SD_MOSI 23
#define PIN_SD_MISO 19
#define PIN_SD_SCLK 18

struct CurrentSongInfo {
  bool isAvailable;
  File file;
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

extern void loadSong(const char *filePath);

extern String getSongPath();

extern void nextSong();

extern void previousSong();

extern CurrentSongInfo &currentSong();

extern void loadDirIntoQueue(String dirPath, boolean append);

extern void loadSongDirIntoQueue(String filePath, boolean append);

extern std::vector<struct FileInfo> listDirectory(const char *path);

} // namespace music_loader
