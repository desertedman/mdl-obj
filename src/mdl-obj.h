#pragma once

#ifndef SW_EOF
#define SW_EOF (std::char_traits<char>::eof())

#include <cctype>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace desobj {
struct Face {
  int v;  // vertex
  int vt; // tex coord
  int vn; // normal

  Face() : v(-1), vt(-1), vn(-1) {}
};

struct Obj {
  std::vector<float> vertices;
  std::vector<float> normals;
  std::vector<float> uv;
  std::vector<Face> faces;
};

class StreamWrapper {
public:
  void PrintDebug() { std::cout << file.rdbuf(); }

  bool OpenFile(const char *path) {
    file.open(path);

    if (!file) {
      std::cerr << "ERROR: SW could not open file.\n";
      return false;
    }

    return true;
  }

  bool IsValidChar(const char c) {
    if (c == '+' || c == '-' || c == '/' || c == '.')
      return true;

    if (c == '#')
      return false;

    return std::isalnum(static_cast<unsigned char>(c));
  }

  bool IsSpace(const char c) {
    if (c == ' ' || c == '\t' || c == '#')
      return true;

    return false;
  }

  auto FindCharOffset(const char c, bool skipCurrChar) {
    int offset = 0;
    if (skipCurrChar)
      offset++;

    char currChar = PeekAtOffset(offset);

    while (currChar != c) {
      currChar = PeekAtOffset(offset);
      if (currChar == c)
        break;

      // Char not found
      else if (currChar == '\0' || currChar == SW_EOF)
        return -1;

      offset++;
    }

    return offset;
  }

  auto SkipLine() {
    auto currChar = PeekAtOffset(0);

    if (currChar == '\n')
      file.ignore(1);

    else {
      auto nextPos = FindCharOffset('\n', true);
      file.seekg(nextPos + 1, std::ios::cur);
    }
  }

  bool SkipAllSpace(bool skipLines = false) {
    int currChar{-1};

    do {
      currChar = file.peek();

      // check for EOF first; EOF can not fit into a char
      if (currChar == std::ifstream::traits_type::eof()) {
        std::cout << "end of file\n";
        return false;
      }

      // comment
      else if (currChar == '#' && skipLines) {
        SkipLine();
      }

      else if (currChar == '#' && !skipLines) {
        std::cout << "end of line\n";
        break;
      }

      else if (currChar == '\n' && skipLines) {
        file.ignore(1);
      }

      else if (currChar == '\n' && !skipLines) {
        std::cout << "end of line\n";
        break;
      }

      else if (IsSpace(currChar)) {
        file.ignore(1);
      }
    }

    while (IsSpace(currChar) || currChar == '\n');

    return true;
  }

  // Returns '\0' if error, or 'std::char_traits<char>::eof()' (SW_EOF macro) if
  // EOF
  char PeekAtOffset(std::streampos offset) {
    std::streampos origPos = file.tellg();

    // tellg fails (file corrupt or closed)
    if (origPos == std::streampos(-1))
      return '\0';

    // EOF
    else if (origPos == std::streampos(-1))
      return SW_EOF;

    // Seek to offset relative to curr pos
    file.seekg(offset, std::ios::cur);
    auto peekChar = file.peek();

    // Clear EOF flags and return to original position
    file.clear();
    file.seekg(origPos);

    return peekChar;
  }

  std::string ExtractWord() {
    std::streampos origPos = file.tellg();

    size_t len{0};
    char currChar = PeekAtOffset(0);

    while (IsValidChar(currChar)) {
      currChar = PeekAtOffset(len);

      if (IsValidChar(currChar))
        len++;
    }

    std::string word(len, '\0');
    file.read(&word[0], len);

    // Clear EOF flags and return to original position
    file.clear();
    file.seekg(origPos);

    return word;
  }

  auto SkipWord() {
    auto word = ExtractWord();
    auto len = word.length();

    file.seekg(len, std::ios::cur);

    // NOTE: Should we leave it to user to call SkipAllSpace?
    // Intuitively, I expect this function to skip spaces, but not lines
    SkipAllSpace(true);

    auto offset = file.tellg();
  }

  std::ifstream &GetIfstream() { return file; }

private:
  std::ifstream file;
  const char *currChar;
};

/* Private Functions */
static inline void ParseVertex(std::string line, double &outX, double &outY,
                               double &outZ) {
  std::stringstream iss(line);
  iss >> outX >> outY >> outZ;
}

/*
TODO: Implement utility functions into streamwrapper, such that we can totally
avoid creating strings. Useful utilities:
- Seeking to a specific character
- Getting position of specific character
- Extracting words (deliminated by white space)
- Skipping n chars
*/
static inline void ParseTriple(StreamWrapper &sw, Face face, size_t startPos) {}

} // namespace desobj

#undef SW_EOF
#endif
