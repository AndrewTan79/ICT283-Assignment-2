#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>


/**
 * @class Date
 * @brief Holds a date as a day, a month, and a year.
 *
 * This class only keeps the three numbers and gives them back.
 * It does not read the file, and it does not check if the date is real.
 */
class Date
{
public:
    /**
     * @brief Makes an empty date. Day, month, and year start at 0.
     */
    Date();

    /**
     * @brief Makes a date from the three numbers you pass in.
     * @param day The day.
     * @param month The month.
     * @param year The year.
     */
    Date(int day, int month, int year);

    /**
     * @brief Gives back the day.
     * @return The day stored in this date.
     */
    int GetDay() const;

    /**
     * @brief Gives back the month.
     * @return The month stored in this date.
     */
    int GetMonth() const;

    /**
     * @brief Gives back the year.
     * @return The year stored in this date.
     */
    int GetYear() const;

    /**
     * @brief Changes the day.
     * @param day The new day.
     */
    void SetDay(int day);

    /**
     * @brief Changes the month.
     * @param month The new month.
     */
    void SetMonth(int month);

    /**
     * @brief Changes the year.
     * @param year The new year.
     */
    void SetYear(int year);

    //comparison operator
    bool operator<(const Date & other) const;
    bool operator>(const Date & other) const;
    bool operator==(const Date & other) const;

private:
    int m_day;    ///< The day.
    int m_month;  ///< The month.
    int m_year;   ///< The year.
};

std::ostream & operator<<(std::ostream & os, const Date & d);

#endif // DATE_H_INCLUDED
