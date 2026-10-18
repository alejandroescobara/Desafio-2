#include "core.hpp"
#include <string>
#include <cstddef>//para los conteos
#include <cassert>//para los conteos

#include "Date.hpp"
#include "Album.hpp"
#include "Usr.hpp"
#include "Chat.hpp"
#include "Msg.hpp"

namespace core{

    std::uint64_t totalIterations = 0;

    void countIteration() noexcept {
        ++totalIterations;
    }

    std::size_t currentMemoryBytes = 0;

    void registerMemoryAllocation(std::size_t bytes) noexcept {
        currentMemoryBytes += bytes;
    }

    void registerMemoryDeallocation(std::size_t bytes) noexcept {
        assert(bytes <= currentMemoryBytes);
        currentMemoryBytes -= bytes;
    }

    size_t totalMemory(){
        return currentMemoryBytes + Usr::getTotalMemoryAllocated() + Chat::getTotalMemoryAllocated() +
            Album::getTotalMemoryAllocated() + Photo::getTotalMemoryAllocated()+
            Msg::getTotalMemoryUsage() + Date::getMemoryUsage();
    }

    void initializerAll(Usr**&  masterArrayUsrs,
            size_t& masterUsrCount,
            size_t& masterUsrCapacity,
            Chat**& masterArrayChats,
            size_t& masterChatCount,
            size_t& masterChatCapacity){
        masterUsrCount = 0;
        masterChatCount = 0;
        masterUsrCapacity = 32;
        masterChatCapacity = 32;
        masterArrayChats = new Chat * [32]();
        masterArrayUsrs = new Usr * [32]();
    }

    Usr * usrNameSearch(Usr ** totalUsr, std::string usrName, size_t numUsr){
        size_t init = 0;
        size_t end = numUsr - 1;
        size_t mid = 0;
        while(init <= end){
            mid = init + ((end - init)/ 2);
            if((totalUsr[mid])->getUsrname() == usrName){
                return totalUsr[mid];
            }
            if((totalUsr[mid])->getUsrname() < usrName){
                init = mid + 1;
            }
            else{
                if (mid == 0){return nullptr;}
                end = mid - 1;
            }
            totalIterations++;
        }
        return nullptr;
    }

    Chat * chatSearch(const std::string usrName1, const std::string usrName2, Chat** totalChats, size_t numChats){
        std::string names = ((usrName1 > usrName2) ? (usrName1+'#'+usrName2) : (usrName2+'#'+usrName1));

        size_t init = 0;
        size_t end = numChats - 1;
        size_t mid = 0;
        while(init <= end){
            mid = init + ((end - init)/ 2);
            const std::string midNames = totalChats[mid]->getUsrA()->getUsrname() + '#' + totalChats[mid]->getUsrB()->getUsrname();
            if(midNames == names){ // nombreA#nombreB == usrname1#usrname2
                return totalChats[mid];
            }
            if(midNames < names){
                init = mid + 1;
            }
            else{
                if (mid == 0) return nullptr;
                end = mid - 1;
            }
            totalIterations++;
        }
        return nullptr;
    }

    void resizeMasterArrayUsrs(Usr ** &masterArrayUsrs,size_t &masterUsrcapacity, size_t masterUsrCount){
        size_t newCapacity = masterUsrcapacity * 2;

        Usr** auxUsers = nullptr;

        try {
            auxUsers = new Usr*[newCapacity];
        } catch (const std::bad_alloc&) {
            delete[] auxUsers;
            throw;
        }

        for (size_t i = 0; i < masterUsrCount; ++i)           auxUsers[i] = masterArrayUsrs[i];
        totalIterations+=masterUsrCount;
        for (size_t i = masterUsrCount; i < newCapacity; ++i) auxUsers[i] = nullptr;
        totalIterations+=(newCapacity-masterUsrCount);

        delete[] masterArrayUsrs;
        masterArrayUsrs = auxUsers;

        masterUsrcapacity = newCapacity;

    }

    void resizeMasterArrayChats(Chat ** &masterArraychats,size_t &masterchatscapacity, size_t numChats){

        size_t newCapacity = masterchatscapacity * 2;

        Chat** auxChats = nullptr;

        try {
            auxChats = new Chat*[newCapacity];
        } catch (const std::bad_alloc&) {
            delete[] auxChats;
            throw;
        }

        for (size_t i = 0; i < numChats; ++i)           auxChats[i] = masterArraychats[i];
        for (size_t i = numChats; i < newCapacity; ++i) auxChats[i] = nullptr;

        delete[] masterArraychats;
        masterArraychats = auxChats;

        masterchatscapacity = newCapacity;
    }

    Chat ** chatIncrust(size_t &chatsCapacity, size_t numChats,
                       Chat **totalChats, Chat *newChat){

        const std::string newNames =
            newChat->getUsrA()->getUsrname() + '#' +
            newChat->getUsrB()->getUsrname();

        // Se usa el mismo orden de nombres que en chatSearch

        if(numChats == chatsCapacity){
            core::resizeMasterArrayChats(totalChats,chatsCapacity,numChats);
        }

        size_t position = numChats;

        while(position > 0){
            Chat * currentChat = totalChats[position - 1];

            const std::string currentNames =
                currentChat->getUsrA()->getUsrname() + '#' +
                currentChat->getUsrB()->getUsrname();

            if(currentNames <= newNames){
                break;
            }

            totalChats[position] = totalChats[position - 1];
            position--;
            totalIterations++;
        }

        totalChats[position] = newChat;

        return totalChats;
    }


}




