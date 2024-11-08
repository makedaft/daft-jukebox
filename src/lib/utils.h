#pragma once
#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>

#define GUARD(expr)                                                            \
  if (!expr) {                                                                 \
    utils::preventLooping = true;                                              \
    return;                                                                    \
  }

namespace utils {
extern bool preventLooping;

extern bool shouldSkipLoop();

extern void noop();

extern void printDirectory(File dir, int numTabs = 2);

extern long stringHash(const char *str);

template <typename T> class Optional {
  bool _isSome = false;
  T _value;

public:
  Optional() {}
  Optional(T value) { update(value); }

  void withValue(std::function<void(T)> fn) {
    if (_isSome)
      fn(_value);
  }
  bool isSome() { return _isSome; }

  void update(T value) {
    this->_isSome = true;
    this->_value = value;
  }
  void update() { this->_isSome = false; }
};
} // namespace utils
