#include "lib/curl/curl.h"
#include "lib/json.hpp"
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;
using json = nlohmann::json;

// API key: 6a23773c0153f0beac3cf62e6df26495
// Compile: g++ main.cpp -o main.exe -lcurl

// Global variables declaration
string url;
string fileName = "testFile.txt";

// Function declaration
size_t curlCallback(void *contents, size_t unitsize, size_t qty, void *userp);
void urlConstruction();
bool curlStart();
void resultsDisplay();

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    urlConstruction();
    curlStart();
    if (!curlStart())
    {
        resultsDisplay();
        system("pause");

        return 0;
    }
    else
    {
        system("pause");
        return 1;
    }
}

// Function definition
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
    string base_url = "https://www.example.com";

    // url should be constructed depending on several parameters. Set url = base_url ase a placeholder
    url = base_url;
}

bool curlStart()
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
            return true;
        }

        // Final cURL handle cleanup
        curl_easy_cleanup(curl);
    }
    return false;
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
