#include "validators.hpp"

#include <fstream>

namespace validators {

  bool isValidMsgText(const std::string& text) {
    return !text.empty() && text.length() <= 512;
  }

  bool fileExists(const char* filePath) {
    std::ifstream file(filePath);
    return file.is_open();
  }
}
