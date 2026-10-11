#include "Date.hpp"

#include <ctime>
#include <iomanip>

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
  if (hour > 23 || minute > 59 || 59) return false;

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

    default:
      daysInMonth = 31;
      break;
  }

  return (day >= 1 && day <= daysInMonth);
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
  if (day    != other.minute)  return minute  < other.minute;
  return second < other.second;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
  os << std::setfill('0')
     << std::setw(4) << date.year << "-"
     << std::setw(2) << static_cast<unsigned int>(date.month) << "-"
     << std::setw(2) << static_cast<unsigned int>(date.day) << " "
     << std::setw(2) << static_cast<unsigned int>(date.hour) << ":"
     << std::setw(2) << static_cast<unsigned int>(date.minute) << ":"
     << std::setw(2) << static_cast<unsigned int>(date.second);
  return os;
}

