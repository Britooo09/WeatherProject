#include "lib/json.hpp"
#include "lib/initialConfigRead.hpp"
#include <iostream>
#include <fstream>
#include <windows.h>

// Languages
#include "lang/English.hpp"

using namespace std;
using json = nlohmann::json;

// Compile: g++ menuSystem.cpp -o menuSystem.exe

// Global variables declaration
int opt;

// Functions declaration
void intro();
void menu();
void settings();

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    initialConfigRead();
    intro();
    system("pause");
    return 0;
}

// Functions definition

void intro()
{
    system("cls");
    cout << "Hello!\n";
    cout << "Welcome to the weather query tool.\n\n";

    cout << "This application uses the OpenWeatherMap API to obtain a variety of information about the current weather conditions\n";
    cout << "and forecasts around the world. Every part of the program and every query is highly customizable, allowing \n";
    cout << "the information to be tailored to your needs.\n\n";

    cout << "To begin, enter the number corresponding to the option you would like to run.\n";
    cout << "  1- Start program\n  9- Settings\n  0- Exit\n\n";

    cin >> opt;
    switch (opt)
    {
    case 1:
        // Start program
        menu();
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
    if (isMetric)
    {
        cout << "Yes.\n\n";
    }
    else
    {
        cout << "No.\n\n";
    }
}

void settings()
{
    // Config menu. Current objectives: language and units.
    system("cls");
    cout << "Message saying which option to set.\n";
    cout << "  1- Language\n  2- System of units of measurement\n  0- Back\n\n";

    cin >> opt;
    switch (opt)
    {
    case 1:
        // Language setting
        system("cls");
        // TODO: Open config.json as read, to show current setting
        cout << "Message saying which language to set.\n";
        cout << "  1- English\n  2- Spanish\n  0- Back\n\n";

        // TODO: Open config.json as write, to save the new setting
        cin >> opt;

        // In order to add a new language, the following if statement condition must bu adjusted accordingly
        if (opt <= 0 || opt > 2)
        {
            cout << "The option selected is invalid. Please, try again.\n\n";
            system("pause");
            // Reload this menu
        }

        else
        {
            // Save the new setting on config.json
            lang = opt - 1;
        }
        break;

    case 2:
        // Units setting
        system("cls");
        // TODO: Open config.json as read, to show current setting
        cout << "Message saying which system of units of measurement to set.\n";
        cout << "  1- Metric\n  2- Imperial\n  0- Back\n\n";

        // TODO: Open config.json as write, to save the new setting
        cin >> opt;

        switch (opt)
        {
        case 1:
            // Set "isMetric": true on config.json
            break;

        case 2:
            // Set "isMetric": false on config.json
            break;

        default:
        cout << "The option selected is invalid. Please, try again.\n\n";
        system("pause");
        // Reload this menu
        break;
        }

    case 0:
        // Back. Reload previous menu
        break;

    default:
        cout << "The option selected is invalid. Please, try again.\n\n";
        system("pause");
        // Reload this menu
        break;
    }
}

/*
SPANISH TEXT:
intro():

cout << "\t\t\t\t\t    ¡Hola!\n";
cout << "\t\t\tBienvenido a la utilidad de consulta del clima.\n\n";

cout << "Esta aplicación usa la API de OpenWeatherMap para obtener distinta información sobre el clima actual\n";
cout << "y los pronósticos alrededor del mundo. Cada parte del programa y cada consulta son altamente personalizables,\n";
cout << "con lo que se permite que la información se adapte a ti.\n\n";

cout << "Para comenzar, escribe el número que corresponda a la opción que deseas ejecutar.\n";
cout << "  1- Iniciar programa\n  9- Configuración\n  0- Salir\n\n";

La opción seleccionada no es válida. Por favor, inténtalo de nuevo.\n\n
*/
