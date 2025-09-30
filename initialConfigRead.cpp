#include "lib/initialConfigRead.hpp"
#include "lib/globals.hpp"
#include "lib/json.hpp"
#include <iostream>
#include <fstream>

void initialConfigRead()
{
	std::ifstream config("config.json");
	nlohmann::json j;

	if (config.is_open())
	{
		// If a configuration file is found, here the program loads the settings in that file
		// If the configuration file is found to be corrupted or incomplete, the program should overwrite it with the default settings
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

		lang = 0;
		isMetric = true;
		isWeather = true;

		std::ofstream config("config.json");
		if (config.is_open())
		{
			j["lang"] = lang;
			j["isMetric"] = isMetric;
			j["isWeather"] = isWeather;

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
