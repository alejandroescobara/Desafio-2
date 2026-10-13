#include "validators.hpp"

namespace validators {

  bool isValidMsgText(const std::string& text) {
    return !text.empty() && text.length() <= 512;
  }

}
