#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <vector>

#include "lib/SongQueue.h"
#include "lib/logger.h"

void SongQueue::append(const char *path) {
  this->queue.push_back({.path = path});
}

void SongQueue::insertNext(const char *path) {
  logger::printf("Inert nesxt: %s\n", path);
  this->queue.insert(this->queue.begin() + currentIndex + 1, {.path = path});
}

void SongQueue::remove(int index) {
  this->queue.erase(this->queue.begin() + index);
}

String SongQueue::current() { return this->queue[currentIndex].path; }
unsigned int SongQueue::getCurrentIndex() { return currentIndex; }

void SongQueue::next() {
  currentIndex++;
  if (currentIndex >= this->queue.size())
    currentIndex = 0;
}

void SongQueue::previous() {
  if (this->queue.size() == 0)
    return;

  if (currentIndex > 0)
    currentIndex--;
  else
    currentIndex = this->queue.size() - 1;
}

void SongQueue::setCurrentAs(const char *path) {
  boolean found = false;
  int index = 0;
  for (const QueueItem &item : this->queue) {
    if (item.path == path) {
      currentIndex = index;
      found = true;
      return;
    }
    index++;
  }

  if (!found) {
    this->queue.insert(this->queue.begin() + currentIndex + 1, {.path = path});
    currentIndex++;
  }
}

void SongQueue::loadFromDir(fs::SDFS &fs, const char *path, boolean append) {
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
