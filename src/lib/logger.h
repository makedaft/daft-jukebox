#pragma once
#include <HardwareSerial.h>

namespace logger {
static inline void setup() { Serial.begin(BAUD_RATE); }

static inline void msg(const char *msg) { Serial.println(msg); }

static inline void error(const char *err) { Serial.println(err); }

template <typename... Args>
static inline void printf(const char *fmt, Args... args) {
  Serial.printf(fmt, args...);
}

static inline void debug(const char *msg) { Serial.println(msg); }
} // namespace logger
