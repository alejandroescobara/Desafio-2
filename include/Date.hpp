#pragma once

#include <string>
#include <iostream>
#include <cstddef>

class Date {
  
  public:

    //#### CONSTRUCTORS ||>
    
    inline Date() : Date(1970, 1, 1, 0, 0, 0) {}

    Date(unsigned short year,
         unsigned char  month,
         unsigned char  day,
         unsigned char  hour = 0,
         unsigned char  minute=0,
         unsigned char  second=0);

    Date(const std::string& str, bool hasTime);

    //#### DESTRUCTOR ||>

    inline ~Date() {
      if(activeInstances > 0) --activeInstances;
    }

    //#### GETTERS ||>

    inline unsigned short getYear() const {
      return year;
    }

    inline unsigned char getMonth() const {
      return month;
    }

    inline unsigned char getDay() const {
      return day;
    }

    inline unsigned char getHour() const {
      return hour;
    }

    inline unsigned char getMinute() const {
      return minute;
    }

    inline unsigned char getSecond() const {
      return second;
    }

    //#### OTHERS ||>

    std::string toString() const;

    static bool isLeapYear(unsigned short year);
    
    static bool isValidDate(unsigned short year,
                 unsigned char month,
                 unsigned char day,
                 unsigned char hour   =0,
                 unsigned char minute =0,
                 unsigned char second =0);

    std::string toString(bool hasTime) const;

    static size_t getMemoryUsage();

    static Date now();

    //#### OPERATORS ||>

    Date& operator=(const Date& other);

    bool operator==(const Date& other) const;
    bool operator<(const Date& other) const;

    inline bool operator!=(const Date& other) const {
      return !(*this == other);
    }

    inline bool operator>=(const Date& other) const {
      return !(*this < other);
    }

    inline bool operator>(const Date& other) const {
      return (other < *this);
    }

    inline bool operator<=(const Date& other) const {
      return !(*this > other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& date);

  private:
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;

    static size_t activeInstances;
};
