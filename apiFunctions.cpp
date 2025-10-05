// Custom headers
#include "lib/apiFunctions.hpp"
#include "lib/api_keys.hpp"
#include "lib/curlFunctions.hpp"
#include "lib/globals.hpp"
#include "lib/menuSystem.hpp"
#include "lib/otherFunctions.hpp"

// 3rd party headers
#include "lib/json.hpp"

// Standard headers
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

using std::cerr;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;

string queryOld;
bool resultsFound = true;

// Checks if the query string is valid before performing the cURL operation
void checkQuery()
{
	// Check if the query string is empty
	if (query.empty())
	{
		cerr << "\nError: The query string is empty.\n";
		cerr << "Returning to main menu...\n\n";
		queryOK = false;
		system("pause");
		menu();
		return;
	}

	// Check if the query string is too long
	if (query.length() > 50)
	{
		cerr << "\nError: The query string is too long.\n";
		cerr << "Returning to main menu...\n\n";
		queryOK = false;
		system("pause");
		menu();
		return;
	}

	// TODO: Check if the query string contains invalid characters? Maybe later

	// Check if the query string contains spaces and replace them with '%20'
	queryOld = query;
	for (int i = 0; i < query.length(); i++)
	{
		if (query[i] == ' ')
		{
			query.replace(i, 1, "%20");
		}
	}
}

// Constructs the URL for the cURL operation based on the selected search method and current settings
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

	default:
		break;
	}

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

// Uses the Geocoding API to search for a location and display a list of results to choose from
void geocoding()
{
	cout << "Enter the name of the location you want to consult (e.g., 'London'):\n";
	cin.ignore();
	std::getline(cin, query);

	checkQuery();
	if (!queryOK)
	{
		return;
	}

	curlStart("http://api.openweathermap.org/geo/1.0/direct?q=" + query + "&limit=9&appid=" + OPENWEATHERMAP_API_KEY);
	if (!curlOK)
	{
		return;
	}

	int optLimit = 9;
	resultsFound = true;
	ifstream showOptions(fileName);
	if (showOptions.is_open())
	{
		nlohmann::json j = nlohmann::json::parse(showOptions);

		system("cls");
		cout << "*SEARCH*\n";
		cout << "Results for \"" << queryOld << "\":\n\n";
		for (int i = 0; i < 9; i++)
		{
			if (j[i]["name"] == nullptr)
			{
				optLimit = i;
				if (optLimit == 0)
				{
					cout << "Sorry, no results found.\n";
					cout << "You can try again with a different search term.\n";
					cout << "Here are some tips to improve your search:\n";
					cout << "  - Make sure the spelling is correct.\n";
					cout << "  - Use only latin characters to perform the query.\n";
					cout << "  - Try adding the country code (e.g., 'London,uk').\n\n";
					cout << "Returning to main menu...\n\n";

					resultsFound = false;
					system("pause");
					return;
				}
				break;
			}

			else
			{
				cout << i + 1 << "- Location name: " << j[i]["name"] << "\n";
				cout << "   Latitude: " << j[i]["lat"] << "\n";
				cout << "   Longitude: " << j[i]["lon"] << "\n";
				cout << "   Country: " << j[i]["country"] << "\n";
				cout << "   State: " << j[i]["state"] << "\n\n";
			}
		}

		cout << "0- Exit search\n\n";
		cout << "Didn't find what you were looking for?\n";
		cout << "You can try again with a different search term.\n";
		cout << "Here are some tips to improve your search:\n";
		cout << "  - Make sure the spelling is correct.\n";
		cout << "  - Use only latin characters to perform the query.\n";
		cout << "  - Try adding the country code (e.g., 'London,uk').\n\n";

		cout << "Enter the number corresponding to the desired option:\n\n";

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

				if (!curlOK)
				{
					menu();
					return;
				}
			}
		} while (opt < 0 || opt > optLimit);

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
}

