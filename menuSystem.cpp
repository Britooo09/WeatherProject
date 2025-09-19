#include "lib/json.hpp"
#include <iostream>
#include <fstream>
#include <windows.h>

// Languages
#include "lang/English.h"

using namespace std;
using json = nlohmann::json;

// Compile: g++ menuSystem.cpp -o menuSystem.exe

// Global variables declaration
int opt;
string fileName = "testFiles/testFile.txt";

// Functions declaration
void resultsDisplay();
void initialConfigRead();
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

void initialConfigRead()
{
    // Contents of the file “initialConfigRead.cpp” must be implemented here once reviewed
}

void intro()
{
    system("cls");
    cout << "\t\t\t\t\t    Hello!\n";
    cout << "\t\t\tWelcome to the weather query tool.\n\n";

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
}

void settings()
{
    // Config menu. Current objectives: language and units.
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
