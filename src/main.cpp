#include "mdl-obj.h"
#include "tiny_obj_loader.h"
#include <iostream>

int main() {
  auto obj = LoadObj("./assets/models/cube.obj");

  for (const auto vert : obj.vertices) {
    std::cout << vert << "\n";
  }
}
