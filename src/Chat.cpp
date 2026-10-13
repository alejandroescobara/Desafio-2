#include "Chat.hpp"

#include <new>
#include <stdexcept>

#include "validators.hpp"

size_t Chat::totalMemoryAllocated = 0;

Chat::Chat(const Usr* usr1, const Usr* usr2, size_t initialMsgCapacity)
    :usrA(nullptr),
     usrB(nullptr),
     msgs(nullptr),
     msgCount(0),
     msgCapacity(initialMsgCapacity) {

  if (usr1 == nullptr || usr2 == nullptr) {
    throw std::invalid_argument("ERROR: Null chat participant");
  }

  if (usr1 == usr2) {
    throw std::invalid_argument("ERROR: User cannot chat with themselves");
  }

  if (initialMsgCapacity == 0) {
    throw std::invalid_argument("ERROR: Invalid initialMsgCapacity.");
  }

  if (usr1->getUsrname() > usr2->getUsrname()) {
    usrA = usr1;
    usrB = usr2;
  } 
  else {
    usrA = usr2;
    usrB = usr1;
  }

  msgs = new (std::nothrow) Msg*[initialMsgCapacity];
  if (!validators::isValidMemoryReservation(msgs)) {
    throw std::bad_alloc();
  }

  for (size_t i = 0; i < msgCapacity; ++i) msgs[i] = nullptr;

  totalMemoryAllocated += (msgCapacity * sizeof(Msg*));
}

Chat::~Chat() {
  for (size_t i = 0; i < msgCapacity; ++i) {
    delete msgs[i];
    msgs[i] = nullptr;
  }
  delete[] msgs;
  msgs = nullptr;

  totalMemoryAllocated -= (msgCapacity * sizeof(Msg*));
}

const Msg* const* Chat::getMsgs() const {
  return msgs;
}

size_t Chat::getMsgCount() const {
  return msgCount;
}

//
void Chat::resizeMsgs() {
  size_t oldCapacity = msgCapacity;
  msgCapacity *= 2;
  Msg** auxMsgs = new (std::nothrow) Msg*[msgCapacity];
  if (!validators::isValidMemoryReservation(auxMsgs)) {
    throw std::bad_alloc();
  }

  for (size_t i = 0; i < msgCount ; ++i ) {
    auxMsgs[i] = msgs[i];
  }
  for (size_t i = msgCount; i < msgCapacity; ++i) {
    auxMsgs[i] = nullptr;
  }
  delete[] msgs;
  msgs = auxMsgs;

  totalMemoryAllocated += ((msgCapacity - oldCapacity) * sizeof(Msg*));
}

const Usr* Chat::getUsrA() const {
  return usrA;
}

const Usr* Chat::getUsrB() const {
  return usrB;
}

const Usr* Chat::getOtherUsr(const Usr* currentUsr) const {
  return (currentUsr == getUsrA())? usrB : usrA;
}

bool Chat::printAndMarkMsgs(const Usr* currentUsr, const Date& startDate, const Date& endDate) {

  if (msgCount == 0 || startDate > endDate) {
    return false;
  }

  size_t low = 0;
  size_t high = msgCount;

  while (low < high) {
    size_t mid = low + (high - low) / 2;

    if (msgs[mid]->getSentDate() >= startDate) {
      high = mid;
    }
    else {
      low = mid + 1;
    }
  }

  if (low == msgCount || msgs[low]->getSentDate() > endDate) {
    return false;
  }

  size_t i = low;
  bool hasMsgs = false;

  while (i < msgCount && msgs[i]->getSentDate() <= endDate) {
    if (msgs[i]->getSender() != currentUsr) {
      std::cout << *(msgs[i]) << "\n";
      msgs[i]->setIsRead(true);
      hasMsgs = true;
    }
    ++i;
  }
  return hasMsgs;
}

bool Chat::consumeUnread(const Usr* currentUsr) {
  
  if (msgCount == 0) return false;

  bool hasUnread = false;

  for (size_t i = 0; i < msgCount; ++i) {
    if ((msgs[i]->getSender() != currentUsr) && (msgs[i]->getIsRead() == false)) {
      std::cout << *(msgs[i]) << "\n";
      msgs[i]->setIsRead(true);
      hasUnread = true;
    }
  }
  return hasUnread;
}

size_t Chat::getTotalMemoryAllocated() {
  return totalMemoryAllocated;
}

Chat& Chat::operator+=(Msg* newMsg) {
  if (msgCount >= msgCapacity) {
    resizeMsgs();
  }
  msgs[msgCount++] = newMsg;
  return *this;
}
