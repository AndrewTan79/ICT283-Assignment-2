#include "FuncPtr.h"
#include <iostream>
#include "Vector.h"

// This is the real collector that stores records during a tree traversal.
// It is defined here (only once) and declared with "extern" in the header.
Vector<WeatherRecType> collectRec;

// This function is called by the BST every time it visits a node.
// It simply adds the current record to the end of the collector.
void CollectData(WeatherRecType& rec)
{
    collectRec.Insert(collectRec.Size(), rec);   // append the record
}

// Helper function that prints one record (useful for testing).
void PrintData(WeatherRecType& rec)
{
    std::cout << rec.d << " " << rec.speed << " " << rec.temp << " " << rec.sr << std::endl;
}
