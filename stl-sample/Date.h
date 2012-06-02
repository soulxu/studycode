#ifndef DATE_H
#define DATE_H

#include <iosfwd>
#include <iomanip>
#include <iostream>

class Date {
public:
    Date(int year, int month, int day);
    
    int year() const { return m_year; }
    int month() const { return m_month; }
    int day() const { return m_day; }

private:
    int m_year;
    int m_month;
    int m_day;
};

template <class charT, class traits>
std::basic_ostream<charT, traits> &operator<<(std::basic_ostream<charT, traits> &os, const Date &d);

#endif
