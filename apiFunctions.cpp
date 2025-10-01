// Custom headers
#include "lib/apiFunctions.hpp"
#include "lib/api_keys.hpp"
#include "lib/curlFunctions.hpp"
#include "lib/globals.hpp"
#include "lib/menuSystem.hpp"

// 3rd party headers
#include "lib/json.hpp"

// Standard headers
#include <iostream>
#include <fstream>
#include <string>

using std::cerr;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;

string urlConstruction(int mode)
{
	string url_base = "https://api.openweathermap.org/data/2.5/";
	string url_appid = "&appid=" + OPENWEATHERMAP_API_KEY;
	string url_mode;
	string url_consultType;
	string url_units;
	string url_lang;

	string url_final;

	switch (lang)
	{
	case 0:
		// English
		url_lang = "&lang=en";
		break;

	case 1:
		// Spanish
		url_lang = "&lang=es";
		break;

	default:
		break;
	}

	(mode == 0 || mode == 1) ? url_mode = "?q=" : url_mode = "?id=";

	switch (mode)
	{
	case 0:
		// Query by name
		url_mode = "?q=";
		break;

	case 1:
		// Query by ID
		url_mode = "?id=";
		break;

	case 2:
		// Geocoding query
		url_mode = "?lat=";
		break;
	}

	url_mode.append(query);

	isWeather ? url_consultType = "weather" : url_consultType = "forecast";
	isMetric ? url_units = "&units=metric" : url_units = "&units=imperial";

	return url_base + url_consultType + url_mode + url_appid + url_units + url_lang;
}

void geocoding()
{
	cout << "Enter the name of the location you want to consult (e.g., 'London'):\n";
	cin >> query;
	curlStart("http://api.openweathermap.org/geo/1.0/direct?q=" + query + "&limit=9&appid=" + OPENWEATHERMAP_API_KEY);

	int optLimit = 9;
	ifstream showOptions(fileName);
	nlohmann::json j = nlohmann::json::parse(showOptions);

	if (showOptions.is_open())
	{
		for (int i = 0; i < 9; i++)
		{
			if (j[i]["name"] == nullptr)
			{
				optLimit = i;
				break;
			}
		}

		showOptions.close();
	}

	else
	{
		system("cls");
		cerr << "Couldn't parse the search results.\n";
		cerr << "Returning to main menu...\n\n";
		system("pause");
		menu();
	}

	// TODO: ACTUALLY show options
	cout << "Show options\n  0- Exit search";

	do
	{
		cin >> opt;
		if (opt < 0 || opt > optLimit)
		{
			// If the option selected is not on the menu
			cerr << "\nThe option selected is invalid. Please, try again.\n\n";
		}

		else if (opt == 0)
		{
			// Get back to main menu
			menu();
		}

		else
		{
			// Use the selected location's coordinates to perform a weather/forecast query
			opt = opt - 1;
			double lat = j[opt]["lat"];
			double lon = j[opt]["lon"];
			query = std::to_string(lat) + "&lon=" + std::to_string(lon);
			curlStart(urlConstruction(2));
		}
	} while (opt < 0 || opt > optLimit);
}

// Functions for different search methods
// TODO: Implement a way to differentiate between existing and non-existing locations before displaying any results
// In other words: Implement a way to identify when the input didn't return any results

// Al momento de presentar los resultados, se debe hacer un if para verificar si la ciudad en cuestión tiene un nombre en el idioma seleccionado
// Si lo tiene, mostrar ese nombre. Si no lo tiene, mostrar el nombre en inglés (el nombre principal).

