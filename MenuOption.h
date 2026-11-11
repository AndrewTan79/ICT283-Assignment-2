#ifndef MENUOPTION_H_INCLUDED
#define MENUOPTION_H_INCLUDED

#include "Vector.h"
#include "Bst.h"
#include <map>
#include <string>
#include "WeatherRecType.h"

/**
 * @brief Map that groups weather records by month number.
 *
 * Key   = month (1–12)
 * Value = Vector of all WeatherRecType records that belong to that month.
 */
typedef std::map<int, Vector<WeatherRecType>> monthMap;

/**
 * @brief Iterator type for monthMap.
 */
typedef monthMap::iterator monthMapItr;

/**
 * @brief Const iterator type for monthMap.
 */
typedef monthMap::const_iterator cmonthMapItr;

/**
 * @brief Returns the English name of a month.
 *
 * @param month Month number (1 = January … 12 = December).
 * @return The name of the month, or "Invalid month" if the number is out of range.
 */
std::string monthName(int month);

/**
 * @brief Menu option 1 – average wind speed and sample standard deviation.
 *
 * Asks the user for a month and a year, then calculates the average
 * wind speed (in km/h) and the sample standard deviation for that
 * month and year. Results are printed to the screen.
 *
 * @param monthMap Map that holds records grouped by month.
 */
void menuOption1(std::map<int, Vector<WeatherRecType>> & monthMap);

/**
 * @brief Menu option 2 – average temperature and standard deviation for each month of a year.
 *
 * Asks the user for a year, then uses the BST in-order traversal to
 * collect records. For every month it prints the average ambient
 * temperature and the sample standard deviation (or “No Data”).
 *
 * @param WeatherTree Binary search tree containing all weather records.
 */
void menuOption2(Bst<WeatherRecType> & WeatherTree);

/**
 * @brief Menu option 3 – sample Pearson Correlation Coefficient for one month.
 *
 * Asks the user for a month number. Calculates the sPCC between
 * wind speed & temperature, wind speed & solar radiation, and
 * temperature & solar radiation for that month across all years.
 * Results are printed to the screen.
 *
 * @param monthMap Map that holds records grouped by month.
 */
void menuOption3(std::map<int, Vector<WeatherRecType>> & monthMap);

/**
 * @brief Menu option 4 – monthly averages, standard deviation, MAD and total solar radiation.
 *
 * Asks the user for a year. Uses the BST in-order traversal to collect
 * records, then writes a CSV file (WindTempSolar.csv) containing, for
 * each month that has data:
 * average wind speed (stdev, mad), average temperature (stdev, mad),
 * and total solar radiation.
 *
 * @param WeatherTree Binary search tree containing all weather records.
 */
void menuOption4(Bst<WeatherRecType> & WeatherTree);

#endif //MENUOPTION_H_INCLUDED
