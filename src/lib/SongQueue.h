#pragma once

#include <FS.h>
#include <SD.h>
#include <vector>

struct QueueItem {
  String path;
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

  void loadFromDir(fs::SDFS &fs, const char *path, boolean append = false);
};
