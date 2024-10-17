#pragma once

#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <vector>

#include "lib/logger.cpp"

struct QueueItem {
  String path;
};

class SongQueue {
  int currentIndex = 0;

public:
  std::vector<struct QueueItem> queue;

  // void append(const char *path) { this->queue.push_back({.path = path}); }
  // void remove(int index) { this->queue.erase(this->queue.begin() + index); }

  String current() { return this->queue[currentIndex].path; }

  void next() {
    currentIndex++;
    if (currentIndex >= this->queue.size())
      currentIndex = 0;
  }

  void previous() {
    if (this->queue.size() == 0)
      return;

    if (currentIndex > 0)
      currentIndex--;
    else
      currentIndex = this->queue.size() - 1;
  }

  void setCurrentAs(const char *path) {
    boolean found = false;
    int index = 0;
    for (auto &item : this->queue) {
      if (item.path == path) {
        currentIndex = index;
        found = true;
        return;
      }
      index++;
    }

    if (!found) {
      this->queue.insert(this->queue.begin() + currentIndex + 1,
                         {.path = path});
      currentIndex++;
    }
  }

  void loadFromDir(fs::SDFS &fs, const char *path, boolean append = false) {
    if (!append)
      this->queue.clear();

    File root = fs.open(path, FILE_READ, false);
    if (!root.isDirectory())
      return;

    while (true) {
      boolean isDir;
      String filePath = root.getNextFileName(&isDir);

      if (filePath.isEmpty())
        break;

      if (!isDir)
        this->queue.push_back({.path = filePath});
    }
  }
};
