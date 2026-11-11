#include "MenuOption.h"
#include "Vector.h"
#include <map>
#include "Bst.h"
#include "FuncPtr.h"
#include <fstream>
#include "Stat.h"
#include <iomanip>

// Turns a month number into its English name
std::string monthName(int month)
{
    if (month == 1)
        return "January";
    if (month == 2)
        return "February";
    if (month == 3)
        return "March";
    if (month == 4)
        return "April";
    if (month == 5)
        return "May";
    if (month == 6)
        return "June";
    if (month == 7)
        return "July";
    if (month == 8)
        return "August";
    if (month == 9)
        return "September";
    if (month == 10)
        return "October";
    if (month == 11)
        return "November";
    if (month == 12)
        return "December";
    return "Invalid month";
}

// Menu option 1: average wind speed + stdev for one month and year
void menuOption1 (std::map<int, Vector<WeatherRecType>> & monthMap)
{
    int month = 0;                          // store the month the user types
    int yr = 0;                             // store the year the user types

    std::cout << "\nWhich month do you want to search?\n";
    std::cin >> month;                      // read month from keyboard
    std::cout << "\nWhich year do you want to search?\n";
    std::cin >> yr;                         // read year from keyboard

    monthMapItr it = monthMap.find(month);  // look for this month in the map

    if (it == monthMap.end())               // month was not found
    {
        std::cout << "No Data for that month. \n";
        return;                             // stop this function
    }

    Vector<float> windspeed;                // will hold the wind speeds we need

    const Vector<WeatherRecType>& records = it->second;  // all records for this month
    for (int i=0; i<records.Size(); i++)    // look at every record
    {
        const WeatherRecType& rec = records[i];
        if (rec.d.GetYear() == yr)          // keep only records from the chosen year
        {
            windspeed.Insert(windspeed.Size(), rec.speed * 3.6f);  // save the speed
        }
    }
    if (windspeed.Size() == 0)              // nothing matched the year
    {
        std::cout << "No data for that month and year.\n";
        return;
    }

    float m = mean(windspeed, windspeed.Size());          // calculate average
    float ss = sqSum(windspeed, windspeed.Size(), m);     // sum of squared differences
    float sv = standardDV(ss,windspeed.Size());           // sample standard deviation
    std::cout << std::fixed << std::setprecision(1);      // show 1 decimal place
    std::cout << monthName(month) << " " << yr << ":" << std::endl;
    std::cout<< "Average speed: " << m << " km/h" << std::endl;
    std::cout << "Sample stdev: " << sv << std::endl;
}

// Menu option 2: average temperature + stdev for every month of one year
void menuOption2(Bst<WeatherRecType> & WeatherTree)
{
    int yr = 0;
    std::cout << "\nWhich year do you want to search?\n";
    std::cin >> yr;                         // get the year from the user
    std::cout << yr << std::endl;
    std::cout << std::fixed << std::setprecision(1);

    for (int month = 1; month <= 12; month++)   // do this for every month
    {
        Vector<float> temp;                 // will hold temperatures for this month

        collectRec = Vector<WeatherRecType>();   // empty the collector
        WeatherTree.InorderTraversal(CollectData);  // BST sends every record to CollectData

        for (int i = 0; i<collectRec.Size(); i++)
        {
            const WeatherRecType& rec = collectRec[i];
            if  (rec.d.GetYear() == yr && rec.d.GetMonth() == month)
            {
                temp.Insert(temp.Size(), rec.temp);  // keep temperature if year and month match
            }
        }

        int t_count = temp.Size();
        if (t_count == 0)
        {
            std::cout << monthName(month) << ": No Data" << std::endl;
        }
        else if (t_count == 1)
        {
            float m = mean(temp, t_count);
            std::cout << monthName(month) << ": average: " << m << " degrees C" << std::endl;
        }
        else
        {
            float m = mean(temp, t_count);
            float ss = sqSum(temp, t_count, m);
            float sv = standardDV(ss, t_count);
            std::cout << monthName(month) << ": average: " << m << " degrees C, stdev: " << sv << std::endl;
        }
    }
}

