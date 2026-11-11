#include "Vector.h"
#include "WeatherRecType.h"
#include "ReadFile.h"
#include <iostream>
#include <map>
#include "MenuOption.h"
#include "FuncPtr.h"

using namespace std;

int main()
{
    Bst<WeatherRecType> weathertree;
    map<int, Vector<WeatherRecType>> monthMap;

    openFile("data/data_source.txt", weathertree, monthMap);

    int option = 0;
    while(option != 5)
    {
        cout << "\n========== Menu Option ==========" << endl;
        cout << "1. Average wind speed and standard deviation for wind speed given a specified month and year\n";
        cout << "2. Average ambient air temperature and standard deviation for each month of a specified year\n";
        cout << "3. Sample Pearson Correlation Coeffient for a specifed month\n";
        cout << "4. Average wind speed (km/h), average ambient air temperature and total solar radiation in kWh/m2 for each month of a specified year.\n";
        cout << "5. Quit the program\n";
        cin >> option;

        switch (option)
        {
        case 1:
            menuOption1(monthMap);
            break;
        case 2:
            menuOption2(weathertree);
            break;
        case 3:
            menuOption3(monthMap);
            break;
        case 4:
            menuOption4(weathertree);
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice\n";
        }
    }
    /*
    //test traversal
    cout << "Inorder Traversal: ";
    weathertree.InorderTraversal(PrintData);
    cout << endl << endl;
    */

    /*
    //test map - march
    cout << "Print Map" << endl;
    if (monthMap.find(3) != monthMap.end())
    {
        Vector<WeatherRecType>& march = monthMap[3];
        for (int i= 0; i<march.Size(); i++)
        {
        cout << march[i].d << "  " << march[i].speed << "  " << march[i].temp << "  " << march[i].sr << "\n";
        }
    }
    */

    return 0;
}
