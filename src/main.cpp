#include "mdl-obj.h"
#include <iostream>

int main() {
  desobj::StreamWrapper sw;
  if (!sw.OpenFile("./assets/models/test.txt")) {
    std::cerr << "Failed to open file\n";
    return -1;
  }

  std::cout << "File opened successfully\n";

  // sw.PrintDebug();

  sw.SkipAllSpace(true);

  sw.SkipWord();
  std::cout << sw.ExtractWord() << '\n';
  sw.SkipWord();
  std::cout << sw.ExtractWord() << '\n';
  sw.SkipWord();
  std::cout << sw.ExtractWord() << '\n';
}
