#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <cstring>

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
    if (item.path == String(path)) {
      this->queue.erase(this->queue.begin() + index);

      if (index < this->currentIndex)
        this->currentIndex--;

      if (this->currentIndex >= this->queue.size())
        this->currentIndex = this->queue.size() - 1;

      if (this->currentIndex < 0)
        this->currentIndex = 0;

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

void SongQueue::addMp3File(fs::SDFS &fs, String filePath, LoadType type) {
  auto pathC = filePath.c_str();
  if (filePath.isEmpty() || !filePath.startsWith("/") || !fs.exists(pathC)) {
    logger::printf("[err] Invalid file path: %s\n", pathC);
    return;
  }

  if (type == LOAD_NEXT)
    this->insertNext(pathC);
  else
    this->append(pathC);
}

void SongQueue::loadFromDir(fs::SDFS &fs, const char *path, boolean append) {
  if (!append)
    this->clear();

  File root = fs.open(path, FILE_READ, false);
  if (!root.isDirectory())
    return;

  boolean isDir;
  String filePath;
  while (true) {
    filePath = root.getNextFileName(&isDir);
    if (filePath.isEmpty()) // If empty, no more files left
      return;

    if (!isDir)
      addMp3File(fs, filePath, LOAD_APPEND);
  }
}

void SongQueue::loadFromPlaylistFile(fs::SDFS &fs, const char *path,
                                     LoadType type) {
  if (type == LOAD_CLEAR)
    this->clear();

  File playlistF = fs.open(path, FILE_READ, false);
  if (playlistF.isDirectory())
    return;

  String filePath;
  while (playlistF.available() > 0) {
    filePath = playlistF.readStringUntil('\n');
    logger::printf("Playlist: %s\n", filePath.c_str());

    addMp3File(fs, filePath, type);
  }
}
