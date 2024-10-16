#include <climits>

#include "Renderable.h"

void Renderable::run() {
  if (this->firstRender || this->dependencies() == this->previousDependency)
    return;
  if (this->firstRender)
    this->firstRender = false;

  this->render();
}
