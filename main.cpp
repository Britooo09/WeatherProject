#include "lib/curl/curl.h"
#include "lib/json.hpp"
#include "lib/api_keys.hpp"
#include "lib/initialConfigRead.hpp"
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;
using json = nlohmann::json;

// Compile: g++ main.cpp -o main.exe -lcurl

// Global variables declaration
int opt;
int mode = 0;        // 0. City Name; 1. City Name + Country Code; 2. ID
int consultType = 0; // 0. Weather; 1. Forecast
// bool isMetric = true;
string url;
string fileName = "testFiles/testFile.txt";
bool curlError = false;

// Functions declaration
size_t curlCallback(void *contents, size_t unitsize, size_t qty, void *userp);
void urlConstruction();
void curlStart();
void resultsDisplay();

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    urlConstruction();
    curlStart();
    if (curlError)
    {
        system("pause");
        return 1;
    }
    else
    {
        resultsDisplay();
        system("pause");
        return 0;
    }
}

// Functions definition
size_t curlCallback(void *contents, size_t unitsize, size_t qty, void *userp)
{
    size_t realsize = unitsize * qty;            // realsize stores full processed data size
    auto *buffer = static_cast<string *>(userp); // *buffer stores string casted *userp
    auto *data = static_cast<char *>(contents);  // *data stores char casted *contents
    buffer->append(data, realsize);              // Add the amount of characters of data, indicated by realsize. Stored in api_response

    return realsize;
}

void urlConstruction()
{
    // API-related variables declaration
    string url_base = "https://api.openweathermap.org/data/2.5/";
    string url_appid = "&appid=" + OPENWEATHERMAP_API_KEY;
    string url_mode;
    string url_consultType;
    string url_units;

    // TO-DO: Append user-typed input. For City Name + Country Code, start append with ","
    // For testing purposes, appending will happen inside the switch block. Pending definitive structure
    // Recommendation: check for numbers-only input for ID
    // Going to set to "maturin", "maturin,ve" and "3778045" as placeholders

    switch (mode)
    {
    case 0:
        // City Name
        url_mode = "?q=";
        url_mode.append("maturin");
        break;

    case 1:
        // City Name + Country Code
        url_mode = "?q=";
        url_mode.append("maturin,ve");
        break;

    case 2:
        // ID
        url_mode = "?id=";
        url_mode.append("3778045");
        break;

    default:
        // Return error
        break;
    }

    switch (consultType)
    {
    case 0:
        // Weather
        url_consultType = "weather";
        break;

    case 1:
        // Forecast
        url_consultType = "forecast";
        break;

    default:
        // Return error
        break;
    }

    isMetric ? url_units = "&units=metric" : url_units = "&units=imperial";

    /*Se necesita:
    - Clima actual (weather)
    - pronóstico para los próximos 5 días, cada 3 horas (forecast)
    - búsqueda por nombre ([?q={city name}][?q={city name},{country code}])
    - búsqueda por id (?id={city id})
    - selector de unidades (&units={[metric][imperial]})
    - selector de idioma (&lang={language})
    - establecimiento de la api (&appid={API key})
    - integración con la api de geocoding
    - pensar si se van a pedir primero los detalles o el tipo de consulta
    - pensar si la api de geocoding va aparte
    */

    // url should be constructed depending on several parameters. Set url = url_base ase a placeholder
    url = url_base + url_consultType + url_mode + url_units + url_appid;
}

void curlStart()
{
    // cURL variables declaration
    CURL *curl;
    CURLcode res;
    string api_response;

    // cURL start
    curl = curl_easy_init();
    if (curl)
    {
        // These options set: the URL from which the data will be downloaded; callback function; and variable where data will be stored
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &api_response);

        res = curl_easy_perform(curl);
        // If the executing cURL operation was successful, writes a file with the downloaded data
        if (res == CURLE_OK)
        {
            ofstream fileWrite(fileName);
            if (fileWrite.is_open())
            {
                fileWrite << api_response;
                fileWrite.close();
            }
        }
        else
        {
            cerr << "cURL failed.\n";
            cerr << "Error: " << curl_easy_strerror(res) << "\n\n";
            curlError = true;
        }
    }
    curl_easy_cleanup(curl);
}

void resultsDisplay()
{
    string read;

    ifstream fileRead(fileName);
    if (fileRead.is_open())
    {
        while (fileRead >> read)
        {
            getline(fileRead, read);
            cout << read << "\n\n";
        }
        fileRead.close();
    }
}
