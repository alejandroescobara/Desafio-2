#pragma once
#include <string>
#include <cstdint>
#include "Usr.hpp"
#include "Chat.hpp"
#include "Msg.hpp"

namespace core{

    extern std::uint64_t totalIterations;//para el conteo de iteraciones
    void countIteration() noexcept;//para el conteo de iteraciones

    extern std::size_t currentMemoryBytes;//para el conteo de memoria
    void registerMemoryAllocation(std::size_t bytes) noexcept;//para el conteo de memoria
    void registerMemoryDeallocation(std::size_t bytes) noexcept;//para el conteo de memoria

    size_t totalMemory();

    void initializerAll(Usr**&  masterArrayUsrs,
            size_t& masterUsrCount,
            size_t& masterUsrCapacity,
            Chat**& masterArrayChats,
            size_t& masterChatCount,
            size_t& masterChatCapacity);

    Usr * usrNameSearch(Usr ** totalUsr, std::string usrName, size_t numUsr);

    Chat * chatSearch(const std::string usrName1, const std::string usrName2, Chat** totalChats, size_t numChats);

    void resizeMasterArrayUsrs(Usr ** &masterArrayUsrs,size_t &masterUsrcapacity, size_t masterUsrCount);

    void resizeMasterArrayChats(Chat ** &masterArraychats,size_t &masterchatscapacity, size_t numChats);

    Chat ** chatIncrust(size_t &chatsCapacity, size_t numChats,Chat **totalChats, Chat *newChat);

}