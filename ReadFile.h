#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED

#include "Bst.h"
#include "Date.h"
#include <fstream>
#include <map>
#include "Vector.h"
#include "WeatherRecType.h"

/**
 * @brief Opens the source file that lists data file names and loads every file.
 *
 * The source file (normally data/data_source.txt) contains one data-file name
 * per line. Each listed file is opened from the data/ folder and passed to
 * readFile. Empty lines are skipped. If a data file cannot be opened the
 * function continues with the next file.
 *
 * @param filename  Name of the source file that lists the data files.
 * @param tree      Binary search tree that will receive every valid record.
 * @param monthMap  Map that groups records by month number.
 */
void openFile(const std::string & filename, Bst<WeatherRecType> & tree, std::map<int, Vector<WeatherRecType>> & monthMap);

/**
 * @brief Reads one weather data file and stores the records.
 *
 * The first line of the file is treated as a header. The function looks for
 * the columns WAST, S, T and SR. Each subsequent line that contains valid
 * values for all four fields is turned into a WeatherRecType and inserted
 * into both the BST and the month map.
 *
 * @param inFile    Already-opened input file stream.
 * @param tree      Binary search tree that receives the records.
 * @param monthMap  Map that receives the records, keyed by month.
 */
void readFile(std::ifstream& inFile, Bst<WeatherRecType> & tree, std::map<int, Vector<WeatherRecType>> & monthMap);

#endif // READFILE_H_INCLUDED
