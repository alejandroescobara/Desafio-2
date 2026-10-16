#pragma once

#include "Chat.hpp"

class Usr;

namespace dataManager {

  bool writeUsers(Usr** masterArrayUsrs, const size_t masterUsrCount, const char*  filePath);

  bool loadSystemData(Usr**&  masterArrayUsrs,
                      size_t& masterUsrCount,
                      size_t& masterUsrCapacity,
                      Chat**& masterArrayChats,
                      size_t& masterChatCount,
                      size_t& masterChatCapacity);

  bool saveSystemData(Usr**  masterArrayUsrs, 
                      size_t masterUsrCount,
                      Chat** masterArrayChats,
                      size_t masterChatCount);

  void freeSystemData(Usr**&  masterArrayUsrs,
                      size_t& masterUsrCount,
                      Chat**& masterArrayChats,
                      size_t& masterChatCount);
}