// Performs a quick query using one of three methods, that gets an immediate result
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
			cin.ignore();
			std::getline(cin, query);

			checkQuery();
			if (!queryOK)
			{
				return;
			}

			curlStart(urlConstruction(0));
			if (!curlOK)
			{
				menu();
				return;
			}

			break;

		case 2:
		{
			// Search by name + country code
			string tempQuery;

			system("cls");
			cout << "*QUICK QUERY*\nSearch by name + country code\n\n";
			cout << "First, enter the name of the location you want to consult (e.g., 'London'):\n";
			cin.ignore();
			std::getline(cin, query);

			checkQuery();
			if (!queryOK)
			{
				return;
			}

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
			if (!curlOK)
			{
				menu();
				return;
			}

			break;
		}

		case 3:
			// Search by ID
			bool isNumber;

			system("cls");
			cout << "*QUICK QUERY*\nSearch by ID\n\n";
			cout << "Enter the ID of the location you want to consult (e.g., '2643743' for London, UK):\n";

			// Check if the input is a number
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
			if (!curlOK)
			{
				menu();
				return;
			}

			break;

		case 0:
			// Get back to previous menu
			menu();
			return;

		default:
			// If the option selected is not on the menu
			cerr << "\nThe option selected is invalid. Please, try again.\n\n";
			break;
		}
	} while (opt < 0 || opt > 3);

	// After the search is performed, check if results were found
	resultsFound = true;
	ifstream checkResults(fileName);
	if (checkResults.is_open())
	{
		nlohmann::json j = nlohmann::json::parse(checkResults);

		if (isWeather && (j["name"] == nullptr))
		{
			resultsFound = false;
			checkResults.close();
		}
		else if ((!isWeather) && (j["cod"] == nullptr))
		{
			resultsFound = false;
			checkResults.close();
		}
	}

	else
	{
		system("cls");
		cerr << "Couldn't parse the search results.\n";
		cerr << "Returning to main menu...\n\n";
		system("pause");
		menu();
		return;
	}

	if (resultsFound)
	{
		displayResults(isWeather);
	}

	else
	{
		system("cls");
		cout << "*QUICK QUERY*\n";
		switch (opt)
		{
		case 1:
			cout << "Search by name\n\n";
			break;

		case 2:
			cout << "Search by name + country code\n\n";
			break;

		case 3:
			cout << "Search by ID\n\n";
			break;
		}

		cout << "Sorry, no results found.\n";
		cout << "You can try again with a different search term.\n";
		cout << "Here are some tips to improve your search:\n";
		cout << "  - Make sure the spelling is correct.\n";
		cout << "  - Use only latin characters to perform the query.\n";
		cout << "  - Try other search methods.\n\n";
		cout << "Returning to main menu...\n\n";

		system("pause");
		menu();
	}
}

// Performs a search using the Geocoding API and select a location from a list of results
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

			(curlOK && resultsFound) ? displayResults(isWeather) : menu();
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

