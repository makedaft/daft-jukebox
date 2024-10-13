#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>

#include "lib/logger.cpp"

#define GUARD(expr)                                                            \
  if (!expr) {                                                                 \
    utils::preventLooping = true;                                              \
    return;                                                                    \
  }

namespace utils {
static bool preventLooping = false;
static bool skipLoop() { return preventLooping; }

static void noop() {}

static void printDirectory(File dir, int numTabs = 2) {
  while (true) {
    File entry = dir.openNextFile();

    if (!entry) {
      break;
    }

    for (uint8_t i = 0; i < numTabs; i++) {
      logger::printf(" ");
    }

    logger::printf("/%s", entry.name());

    if (entry.isDirectory()) {
      logger::msg("/");
      printDirectory(entry, numTabs + 1);
    } else {
      logger::printf("\t\t%d\n", entry.size());
    }

    entry.close();
  }
}
} // namespace utils
