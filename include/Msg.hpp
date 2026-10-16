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

    void setSentDate(const Date& sentDate);
    const Date& getSentDate() const;

    void setText(const std::string& newText);
    const std::string& getText() const;

    void setSender(const Usr* newSender);
    const Usr* getSender() const;

    void setIsRead(bool isRead);
    bool getIsRead() const;

    size_t getMemoryUsage() const;

    static size_t getTotalMemoryUsage();

    Msg& operator=(const Msg& other) = delete;

    friend std::ostream& operator<<(std::ostream& os, const Msg& date);

  private:
    const Usr* sender;

    Date sentDate;

    bool isRead;

    std::string text;

    static size_t totalMemoryAllocated;
};
