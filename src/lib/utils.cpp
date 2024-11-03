#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <functional>
#include <string>

#include "lib/logger.h"

#include "lib/utils.h"

namespace utils {
bool preventLooping = false;

bool shouldSkipLoop() { return preventLooping; }

void noop() {}

void printDirectory(File dir, int numTabs) {
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

long stringHash(const char *str) {
  return std::hash<std::string>{}(std::string(str));
}
} // namespace utils
