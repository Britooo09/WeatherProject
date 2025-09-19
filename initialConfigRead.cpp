#include "lib/json.hpp"
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;
using json = nlohmann::json;

int lang;
bool isMetric;

void initialConfigRead()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    ifstream config("config.json");
    json j;

    if (config.is_open())
    {
        // If a configuration file is found, here the program loads the settings in that file
        j = json::parse(config);
        lang = j["lang"];
        isMetric = j["isMetric"];

        config.close();
    }

    else
    {
        // If a configuration file is not found, here the program writes a new one with the default settings
        // Currently, the default settings include:
        // Language = English ("lang": 0)
        // Units = Metric ("isMetric": true)

        ofstream config("testFiles/config.json");
        if (config.is_open())
        {
            j["lang"] = 0;
            j["isMetric"] = true;
            lang = 0;
            isMetric = true;

            config << j;
            config.close();
        }

        else
        {
            system("cls");
            cerr << "Couldn't save the configuration file!\n";
            cerr << "Settings will not be applied and the default values will be used instead.\n\n";
        }
    }

    system("pause");
}