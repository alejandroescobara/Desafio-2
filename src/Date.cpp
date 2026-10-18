#include "Date.hpp"

#include <ctime>

size_t Date::activeInstances = 0;

//#### CONSTRUCTORS ||>

Date::Date(unsigned short year,
      unsigned char  month,
      unsigned char  day,
      unsigned char  hour,
      unsigned char  minute,
      unsigned char  second)
    : year(year),
      month(month),
      day(day),
      hour(hour),
      minute(minute),
      second(second) {
//---------
  if (!isValidDate(year, month, day, hour, minute, second)) {
    throw std::invalid_argument("ERROR: FAILED TO CREATE OBJECT (INVALID DATE)");
  }
  ++activeInstances;
}

static unsigned int parseNumber(const std::string& str, unsigned int start, unsigned int length) {
  unsigned int number = 0;

  for (unsigned int i = start; i < start + length; ++i) {
    number = number * 10 + static_cast<unsigned int>(str[i] - '0');
  }

  return number;
}

Date::Date(const std::string& str, bool hasTime)
    : year(static_cast<unsigned short>(parseNumber(str, 0, 4))),
      month(static_cast<unsigned char>(parseNumber(str, 4, 2))),
      day(static_cast<unsigned char>(parseNumber(str, 6, 2))),
      hour(static_cast<unsigned char>(hasTime ? parseNumber(str, 8, 2) : 0)),
      minute(static_cast<unsigned char>(hasTime ? parseNumber(str, 10, 2) : 0)),
      second(static_cast<unsigned char>(hasTime ? parseNumber(str, 12, 2) : 0)) {

  if (!isValidDate(year, month, day, hour, minute, second)) {
    throw std::invalid_argument("ERROR: FAILED TO CREATE OBJECT (INVALID DATE)");
  }

  ++activeInstances;
}

//#### OTHERS ||>

bool Date::isLeapYear(unsigned short year) {
  return (year % 4 == 0 && year % 100 != 0)|| (year % 400 == 0);
}

bool Date::isValidDate(unsigned short year,
                 unsigned char month,
                 unsigned char day,
                 unsigned char hour,
                 unsigned char minute,
                 unsigned char second) {
//---------
  if (hour > 23 || minute > 59 || second > 59) return false;

  if (month < 1 || month > 12) return false;

  unsigned char daysInMonth;

  switch (month) {

    case 2:
      daysInMonth = isLeapYear(year)? 29 : 28;
      break;

    case 4:
    case 6:
    case 9:
    case 11:
      daysInMonth = 30;
      break;
    default:
      daysInMonth = 31;
      break;
  }

  return (day >= 1 && day <= daysInMonth);
}

static void appendNumber(std::string& str, unsigned int number, unsigned int width) {
  
  if (number < 10 && width >= 2)   str += '0';
  if (number < 100 && width >= 3)  str += '0';
  if (number < 1000 && width >= 4) str += '0';
  
  str += std::to_string(number);
}

std::string Date::toString(bool hasTime) const {
  std::string str;

  appendNumber(str, year, 4);
  appendNumber(str, static_cast<unsigned int>(month), 2);
  appendNumber(str, static_cast<unsigned int>(day), 2);

  if (hasTime) {
    appendNumber(str, static_cast<unsigned int>(hour), 2);
    appendNumber(str, static_cast<unsigned int>(minute), 2);
    appendNumber(str, static_cast<unsigned int>(second), 2);
  }
  return str;
}

Date Date::now() {
  std::time_t time = std::time(nullptr);
  std::tm*  localTm = std::localtime(&time);

  unsigned short year   = static_cast<unsigned short>(localTm->tm_year + 1900);
  unsigned char  month  = static_cast<unsigned char>(localTm->tm_mon + 1);
  unsigned char  day    = static_cast<unsigned char>(localTm->tm_mday);
  unsigned char  hour   = static_cast<unsigned char>(localTm->tm_hour);
  unsigned char  minute = static_cast<unsigned char>(localTm->tm_min);
  unsigned char  second = static_cast<unsigned char>(localTm->tm_sec);

  return Date(year, month, day, hour, minute, second);
}

size_t Date::getMemoryUsage() {
  return activeInstances * sizeof(Date);
}

//#### OVERLOADED OPERATORS ||>

Date& Date::operator=(const Date& other) {
  if (this != &other) {
    year   = other.year;
    month  = other.month;
    day    = other.day;
    hour   = other.hour;
    minute = other.minute;
    second = other.second;
  }

  return *this;
}

bool Date::operator==(const Date& other) const {
  return (year   == other.year   &&
          month  == other.month  &&
          day    == other.day    &&
          hour   == other.hour   &&
          minute == other.minute &&
          second == other.second);
}


bool Date::operator<(const Date& other) const {
  if (year   != other.year)    return year    < other.year;
  if (month  != other.month)   return month   < other.month;
  if (day    != other.day)     return day     < other.day;
  if (hour   != other.hour)    return hour    < other.hour;
  if (minute != other.minute)  return minute  < other.minute;
  return second < other.second;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
  std::string str;

  appendNumber(str, date.year, 4);
  os << str << "-";
  str.clear();

  appendNumber(str, static_cast<unsigned int>(date.month), 2);
  os << str << "-";
  str.clear();

  appendNumber(str, static_cast<unsigned int>(date.day), 2);
  os << str << " ";
  str.clear();

  appendNumber(str, static_cast<unsigned int>(date.hour), 2);
  os << str << ":";
  str.clear();

  appendNumber(str, static_cast<unsigned int>(date.minute), 2);
  os << str << ":";
  str.clear();

  appendNumber(str, static_cast<unsigned int>(date.second), 2);
  os << str;
  return os;
}