// Performs a search using the Geocoding API and select a location from a list of results to view its technical details
void viewData()
{
	system("cls");
	cout << "*MAIN MENU*\nView data\n\n";
	cout << "This mode allows checking technical details about the selected location, such as:\n";
	cout << "- City ID\n";
	cout << "- Coordinates (latitude and longitude)\n";
	cout << "- Timezone\n";
	cout << "- Sunrise and sunset time\n";
	cout << "- And more...\n";
	cout << "  1- Start search\n  0- Back\n\n";

	do
	{
		cin >> opt;
		switch (opt)
		{
		case 1:
		{
			// Perform search
			system("cls");
			cout << "*VIEW DATA*\nPerform search\n\n";

			// Temporarily set isWeather to true to get the location data
			bool tempIsWeather = isWeather;
			isWeather = true;
			geocoding();
			isWeather = tempIsWeather;

			(curlOK && resultsFound) ? displayViewData() : menu();
			break;
		}

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

// Repeats the last successful query performed
void lastQuery()
{
	system("cls");
	cout << "*MAIN MENU*\nRepeat last query\n\n";
	cout << "This option shows the results of the last successful query made.\n";
	cout << "Use it to quickly check the weather/forecast of the last location consulted.\n";
	cout << "  1- Repeat last query\n  0- Back\n\n";

	do
	{
		cin >> opt;
		switch (opt)
		{
		case 1:
			// Repeat query
			system("cls");
			loadQuery();
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

// Displays the results of the query performed with any method (weather or forecast)
void displayResults(bool weather)
{
	system("cls");
	ifstream data(fileName);
	nlohmann::json j = nlohmann::json::parse(data);
	if (data.is_open())
	{
		if (weather)
		{
			// Save the city ID for future queries
			int id = j["id"];
			query = std::to_string(id);
			saveQuery(std::to_string(id), 0);

			// Display weather data
			cout << "*CURRENT WEATHER*\n";
			cout << "For " << j["name"] << ", " << j["sys"]["country"] << "\n\n";
			cout << "At " << unixConversion(j["dt"], true) << " UTC:\n\n";

			cout << "Weather: " << j["weather"][0]["description"] << "\n";
			cout << "Temperature: " << j["main"]["temp"] << (isMetric ? " °C" : " °F") << "\n";
			cout << "Feels like: " << j["main"]["feels_like"] << (isMetric ? " °C" : " °F") << "\n";
			cout << "Humidity: " << j["main"]["humidity"] << " %\n";
			cout << "Wind speed: " << j["wind"]["speed"] << (isMetric ? " m/s" : " mph") << "\n";
			cout << "Cloudiness: " << j["clouds"]["all"] << " %\n\n";

			cout << "Weather data provided by OpenWeatherMap.\n\n";
			cout << "Select one of the following options to continue:\n";
			cout << "  1- Display 5-day forecast data\n  2- See additional data about this location\n  0- Return to main menu\n\n";

			do
			{
				cin >> opt;
				switch (opt)
				{
				case 1: case 2:
				{
					// Use the city ID to perform a forecast/additional data query
					bool tempIsWeather = isWeather;
					(opt == 1) ? isWeather = false : isWeather = true;

					curlStart(urlConstruction(1));
					if (!curlOK)
					{
						menu();
						return;
					}

					isWeather = tempIsWeather;
					data.close();
					(opt == 1) ? displayResults(false) : displayViewData();

					break;
				}

				case 0:
					// Return to main menu
					menu();
					break;

				default:
					// If the option selected is not on the menu
					cerr << "\nThe option selected is invalid. Please, try again.\n\n";
					break;
				}
			} while (opt < 0 || opt > 2);
		}

		else
		{
			// Save the city ID for future queries
			int id = j["city"]["id"];
			query = std::to_string(id);
			saveQuery(std::to_string(id), 1);

			// Display forecast data
			cout << "*5-DAY FORECAST*\n";
			cout << "For " << j["city"]["name"] << ", " << j["city"]["country"] << "\n\n";
			cout << "Data every 3 hours, 40 entries starting from " << unixConversion(j["list"][0]["dt"], true) << " UTC:\n\n";
			for (const auto& item : j["list"])
			{
				cout << "- " << unixConversion(item["dt"], true) << " UTC\n";
				cout << "  Weather: " << item["weather"][0]["description"] << "\n";
				cout << "  Temperature: " << item["main"]["temp"] << (isMetric ? " °C" : " °F") << "\n";
				cout << "  Feels like: " << item["main"]["feels_like"] << (isMetric ? " °C" : " °F") << "\n\n";
			}

			cout << "Weather data provided by OpenWeatherMap.\n";
			cout << "Remember to scroll up to see all entries!\n\n";
			cout << "Select one of the following options to continue:\n";
			cout << "  1- Display current weather data\n  2- See additional data about this location\n  0- Return to main menu\n\n";

			do
			{
				cin >> opt;
				switch (opt)
				{
				case 1: case 2:
				{
					// Use the city ID to perform a weather/additional data query
					bool tempIsWeather = isWeather;
					isWeather = true;

					curlStart(urlConstruction(1));
					if (!curlOK)
					{
						menu();
						return;
					}

					isWeather = tempIsWeather;
					data.close();
					(opt == 1) ? displayResults(true) : displayViewData();

					break;
				}

				case 0:
					// Return to main menu
					menu();
					break;

				default:
					// If the option selected is not on the menu
					cerr << "\nThe option selected is invalid. Please, try again.\n\n";
					break;
				}
			} while (opt < 0 || opt > 2);
		}
	}
}

// Displays additional data about the location queried
void displayViewData()
{
	ifstream data(fileName);
	nlohmann::json j = nlohmann::json::parse(data);

	system("cls");
	cout << "*ADDITIONAL DATA*\n";
	cout << "For " << j["name"] << ", " << j["sys"]["country"] << "\n\n";

	if (data.is_open())
	{
		// Save the city ID for future queries
		int id = j["id"];
		query = std::to_string(id);
		saveQuery(std::to_string(id), 2);

		std::uint32_t localTimestamp = j["dt"];
		std::uint32_t localTimezone = j["timezone"];

		cout << "City ID: " << j["id"] << "\n";
		cout << "Latitude: " << j["coord"]["lat"] << "\n";
		cout << "Longitude: " << j["coord"]["lon"] << "\n";
		cout << "Sunrise: " << unixConversion(j["sys"]["sunrise"], false) << " UTC\n";
		cout << "Sunset: " << unixConversion(j["sys"]["sunset"], false) << " UTC\n\n";
		cout << "Timezone: " << timezoneConversion(j["timezone"]) << "\n";
		cout << "Local time: " << unixConversion((localTimestamp + localTimezone), true) << "\n";
		cout << "Query timestamp: " << unixConversion(j["dt"], true) << " UTC\n\n";

		cout << "Weather data provided by OpenWeatherMap.\n\n";
		cout << "Select one of the following options to continue:\n";
		cout << "  1- Display current weather data\n  2- Display 5-day forecast data\n  0- Return to main menu\n\n";

		do
		{
			cin >> opt;
			switch (opt)
			{
			case 1: case 2:
			{
				// Use the city ID to perform a weather/forecast query
				bool tempIsWeather = isWeather;
				(opt == 1) ? isWeather = true : isWeather = false;

				curlStart(urlConstruction(1));
				if (!curlOK)
				{
					menu();
					return;
				}

				isWeather = tempIsWeather;
				data.close();
				(opt == 1) ? displayResults(true) : displayResults(false);

				break;
			}

			case 0:
				// Return to main menu
				menu();
				break;

			default:
				// If the option selected is not on the menu
				cerr << "\nThe option selected is invalid. Please, try again.\n\n";
				break;
			}
		} while (opt < 0 || opt > 2);
	}
}
