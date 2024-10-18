#pragma once

#include <FS.h>
#include <SD.h>
#include <vector>

struct QueueItem {
  String path;
};

class SongQueue {
  int currentIndex = 0;

public:
  std::vector<struct QueueItem> queue;

  // void append(const char *path);
  // void remove(int index);

  String current();

  void next();

  void previous();

  void setCurrentAs(const char *path);

  void loadFromDir(fs::SDFS &fs, const char *path, boolean append = false);
};
