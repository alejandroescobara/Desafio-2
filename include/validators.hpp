#pragma once

#include <string>

namespace validators {

  bool isValidMsgText(const std::string& text);
  
  template <typename T>
  bool isValidMemoryReservation(T ptr) {  
    return (ptr == nullptr)? true : false;
  }

  //bool isValidEmail();

  //bool isValidUsrname();

  //bool isValidDob();
}