void quickQuery()
{
	system("cls");
	cout << "*MAIN MENU*\nQuick query\n\n";
	cout << "In this mode, with just a simple input you can get weather data easily and quickly.\n";
	cout << "There are three possible ways to get the data:\n";
	cout << "-\"Search by name\": The simplest method. Just enter the name of the location you want to consult.\n";
	cout << "-\"Search by name + country code\": Same as the previous one, but allows to be more specific.\n";
	cout << "-\"Search by ID\": This method requires knowing the ID of the location to query, but in return, it's the most accurate.\n";
	cout << "  1- Search by name\n  2- Search by name + country code\n  3- Search by ID\n  0- Back\n\n";

	do
	{
		cin >> opt;
		switch (opt)
		{
		case 1:
			// Search by name
			system("cls");
			cout << "*QUICK QUERY*\nSearch by name\n\n";
			cout << "Enter the name of the location you want to consult (e.g., 'London'):\n";
			cin >> query;
			curlStart(urlConstruction(0));
			break;

		case 2:
		{
			// Search by name + country code
			string tempQuery;

			system("cls");
			cout << "*QUICK QUERY*\nSearch by name + country code\n\n";
			cout << "First, enter the name of the location you want to consult (e.g., 'London'):\n";
			cin >> query;
			query.append(",");
			cout << "Now, enter the corresponding 2-character country code (e.g., 'uk'):\n";
			cin >> tempQuery;

			// Check if tempQuery is a valid 2-character country code
			while (tempQuery.length() != 2)
			{
				cerr << "\nInvalid country code. It must be exactly 2 characters long. Please, try again.\n\n";
				cin >> tempQuery;
			}

			query.append(tempQuery);
			curlStart(urlConstruction(0));
			break;
		}

		case 3:
			// Search by ID
			bool isNumber;

			system("cls");
			cout << "*QUICK QUERY*\nSearch by ID\n\n";
			cout << "Enter the ID of the location you want to consult (e.g., '2643743' for London, UK):\n";

			do
			{
				isNumber = true;
				cin >> query;
				for (char c : query)
				{
					if (!isdigit(c))
					{
						isNumber = false;
						cerr << "\nInvalid ID. It must be a numeric value. Please, try again.\n\n";
						break;
					}
				}
			} while (!isNumber);

			curlStart(urlConstruction(1));
			break;

		case 0:
			// Get back to previous menu
			menu();
			break;

		default:
			// If the option selected is not on the menu
			cerr << "\nThe option selected is invalid. Please, try again.\n\n";
			break;
		}
	} while (opt < 0 || opt > 3);

	displayResults();
}

void advancedSearch()
{
	system("cls");
	cout << "*MAIN MENU*\nAdvanced search\n\n";
	cout << "With this mode, you can perform a search and select a location from a list of results.\n";
	cout << "Use it specially if you don't get the desired results with the quick query mode.\n";
	cout << "  1- Start search\n  0- Back\n\n";

	do
	{
		cin >> opt;
		switch (opt)
		{
		case 1:
			// Perform search
			system("cls");
			cout << "*ADVANCED SEARCH*\nPerform search\n\n";
			geocoding();
			displayResults();
			break;

		case 0:
			// Get back to previous menu
			menu();
			break;

		default:
			// If the option selected is not on the menu
			cerr << "\nThe option selected is invalid. Please, try again.\n\n";
			break;
		}
	} while (opt < 0 || opt > 1);
}

void viewData()
{
	// TODO: Implement function
	system("cls");
	cout << "*MAIN MENU*\nView data\n\n";
	cout << "This mode allows checking technical details about the selected location, such as:\n";
	cout << "  - City ID\n";
	cout << "  - Coordinates (latitude and longitude)\n";
	cout << "  - Location names in supported languages\n";
	cout << "  - Timezone\n";
	cout << "  - Sunrise and sunset time\n";
	cout << "  - And more\n\n";
}

void lastQuery()
{
	// TODO: Implement function
	cout << "lastQuery() called\n";
}

// Function only for testing purposes. Remove later and replace with actual result display function
void displayResults()
{
	system("cls");
	cout << "*DISPLAY RESULTS*\n\n";
	if (curlError)
	{
		cerr << "An error occurred while trying to retrieve the data.\n";
		cerr << "Please, check your internet connection and try again.\n\n";
		system("pause");
		menu();
	}
	ifstream results(fileName);
	nlohmann::json j = nlohmann::json::parse(results);
	if (results.is_open())
	{
		if (isWeather)
		{
			// Display weather data
			cout << "Location: " << j["name"] << ", " << j["sys"]["country"] << "\n";
			cout << "Weather: " << j["weather"][0]["description"] << "\n";
			cout << "Temperature: " << j["main"]["temp"] << (isMetric ? " °C" : " °F") << "\n";
			cout << "Feels like: " << j["main"]["feels_like"] << (isMetric ? " °C" : " °F") << "\n";
			cout << "Humidity: " << j["main"]["humidity"] << " %\n";
			cout << "Wind speed: " << j["wind"]["speed"] << (isMetric ? " m/s" : " mph") << "\n";
			cout << "Cloudiness: " << j["clouds"]["all"] << " %\n";
			cout << "\n";
		}
		else
		{
			// Display forecast data
			cout << "Location: " << j["city"]["name"] << ", " << j["city"]["country"] << "\n";
			cout << "Forecast:\n";
			for (const auto& item : j["list"])
			{
				cout << "- Date & Time: " << item["dt_txt"] << "\n";
				cout << "  Weather: " << item["weather"][0]["description"] << "\n";
				cout << "  Temperature: " << item["main"]["temp"] << (isMetric ? " °C" : " °F") << "\n";
				cout << "  Feels like: " << item["main"]["feels_like"] << (isMetric ? " °C" : " °F") << "\n\n";
			}
		}

		system("pause");
	}
}
