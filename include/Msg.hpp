#pragma once

#include <string>
#include <iostream>
#include <cstddef>

#include "Date.hpp"

class Usr;

class Msg {
  public:
    Msg() = delete;

    Msg(const Usr* sender, const Date& sentDate, const std::string& text, bool isRead = false);

    Msg(const Msg& other) = delete;

    ~Msg();

    const Date& getSentDate() const {
      return sentDate;
    }

    const std::string& getText() const {
      return text;
    }

    const Usr* getSender() const {
      return sender;
    }

    void setIsRead(bool isRead);

    bool getIsRead() const {
      return isRead;
    }

    size_t getMemoryUsage() const;

    static size_t getTotalMemoryUsage() {
      return totalMemoryAllocated;
    }

    Msg& operator=(const Msg& other) = delete;

    friend std::ostream& operator<<(std::ostream& os, const Msg& date);

  private:
    const Usr* sender;

    Date sentDate;

    bool isRead;

    std::string text;

    static size_t totalMemoryAllocated;
};
