#include "lib/curl/curl.h"
#include "lib/json.hpp"
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;
using json = nlohmann::json;

// API key: 6a23773c0153f0beac3cf62e6df26495
// Compile: g++ weatherTest_lcurl.cpp -o weatherTest_lcurl.exe -lcurl

// Function declaration
size_t curlCallback(void *contents, size_t unitsize, size_t qty, void *userp);
void curlStart();

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    curlStart();
    
    return 0;
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

void curlStart() {

}
