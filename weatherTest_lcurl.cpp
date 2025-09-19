#include "lib/curl/curl.h"
#include "lib/json.hpp"
#include "lib/api_keys.hpp"
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;
using json = nlohmann::json;

// Compile: g++ weatherTest_lcurl.cpp -o weatherTest_lcurl.exe -lcurl

// Función que procesa cada chunk de datos recibido desde la API
size_t callback(void *contents, size_t unitsize, size_t qty, void *userp)
{
    size_t realsize = unitsize * qty;            // Variable que almacena el tamaño total procesado
    auto *buffer = static_cast<string *>(userp); // Conversión del puntero userp
    auto *data = static_cast<char *>(contents);  // Conversión del puntero contents
    buffer->append(data, realsize);              // Se añaden los datos obtenidos al string al que apunta el puntero buffer (api_response)

    return realsize;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Declaración de variables de cURL
    CURL *curl;
    CURLcode res;
    string api_response;

    // Declaración de variables relacionadas con la API
    string base_url = "http://api.openweathermap.org/data/2.5/forecast?id=524901";
    string apikey_url = "&appid=" + OPENWEATHERMAP_API_KEY;
    string units_url;
    string lang_url;
    int units;
    int lang;

    ifstream cfgFile("testFiles/config.json");
    if (cfgFile.is_open())
    {
        json cfgRead = json::parse(cfgFile);
        units = cfgRead["units"];
        lang = cfgRead["lang"];

        if (units == 0)
        {
            units_url = "&units=metric";
        }
        else if (units == 1)
        {
            units_url = "&units=imperial";
        }
        else
        {
            cerr << "Configuración inválida. Se cerrará el programa.\n\n";
            cfgFile.close();
            system("pause");
            return 1;
        }

        if (lang == 0)
        {
            lang_url = "&lang=en";
        }
        else if (lang == 1)
        {
            lang_url = "&lang=es";
        }
        else
        {
            cerr << "Configuración inválida. Se cerrará el programa.\n\n";
            cfgFile.close();
            system("pause");
            return 1;
        }
        cfgFile.close();
    }
    else
    {
        cerr << "El archivo de configuración no existe. Se cerrará el programa.\n\n";
        system("pause");
        return 1;
    }
    string url = base_url + units_url + lang_url + apikey_url;

    // Inicio de cURL
    curl = curl_easy_init();
    if (curl)
    {
        // Función que establece la URL de la cual se obtendrá la información
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Función que le dice a cURL que use la función de callback para escribir los datos
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

        // Función que le dice a cURL que almacene los datos recibidos en la variable api_response declarada anteriormente
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &api_response);

        // Operaciones realizadas por cURL
        res = curl_easy_perform(curl);
        if (res == CURLE_OK)
        {
            char *ct;
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);

            // Instrucciones que crean y escriben el archivo .json con la información obtenida de la API
            ofstream wWrite("testFiles/weather.json");
            wWrite << api_response;
            wWrite.close();

            if ((res == CURLE_OK) && ct)
            {
                cout << "Se recibió el siguiente tipo de datos: \n"
                     << ct << ".\n\n";
                system("pause");
            }

            system("cls");
            ifstream wRead("testFiles/weather.json"); // Abre el archivo
            if (wRead.is_open())
            {
                json j = json::parse(wRead); // Analiza el archivo

                // Se muestran los datos en pantalla
                cout << "Temperatura: " << j["list"][0]["main"]["temp"] << "°";
                if (units == 0)
                {
                    cout << "C.\n";
                }
                else
                    cout << "F.\n";
                cout << "Clima: " << j["list"][0]["weather"][0]["description"] << ".\n\n";

                // Cierre del programa
                system("pause");
                wRead.close();
            }
        }
        else
        {
            // Comportamiento en caso de fallo de cURL
            cerr << "No se pudo ejecutar la operación.\n";
            cerr << "En ocasiones, esto significa que no se pudo conectar con el servidor.\n";
            cerr << "Error: " << curl_easy_strerror(res) << "\n\n";
            return 1;
        }

        // Limpieza final del handle de cURL
        curl_easy_cleanup(curl);
    }
    // Final de cURL

    return 0;
}