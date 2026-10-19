#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct Obj {
  std::vector<float> vertices;
  std::vector<float> normals;
  std::vector<float> uv;
};

/* Private Functions */
static std::vector<std::string> OpenFile(const char *path) {
  std::ifstream inFile(path);

  std::vector<std::string> strings;
  if (!inFile) {
    std::cerr << "Error opening file!" << std::endl;
    return strings;
  }

  std::string line;
  while (std::getline(inFile, line)) {
    if (line.find("v ") != std::string::npos) {
      strings.emplace_back(line);
    }
  }

  inFile.close();

  return strings;
}

[[maybe_unused]] static std::vector<float>
ParseVertices(const std::vector<std::string> &strings) {
  std::vector<float> vertices;

  for (const auto &str : strings) {
    std::istringstream iss(str);
    std::string word;

    while (iss >> word) {
      if (word != "v") {
        vertices.emplace_back(std::stof(word));
      }
    }
  }

  return vertices;
}

/* Public Functions */
inline Obj LoadObj(const char *path) {
  const auto fileStrings = OpenFile(path);

  Obj obj;
  std::vector<float> *targetBuff = nullptr;

  for (const auto &str : fileStrings) {
    if (str.find("v ") != std::string::npos)
      targetBuff = &obj.vertices;
    else if (str.find("vn ") != std::string::npos)
      targetBuff = &obj.normals;
    else if (str.find("vt ") != std::string::npos)
      targetBuff = &obj.uv;
    else {
      targetBuff = nullptr;
      continue;
    }

    std::istringstream iss(str);
    std::string word;

    while (iss >> word) {
      try {
        targetBuff->emplace_back(std::stof(word));
      }

      catch (const std::invalid_argument &) {
        std::cout << "NaN\n";
        continue;
      }
    }
  }

  return obj;
}
