// Custom headers
#include "lib/otherFunctions.hpp"
#include "lib/apiFunctions.hpp"
#include "lib/curlFunctions.hpp"
#include "lib/globals.hpp"
#include "lib/menuSystem.hpp"

// 3rd party headers
#include "lib/json.hpp"

// Standard headers
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <format>

using std::string;

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

string unixConversion(std::uint32_t timestamp, bool isFullDate) {

	// 1. Create time_point (UTC)
	std::chrono::sys_seconds tp{ std::chrono::seconds{timestamp} };

	// 2. Break down the date part
	std::chrono::year_month_day date_part{ floor<std::chrono::days>(tp) };

	// 3. Break down the time part
	std::chrono::hh_mm_ss time_part{ tp - floor<std::chrono::days>(tp) };

	// 4. Satve date components individually in strings using std::format
	string year = std::format("{:%Y}", date_part);
	string month = std::format("{:%m}", date_part);
	string day = std::format("{:%d}", date_part);

	// 5. Save time components individually in strings using std::format
	string hour = std::format("{:%H}", time_part);
	string minute = std::format("{:%M}", time_part);
	string second = std::format("{:%S}", time_part);

	if (isFullDate)
	{
		return year + "-" + month + "-" + day + " " + hour + ":" + minute + ":" + second;
	}

	else {
		return hour + ":" + minute + ":" + second;
	}
}

string timezoneConversion(int offset)
{
	string tz;
	int hours = offset / 3600;
	int minutes = (offset % 3600) / 60;

	if (offset < 0)
	{
		tz = "UTC-" + std::to_string(abs(hours));
	}
	else {
		tz = "UTC+" + std::to_string(abs(hours));
	}

	if (minutes != 0)
	{
		tz.append(":" + std::to_string(abs(minutes)));
	}

	return tz;
}
