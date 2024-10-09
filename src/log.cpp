#pragma once
#include <HardwareSerial.h>

namespace logger {
static void setup() {
  Serial.begin(BAUD_RATE);
}

static void msg(const char* msg) {
  Serial.println(msg);
}

template<typename... Args>
static void printf(const char* fmt, Args... args) {
  Serial.printf(fmt, args...);
}

template<typename... Args>
static void error(const char* fmt, Args... args) {
  Serial.printf(fmt, args...);
}
}
