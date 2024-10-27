#pragma once

#include <FS.h>
#include <SD.h>
#include <vector>

struct QueueItem {
  String path;
};

enum LoadType {
  LOAD_CLEAR,
  LOAD_APPEND,
  LOAD_NEXT,
};

class SongQueue {
  unsigned int currentIndex = 0;

public:
  std::vector<struct QueueItem> queue;

  void append(const char *path);
  void insertNext(const char *path);
  void remove(const char *path);
  void clear();

  bool empty();
  String current();
  unsigned int getCurrentIndex();

  void next();

  void previous();

  void setCurrentAs(const char *path);

  void loadFile(const char *filePath, LoadType type);
  void loadFromDir(fs::SDFS &fs, const char *path, boolean append = false);
  void loadFromPlaylistFile(fs::SDFS &fs, const char *path,
                            LoadType append = LOAD_CLEAR);
};
