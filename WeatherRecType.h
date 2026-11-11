#ifndef WEATHERRECTYPE_H_INCLUDED
#define WEATHERRECTYPE_H_INCLUDED

#include "Date.h"

/**
 * @struct WeatherRecType
 * @brief Holds one row of weather data from the input file.
 *
 * This is a simple struct (no member functions) that groups the four
 * values that appear in a data file: date, wind speed, temperature
 * and solar radiation. Wind speed is stored in metres per second,
 * exactly as it appears in the file. Conversion to km/h is done
 * later when averages are calculated.
 */
struct WeatherRecType
{
    Date d;       ///< Date of the observation.
    float speed;  ///< Wind speed (S) in m/s.
    float temp;   ///< Ambient air temperature (T) in degrees Celsius.
    float sr;     ///< Solar radiation (SR).
};

/**
 * @brief Less-than operator for WeatherRecType.
 *
 * Compares two records by their date only. Required so that
 * WeatherRecType objects can be stored in the binary search tree.
 *
 * @param a Left-hand record.
 * @param b Right-hand record.
 * @return true if the date of a is earlier than the date of b.
 */
inline bool operator<(const WeatherRecType& a, const WeatherRecType& b)
{
    return a.d < b.d;
}

/**
 * @brief Greater-than operator for WeatherRecType.
 *
 * Compares two records by their date only.
 *
 * @param a Left-hand record.
 * @param b Right-hand record.
 * @return true if the date of a is later than the date of b.
 */
inline bool operator>(const WeatherRecType& a, const WeatherRecType& b)
{
    return a.d > b.d;
}

/**
 * @brief Equality operator for WeatherRecType.
 *
 * Two records are considered equal when their dates are the same.
 *
 * @param a Left-hand record.
 * @param b Right-hand record.
 * @return true if both records have the same date.
 */
inline bool operator==(const WeatherRecType& a, const WeatherRecType& b)
{
    return a.d == b.d;
}

#endif // WEATHERRECTYPE_H_INCLUDED
