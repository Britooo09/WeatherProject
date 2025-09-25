#include "lib/menuSystem.hpp"
#include "lib/initialConfigRead.hpp"
#include "lib/json.hpp"
#include <iostream>
#include <fstream>
#include <windows.h>

using std::cerr;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;

void intro()
{
    system("cls");
    cout << "Hello!\n";
    cout << "Welcome to the weather query tool.\n\n";

    cout << "This application uses the OpenWeatherMap API to obtain a variety of information about the current weather\n";
    cout << "conditions and forecasts around the world. Every part of the program and every query is highly customizable,\n";
    cout << "allowing the information to be tailored to your needs.\n\n";

    cout << "To begin, enter the number corresponding to the option you would like to run:\n";
    cout << "  1- Start program\n  9- Settings\n  0- Exit\n\n";

    cin >> opt;
    switch (opt)
    {
    case 1:
        // Start program
        // menu();
        break;

    case 9:
        // Config
        settings();
        break;

    case 0:
        // Close
        break;

    default:
        cout << "The option selected is invalid. Please, try again.\n\n";
        system("pause");
        intro();
        break;
    }
}

void menu()
{
    // Main menu
    cout << "Current language code: " << lang << ".\n\n";
    cout << "Is Metric the system of units selected?\n";
    isMetric ? cout << "Yes.\n\n" : cout << "No.\n\n";
    cout << "Is Weather the query mode selected?\n";
    isWeather ? cout << "Yes.\n\n" : cout << "No.\n\n";
}

void configError()
{
    system("cls");
    cerr << "Couldn't save the configuration file!\n";
    cerr << "Settings will not be applied and the default values will be used instead.\n\n";
    system("pause");
}

void settings()
{
    // Config menu
    string currentText;
    nlohmann::json j;

    system("cls");
    cout << "*SETTINGS*\n\n";
    cout << "Select the option you would like to change:\n";
    cout << "  1- Language\n  2- System of units of measurement\n  3- Default query mode\n  0- Back\n\n";

    cin >> opt;
    switch (opt)
    {
    case 1:
    {
        // Language setting
        system("cls");
        ifstream config("config.json");

        // Read the file to show the current settings
        if (config.is_open())
        {
            int currentSetting;
            j = nlohmann::json::parse(config);
            currentSetting = j["lang"];
            switch (currentSetting)
            {
            case 0:
                currentText = "English";
                break;

            case 1:
                currentText = "Spanish";
                break;

            default:
                currentText = "Invalid";
                break;
            }
            config.close();
        }
        else
        {
            currentText = "Error reading the config file";
        }

        cout << "*SETTINGS*\n";
        cout << "Language\n\n";
        cout << "This option allows to set the language of the program. This also affects the results.\n";
        cout << "Current setting: " << currentText << "\n";
        cout << "  1- English\n  2- Spanish\n  0- Back\n\n";

        // In order to add a new language, the following do and if blocks conditions must be adjusted accordingly
        do
        {
            cin >> opt;
            if (opt < 0 || opt > 2)
            {
                // If the option selected is not on the menu
                cerr << "\nThe option selected is invalid. Please, try again.\n\n";
            }

            else if (opt == 0)
            {
                // Get back to previous menu
                settings();
            }

            else
            {
                // Set "lang" on config.json
                ofstream config("config.json");
                if (config.is_open())
                {
                    j["lang"] = opt - 1;
                    lang = opt - 1;
                    config << j;
                    config.close();

                    cout << "\nSettings changed succesfully!\n\n";
                    system("pause");
                    settings();
                }

                else
                {
                    configError();
                    settings();
                }
            }

        } while (opt < 0 || opt > 2);
        break;
    }

    case 2:
    {
        // Units setting
        system("cls");
        ifstream config("config.json");

        // Read the file to show the current settings
        if (config.is_open())
        {
            bool currentSetting;
            j = nlohmann::json::parse(config);
            currentSetting = j["isMetric"];
            currentSetting ? currentText = "Metric" : currentText = "Imperial";
            config.close();
        }
        else
        {
            currentText = "Error reading the config file";
        }

        cout << "*SETTINGS*\n";
        cout << "System of units of measurement\n\n";
        cout << "This option allows to set the system of units used to display the results.\n";
        cout << "Current setting: " << currentText << "\n";
        cout << "  1- Metric\n  2- Imperial\n  0- Back\n\n";

        do
        {
            cin >> opt;
            switch (opt)
            {
            case 1:
            {
                // Set "isMetric": true on config.json
                ofstream config("config.json");
                if (config.is_open())
                {
                    j["isMetric"] = true;
                    isMetric = true;
                    config << j;
                    config.close();

                    cout << "\nSettings changed succesfully!\n\n";
                    system("pause");
                    settings();
                }

                else
                {
                    configError();
                    settings();
                }
                break;
            }
            case 2:
            {
                // Set "isMetric": false on config.json
                ofstream config("config.json");
                if (config.is_open())
                {
                    j["isMetric"] = false;
                    isMetric = false;
                    config << j;
                    config.close();

                    cout << "\nSettings changed succesfully!\n\n";
                    system("pause");
                    settings();
                }

                else
                {
                    configError();
                    settings();
                }
                break;
            }

            case 0:
                // Get back to previous menu
                settings();
                break;

            default:
                // If the option selected is not on the menu
                cerr << "\nThe option selected is invalid. Please, try again.\n\n";
                break;
            }
        } while (opt < 0 || opt > 2);
        break;
    }

    case 3:
    {
        // Mode setting
        system("cls");
        ifstream config("config.json");

        // Read the file to show the current settings
        if (config.is_open())
        {
            bool currentSetting;
            j = nlohmann::json::parse(config);
            currentSetting = j["isWeather"];
            currentSetting ? currentText = "Weather" : currentText = "Forecast";
            config.close();
        }
        else
        {
            currentText = "Error reading the config file";
        }

        cout << "*SETTINGS*\n";
        cout << "Default query mode\n\n";
        cout << "This option allows to change what results are displayed by default.\n";
        cout << "\"Weather\" represents the current weather conditions for the selected location.\n";
        cout << "\"Forecast\" is the weather forecast for the next 5 days for the selected location.\n";
        cout << "Current setting: " << currentText << "\n";
        cout << "  1- Weather\n  2- Forecast\n  0- Back\n\n";

        do
        {
            cin >> opt;
            switch (opt)
            {
            case 1:
            {
                // Set "isWeather": true on config.json
                ofstream config("config.json");
                if (config.is_open())
                {
                    j["isWeather"] = true;
                    isWeather = true;
                    config << j;
                    config.close();

                    cout << "\nSettings changed succesfully!\n\n";
                    system("pause");
                    settings();
                }

                else
                {
                    configError();
                    settings();
                }
                break;
            }
            case 2:
            {
                // Set "isWeather": false on config.json
                ofstream config("config.json");
                if (config.is_open())
                {
                    j["isWeather"] = false;
                    isWeather = false;
                    config << j;
                    config.close();

                    cout << "\nSettings changed succesfully!\n\n";
                    system("pause");
                    settings();
                }

                else
                {
                    configError();
                    settings();
                }
                break;
            }

            case 0:
                // Get back to previous menu
                settings();
                break;

            default:
                // If the option selected is not on the menu
                cerr << "\nThe option selected is invalid. Please, try again.\n\n";
                break;
            }
        } while (opt < 0 || opt > 2);
        break;
    }

    case 0:
        intro();
        break;

    default:
        cerr << "The option selected is invalid. Please, try again.\n\n";
        system("pause");
        settings();
        break;
    }
}
