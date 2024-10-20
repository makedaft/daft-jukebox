#include <climits>

#include "Renderable.h"

void Renderable::run() {
  auto dep = this->dependencies();
  if (!this->firstRender && dep == this->previousDependency)
    return;
  if (this->firstRender)
    this->firstRender = false;

  this->previousDependency = dep;

  this->render();
}

void Renderable::rerender() { this->firstRender = true; }
