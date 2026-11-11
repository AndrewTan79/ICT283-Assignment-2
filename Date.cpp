
#include "Date.h"
#include <iostream>


Date::Date()
{
    m_day = 0;
    m_month = 0;
    m_year = 0;
}

Date::Date(int day, int month, int year)
{
    m_day = day;
    m_month = month;
    m_year = year;
}

int Date::GetDay() const
{
    return m_day;
}

int Date::GetMonth() const
{
    return m_month;
}

int Date::GetYear() const
{
    return m_year;
}

void Date::SetDay(int day)
{
    m_day = day;
}

void Date::SetMonth(int month)
{
    m_month = month;
}

void Date::SetYear(int year)
{
    m_year = year;
}

bool Date::operator<(const Date & other) const
{
    if (m_year != other.m_year)
        return m_year < other.m_year;
    if (m_month != other.m_month)
        return m_month < other.m_month;
    else
        return m_day < other.m_day;
}

bool Date::operator>(const Date & other) const
{
    if (m_year != other.m_year)
        return m_year > other.m_year;
    if (m_month != other.m_month)
        return m_month > other.m_month;
    else
        return m_day > other.m_day;
}

bool Date::operator==(const Date & other) const
{
    return (m_year == other.m_year && m_month == other.m_month && m_day == other.m_day);
}

std::ostream & operator<<(std::ostream & os, const Date & d)
{
    os << d.GetDay() << "/" << d.GetMonth() << "/" << d.GetYear();
    return os;
}
