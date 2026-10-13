#include "Msg.hpp"
#include "validators.hpp"

size_t Msg::totalMemoryAllocated = 0;

Msg::Msg(const Usr* sender,
         const Date& sentDate,
         const std::string& text)
   :sender(sender),
    sentDate(sentDate),
    isRead(false),
    text(text) {
//---------

  if(!validators::isValidMsgText(text)) {
    throw std::invalid_argument("ERROR: the message must be between 1-512 Characters long");
  }
  
  totalMemoryAllocated += getMemoryUsage();
}

Msg::~Msg() {
  totalMemoryAllocated -= getMemoryUsage();
}

void Msg::setSentDate(const Date& newSentDate) {
  sentDate = newSentDate; 
}

const Date& Msg::getSentDate() const {
  return sentDate;
}

void Msg::setText(const std::string& newText) { 
  if(!validators::isValidMsgText(newText)) {
    throw std::invalid_argument("ERROR: the message must be betweeen 1-512 Characters long");
  }

  size_t oldUsage = getMemoryUsage();
  
  text = newText;
  
  totalMemoryAllocated = (totalMemoryAllocated - oldUsage) + getMemoryUsage();
}

const std::string& Msg::getText() const {
  return text;
}

void Msg::setSender(const Usr* newSender) {
  sender = newSender;
}

const Usr* Msg::getSender() const {
  return sender;
}

void Msg::setIsRead(bool newIsRead) {
  isRead = newIsRead;
}

bool Msg::getIsRead() const {
  return isRead;
}

size_t Msg::getMemoryUsage() const {
  return sizeof(*this) + text.capacity();
}

size_t Msg::getTotalMemoryUsage() {
  return totalMemoryAllocated;
}

std::ostream& operator<<(std::ostream& os, const Msg& targetMsg) {
    
  std::string senderName = targetMsg.sender->getUsrname();
    
  os << "@" << senderName << "\n";

  os << targetMsg.sentDate << " " << (targetMsg.isRead ? "read" : "unread") << "\n"
     << targetMsg.text;

  return os;
}


