#pragma once
#include <climits>

class Renderable {
  long previousDependency = LONG_MIN;

  virtual long dependencies() = 0;
  virtual void render() = 0;

protected:
  bool firstRender = true;

public:
  void run();
};
