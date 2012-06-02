#include "Date.h"

#include <iostream>
#include <iomanip>

using namespace std;

Date::Date(int year, int month, int day) : m_year(year), m_month(month), m_day(day) {

}

template <class charT, class traits>
std::basic_ostream<charT, traits> &operator<<(std::basic_ostream<charT, traits> &os, const Date &d) {
    char fillc = os.fill(os.widen('0'));
    os << std::setw(4) << d.year() << os.widen('-')
        << std::setw(2) << d.month() << os.widen('-')
        << std::setw(2) << d.day() << std::setfill(fillc);
}
