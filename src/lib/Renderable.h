#pragma once
#include <climits>

class Renderable {
  long previousDependency = LONG_MIN;
  bool firstRender = true;

  virtual void render() = 0;

public:
  virtual long dependencies() = 0;
  void run();
  void rerender();
};
