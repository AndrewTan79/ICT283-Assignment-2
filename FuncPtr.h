#ifndef FUNCPTR_H_INCLUDED
#define FUNCPTR_H_INCLUDED

#include "WeatherRecType.h"
#include "Vector.h"

/**
 * @brief Global collector used by the BST traversal callback.
 *
 * The binary search tree calls CollectData for every node during a
 * traversal. Because a function pointer cannot carry extra user data,
 * the collected records are stored in this global Vector.
 * This follows the approach shown in the unit’s testTree.cpp example.
 *
 * The actual object is defined in FuncPtr.cpp.
 */
extern Vector<WeatherRecType> collectRec;

/**
 * @brief Callback function used by the BST in-order traversal.
 *
 * The tree calls this function once for every record. The function
 * appends the record to the global collector so the client code can
 * later examine the results.
 *
 * @param rec The weather record currently being visited by the tree.
 */
void CollectData(WeatherRecType& rec);

/**
 * @brief Prints one weather record to standard output.
 *
 * Useful for debugging. Displays the date, wind speed, temperature
 * and solar radiation of the given record.
 *
 * @param rec The record to print.
 */
void PrintData(WeatherRecType& rec);

#endif //FUNCPTR_H_INCLUDED
