#pragma once
#include <climits>

class Renderable {
  long previousDependency = LONG_MIN;

  virtual void render() = 0;

protected:
  bool firstRender = true;

public:
  virtual long dependencies() = 0;
  void run();
};
