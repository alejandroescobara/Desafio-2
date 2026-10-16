#pragma once

#include <string>

namespace validators {

  bool isValidMsgText(const std::string& text);
  
  bool fileExists(const char* filePath);
  //bool isValidEmail();

  //bool isValidUsrname();

  //bool isValidDob();
}