// Menu option 3: Pearson correlation for one month (all years)
void menuOption3(std::map<int, Vector<WeatherRecType>> & monthMap)
{
    int month = 0;
    std::cout << "\nWhich month do you want to search? (1-12)\n";
    std::cin >> month;

    monthMapItr it = monthMap.find(month);
    if (it == monthMap.end() || it->second.Size() == 0)
    {
        std::cout << "No data for that month!";
        return;
    }

    Vector<float>windspeed;                 // three separate lists
    Vector<float>temp;
    Vector<float>sr;

    const Vector<WeatherRecType>& records = it->second;
    for (int i = 0; i < records.Size(); i++)
    {
        const WeatherRecType& rec = records[i];
        windspeed.Insert(windspeed.Size(), rec.speed);  // copy the three values
        temp.Insert(temp.Size(), rec.temp);
        sr.Insert(sr.Size(), rec.sr);
    }

    float s_t = sPCC(windspeed, temp);      // correlation speed vs temperature
    float s_r = sPCC(windspeed, sr);        // correlation speed vs solar
    float t_r = sPCC(temp, sr);             // correlation temperature vs solar

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Sample Pearson Correlation Coefficient for " << monthName(month) << std::endl;
    std::cout << "S_T: " << s_t << std::endl;
    std::cout << "S_R: " << s_r << std::endl;
    std::cout << "T_R: " << t_r << std::endl;
}

// Menu option 4: write monthly stats + MAD to a CSV file
void menuOption4(Bst<WeatherRecType> & WeatherTree)
{
    int yr = 0;
    std::cout << "\nWhich year do you want to search?\n";
    std::cin >> yr;

    std::ofstream outFile("WindTempSolar.csv");   // create/open the output file

    if (!outFile)                           // check the file opened successfully
    {
        std::cout << "Failed to open!" << std::endl;
        return;
    }

    outFile << std::fixed << std::setprecision(1);
    outFile << yr << std::endl;             // first line of the CSV is the year

    collectRec = Vector<WeatherRecType>();  // empty the collector
    WeatherTree.InorderTraversal(CollectData);  // BST fills collectRec with every record

    bool hasData = false;                   // remember if we wrote any month
    for (int month = 1; month <= 12; month++)
    {
        Vector<float> windspeed;
        Vector<float> temp;
        Vector<float> sr;

        for (int i=0; i<collectRec.Size(); i++)
        {
            const WeatherRecType & rec = collectRec[i];
            if(rec.d.GetYear() == yr && rec.d.GetMonth() == month)
            {
                windspeed.Insert(windspeed.Size(), rec.speed * 3.6f);  // convert m/s to km/h
                temp.Insert(temp.Size(), rec.temp);
                if  (rec.sr >= 100.0f)                                  // only use solar >= 100
                    sr.Insert(sr.Size(), rec.sr/6000.0f);               // convert to kWh/m2
            }
        }

        if (windspeed.Size() == 0 && temp.Size() == 0 && sr.Size() == 0)
            continue;                       // skip this month if it has no data

        outFile << monthName(month) << ",";
        if (windspeed.Size() >= 2)
        {
            float sp_m = mean(windspeed, windspeed.Size());
            float sp_ss = sqSum(windspeed, windspeed.Size(), sp_m);
            float sp_sv = standardDV(sp_ss, windspeed.Size());
            float sp_mad = mad(windspeed, windspeed.Size(), sp_m);
            outFile << sp_m << "(" << sp_sv << "," << sp_mad << ")";
        }
        outFile << ",";
        if (temp.Size() >= 2)
        {
            float t_m = mean(temp, temp.Size());
            float t_ss = sqSum(temp, temp.Size(), t_m);
            float t_sv = standardDV(t_ss, temp.Size());
            float t_mad = mad(temp, temp.Size(), t_m);
            outFile << t_m << "(" << t_sv << "," << t_mad << ")";
        }
        outFile << ",";
        if (sr.Size() > 0)
        {
            float sr_total = total(sr, sr.Size());
            outFile << sr_total;
        }
        outFile << std::endl;
        hasData = true;
    }

    if (!hasData)
    {
        outFile << "No Data " << std::endl; // write this if the whole year was empty
    }
}
