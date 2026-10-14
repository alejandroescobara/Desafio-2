#pragma once

#include <cstddef>

#include "Msg.hpp"

class Usr;

class Chat {
  public:

    Chat() = delete;

    Chat(const Usr* usrA, const Usr* usrB, size_t initialMsgCapacity = 10);

    Chat(const Chat& other) = delete;

    ~Chat();
  
    const Msg* const* getMsgs() const;
    size_t getMsgCount() const;

    const Usr* getUsrA() const;
    const Usr* getUsrB() const;
    const Usr* getOtherUsr(const Usr* currentUsr) const;

    bool getIsRead() const;

    bool printAndMarkMsgs(const Usr* currentUsr, const Date& startDate = Date(), const Date& endDate = Date::now());
    
    bool consumeUnread(const Usr* currentUsr);

    static size_t getTotalMemoryAllocated();

    Chat& operator=(const Chat& other) = delete;

    Chat& operator+=(Msg* newMsg);

  private:
    const Usr* usrA;
    const Usr* usrB;

    Msg** msgs;
    size_t msgCount;
    size_t msgCapacity;

    static size_t totalMemoryAllocated;

    void resizeMsgs();
};
