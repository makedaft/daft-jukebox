#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>

#include "lib/logger.h"

#define GUARD(expr)                                                            \
  if (!expr) {                                                                 \
    utils::preventLooping = true;                                              \
    return;                                                                    \
  }

namespace utils {
extern bool preventLooping;

extern bool skipLoop();

extern void noop();

extern void printDirectory(File dir, int numTabs = 2);

extern long stringHash(const char *str);
} // namespace utils
