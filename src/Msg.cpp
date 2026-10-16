#include "Msg.hpp"

#include "Usr.hpp"

size_t Msg::totalMemoryAllocated = 0;

Msg::Msg(const Usr* sender,
         const Date& sentDate,
         const std::string& text,
         bool isRead)
   :sender(sender),
    sentDate(sentDate),
    isRead(isRead),
    text(text) {
//---------

  totalMemoryAllocated += getMemoryUsage();
}

Msg::~Msg() {
  totalMemoryAllocated -= getMemoryUsage();
}

void Msg::setIsRead(bool newIsRead) {
  isRead = newIsRead;
}
size_t Msg::getMemoryUsage() const {
  return sizeof(*this) + text.capacity();
}

std::ostream& operator<<(std::ostream& os, const Msg& targetMsg) {
    
  std::string senderName = targetMsg.sender->getUsrname();
    
  os << "@" << senderName << "\n";

  os << targetMsg.sentDate << " " << (targetMsg.isRead ? "read" : "unread") << "\n"
     << targetMsg.text;

  return os;
}


