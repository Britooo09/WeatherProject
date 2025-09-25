#ifndef INITIALCONFIGREAD_H
#define INITIALCONFIGREAD_H

#include "json.hpp"
#include <iostream>
#include <fstream>

int lang;
bool isMetric;
bool isWeather;
void initialConfigRead()
{
    std::ifstream config("config.json");
    nlohmann::json j;

    if (config.is_open())
    {
        // If a configuration file is found, here the program loads the settings in that file
        j = nlohmann::json::parse(config);
        lang = j["lang"];
        isMetric = j["isMetric"];
        isWeather = j["isWeather"];

        config.close();
    }

    else
    {
        // If a configuration file is not found, here the program writes a new one with the default settings
        // Currently, the default settings include:
        // Language = English ("lang": 0)
        // Units = Metric ("isMetric": true)
        // Mode = Weather ("isWeather": true)

        std::ofstream config("config.json");
        if (config.is_open())
        {
            j["lang"] = 0;
            j["isMetric"] = true;
            j["isWeather"] = true;
            lang = 0;
            isMetric = true;
            isWeather = true;

            config << j;
            config.close();
        }

        else
        {
            system("cls");
            std::cerr << "Couldn't save the configuration file!\n";
            std::cerr << "Settings will not be applied and the default values will be used instead.\n\n";
            system("pause");
        }
    }
}

#endif
