#include "tiny_obj_loader.h"
#include <iostream>

int main() {
  std::string inputfile = "./assets/models/cube.obj";
  tinyobj::ObjReaderConfig reader_config;

  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(inputfile, reader_config)) {
    if (!reader.Error().empty()) {
      std::cerr << "TinyObjReader: " << reader.Error();
    }

    exit(1);
  }
}
