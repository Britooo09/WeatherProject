#include "lib/json.hpp"
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;
using json = nlohmann::json;

// API key: 6a23773c0153f0beac3cf62e6df26495
// Compile: g++ menuTest.cpp -o menuTest.exe

// Global variables declaration
int opt;
string fileName = "testFiles/testFile.txt";

// Functions declaration
void resultsDisplay();
void menu();

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    menu();
    system("pause");
    return 0;
}

// Functions definition
// void resultsDisplay()
// {
//     string read;

//     ifstream fileRead(fileName);
//     if (fileRead.is_open())
//     {
//         while (fileRead >> read)
//         {
//             getline(fileRead, read);
//             cout << read << "\n\n";
//         }
//         fileRead.close();
//     }
// }

void menu()
{
    cout << "¡Hola!\n";
    cout << "Bienvenido a la utilidad de consulta del clima.\n";
    cout << "Esta aplicación usa la API de OpenWeatherMaps para obtener distinta información sobre el clima actual y los pronósticos alrededor del mundo. Cada parte del programa y cada consulta son altamente personalizables, con lo que se permite que la información se adapte a ti.\n";
    cout << "Para comenzar, escribe el número que corresponda a la opción que deseas ejecutar.\n  1- Iniciar programa\n  9- Configuración\n  0- Salir";

    // cin >> opt;
    // switch (opt)
    // {
    // case 1:
    //     /* code */
    //     break;

    // default:
    //     break;
    // }
}
