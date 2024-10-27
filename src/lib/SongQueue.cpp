#include <Arduino.h>
#include <FS.h>
#include <SD.h>

#include "lib/SongQueue.h"
#include "lib/logger.h"

void SongQueue::append(const char *path) {
  this->queue.push_back({.path = String(path)});
}

void SongQueue::insertNext(const char *path) {
  this->queue.insert(this->queue.begin() + currentIndex + 1,
                     {.path = String(path)});
}

void SongQueue::remove(const char *path) {
  if (this->empty())
    return;

  unsigned int index = 0;
  for (const QueueItem &item : this->queue) {
    if (item.path == path) {
      this->queue.erase(this->queue.begin() + index);
      this->queue.push_back({.path = "/Tool/Aenema.mp3"});
      if (this->currentIndex == index && this->currentIndex > 0)
        this->currentIndex--;
      return;
    }
    index++;
  }
}

void SongQueue::clear() {
  this->queue.clear();
  this->currentIndex = 0;
}

bool SongQueue::empty() { return this->queue.empty(); }
String SongQueue::current() {
  if (this->empty())
    return String();

  return this->queue[currentIndex].path;
}
unsigned int SongQueue::getCurrentIndex() { return currentIndex; }

void SongQueue::next() {
  if (this->empty())
    return;

  currentIndex++;
  if (currentIndex >= this->queue.size())
    currentIndex = 0;
}

void SongQueue::previous() {
  if (this->empty())
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
      this->currentIndex = index;
      found = true;
      return;
    }
    index++;
  }

  if (!found) {
    this->insertNext(path);
    this->currentIndex++;
  }
}

void SongQueue::loadFile(const char *filePath, LoadType type) {
  if (type == LOAD_NEXT)
    this->insertNext(filePath);
  else
    this->append(filePath);
}

void SongQueue::loadFromDir(fs::SDFS &fs, const char *path, boolean append) {
  if (!append)
    this->clear();

  File root = fs.open(path, FILE_READ, false);
  if (!root.isDirectory())
    return;

  while (true) {
    boolean isDir;
    String filePath = root.getNextFileName(&isDir);

    if (filePath.isEmpty() || isDir)
      break;

    loadFile(filePath.c_str(), LOAD_APPEND);
  }
}

void SongQueue::loadFromPlaylistFile(fs::SDFS &fs, const char *path,
                                     LoadType type) {
  if (type == LOAD_CLEAR)
    this->clear();

  File playlistF = fs.open(path, FILE_READ, false);
  if (playlistF.isDirectory())
    return;

  while (playlistF.available() > 0) {
    String filePath = playlistF.readStringUntil('\n');
    logger::printf("Playlist: %s\n", filePath.c_str());

    if (filePath.isEmpty() || !filePath.startsWith("/") || !fs.exists(filePath))
      break;

    loadFile(filePath.c_str(), type);
  }
}
