#include "ReadFile.h"
#include "Date.h"
#include <string>
#include <sstream>
#include <map>
#include "Vector.h"
#include <fstream>

// Opens the list of data files and loads every file that is listed
void openFile(const std::string & sourcefile, Bst<WeatherRecType> & tree, std::map<int, Vector<WeatherRecType>> & monthMap)
{
    std::ifstream firstFile(sourcefile);        // open data_source.txt

    if (!firstFile)                             // check it opened
    {
        std::cout << "Fail to open source file!";
        return;
    }

    std::string datafileName;
    while(std::getline(firstFile, datafileName))    // read one filename per line
    {
        if (datafileName.empty())               // skip blank lines
            continue;

        std::ifstream inFile("data/"+datafileName); // open the actual data file

        if (!inFile)
        {
            std::cout << "Fail to open data File!";
            continue;                           // skip this file and try the next one
        }

        readFile(inFile, tree, monthMap);       // read all the records from this file

        inFile.close();
    }
    firstFile.close();
}

// Reads one weather CSV file and stores every valid record
void readFile(std::ifstream& inFile, Bst<WeatherRecType> & tree, std::map<int, Vector<WeatherRecType>> & monthMap)
{
    std::string header;
    std::getline(inFile, header);               // read the first line (column names)

    int wastCol = -1;                           // remember which column is which
    int speedCol = -1;
    int tempCol = -1;
    int srCol = -1;
    int col = 0;

    std::stringstream headerStream(header);
    std::string name;
    while(std::getline(headerStream, name, ','))    // split the header by commas
    {
        if (name == "WAST")
            wastCol = col;
        if (name == "S")
            speedCol = col;
        if (name == "T")
            tempCol = col;
        if (name == "SR")
            srCol = col;
        col++;
    }

    std::string line;
    while(std::getline(inFile, line))           // read every data line
    {
        std::stringstream lineStream(line);
        std::string field;
        int col = 0;
        bool gotSpeed = false;                  // flags to check we found all values
        bool gotTemp = false;
        bool gotSR = false;
        WeatherRecType rec;                     // one record we are building

        while(std::getline(lineStream, field, ',')) // split the line by commas
        {
            if (col == wastCol)                 // this column is the date
            {
                std::string dd;
                std::stringstream wastStream(field);
                wastStream >> dd;

                int day, month, year;
                char slash;
                std::stringstream(dd) >> day >> slash >> month >> slash >> year;
                rec.d = Date(day, month, year); // store the date
            }
            if (col == speedCol)
            {
                std::stringstream speedstream(field);
                gotSpeed = (bool)(speedstream >> rec.speed);  // try to read the speed
            }
            if (col == tempCol)
            {
                std::stringstream tempstream(field);
                gotTemp = (bool)(tempstream >> rec.temp);
            }
            if (col == srCol)
            {
                std::stringstream srstream(field);
                gotSR = (bool)(srstream >> rec.sr);
            }
            col++;
        }
        if(gotSpeed && gotTemp && gotSR)        // only keep the record if all three numbers were read
        {
            tree.Insert(rec);                   // put it in the BST
            int monthKey = rec.d.GetMonth();
            monthMap[monthKey].Insert(monthMap[monthKey].Size(), rec);  // also put it in the map
        }
    }
}
