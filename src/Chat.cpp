#include "Chat.hpp"

#include <new>
#include <stdexcept>
#include "core.hpp"
#include "Usr.hpp"

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

  try {
    msgs = new Msg*[initialMsgCapacity]; 
  } catch (const std::bad_alloc&) {
    delete[] msgs;
    throw;
  }

  for (size_t i = 0; i < msgCapacity; ++i){ msgs[i] = nullptr;core::countIteration();}

  totalMemoryAllocated += sizeof(Chat)+(msgCapacity * sizeof(Msg*));
}

Chat::~Chat() {
  for (size_t i = 0; i < msgCount; ++i) {
    core::countIteration();
    delete msgs[i];
    msgs[i] = nullptr;
  }
  delete[] msgs;
  msgs = nullptr;

  totalMemoryAllocated -= (sizeof(Chat)+(msgCapacity * sizeof(Msg*)));
}

void Chat::resizeMsgs() {
  size_t newCapacity = msgCapacity * 2;
 
  Msg** auxMsgs = nullptr; 
  try {
    auxMsgs = new Msg*[newCapacity]; 
  } catch (const std::bad_alloc&) {
    delete[] auxMsgs;
    throw;
  }

  for (size_t i = 0; i < msgCount ; ++i ){         auxMsgs[i] = msgs[i];core::countIteration();}
  for (size_t i = msgCount; i < newCapacity; ++i){ auxMsgs[i] = nullptr;core::countIteration();}
  
  delete[] msgs;
  msgs = auxMsgs;

  totalMemoryAllocated += ((newCapacity - msgCapacity) * sizeof(Msg*));
  msgCapacity = newCapacity;
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
    core::countIteration();
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
    core::countIteration();
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
    core::countIteration();
    if ((msgs[i]->getSender() != currentUsr) && (msgs[i]->getIsRead() == false)) {
      std::cout << *(msgs[i]) << "\n";
      msgs[i]->setIsRead(true);
      hasUnread = true;
    }
  }
  return hasUnread;
}

Chat& Chat::operator+=(Msg* newMsg) {
  if (msgCount >= msgCapacity) {
    resizeMsgs();
  }
  msgs[msgCount++] = newMsg;
  return *this;
}
