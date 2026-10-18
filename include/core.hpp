#pragma once
#include <string>

#include "Usr.hpp"
#include "Chat.hpp"
#include "Msg.hpp"

namespace core{

    Usr * usrNameSearch(Usr ** totalUsr, std::string usrName, size_t numUsr);

    Chat * chatSearch(const std::string usrName1, const std::string usrName2, Chat** totalChats, size_t numChats);

    void resizeMasterArrayUsrs(Usr ** &masterArrayUsrs,size_t &masterUsrcapacity, size_t masterUsrCount);

    void resizeMasterArrayChats(Chat ** &masterArraychats,size_t &masterchatscapacity, size_t numChats);

    Chat ** chatIncrust(size_t &chatsCapacity, size_t numChats,Chat **totalChats, Chat *newChat);

}