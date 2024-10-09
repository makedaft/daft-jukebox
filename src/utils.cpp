#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>

#include "log.cpp"

#define GUARD(expr)                                                            \
  if (!expr) {                                                                 \
    utils::preventLooping = true;                                              \
    return;                                                                    \
  }

namespace utils {
static bool preventLooping = false;
static bool skipLoop() { return preventLooping; }

static void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry = dir.openNextFile();

    if (!entry) {
      break;
    }

    for (uint8_t i = 0; i < numTabs; i++) {
      logger::printf("\t");
    }

    logger::printf(entry.name());

    if (entry.isDirectory()) {
      logger::printf("/\n");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      logger::printf("\t\t%d", entry.size());
    }

    entry.close();
  }

  logger::printf("\n");
}
} // namespace utils
