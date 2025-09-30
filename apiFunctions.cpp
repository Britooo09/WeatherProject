#include "lib/apiFunctions.hpp"
#include "lib/api_keys.hpp"
#include "lib/curlFunctions.hpp"
#include "lib/globals.hpp"
#include "lib/menuSystem.hpp"

#include <iostream>
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
	url_mode.append(query);

	isWeather ? url_consultType = "weather" : url_consultType = "forecast";
	isMetric ? url_units = "&units=metric" : url_units = "&units=imperial";

	return url_base + url_consultType + url_mode + url_appid + url_units + url_lang;
}

// Functions for different search methods
// TODO: Implement a way to differentiate between existing and non-existing locations before displaying any results
// In other words: Implement a way to identify when the input didn't return any results

void quickQuery()
{
	system("cls");
	cout << "*MAIN MENU*\nQuick query\n\n";
	cout << "In this mode, with just a simple input you can get weather data easily and quickly.\n";
	cout << "There are three possible ways to get the data:\n";
	cout << "\"Search by name\": The simplest method. Just enter the name of the location you want to consult.\n";
	cout << "\"Search by name + country code\": Same as the previous one, but allows to be more specific.\n";
	cout << "\"Search by ID\": This method requires knowing the ID of the location to query, but in return, it's the most accurate.\n";
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
			curlStart(urlConstruction(1));
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
			
			curlStart(urlConstruction(2));
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
}

void advancedSearch()
{
	// TO-DO: Implement function
	cout << "advancedSearch() called\n";
}

void viewData()
{
	// TO-DO: Implement function
	cout << "viewData() called\n";
}

void lastQuery()
{
	// TO-DO: Implement function
	cout << "lastQuery() called\n";
}
