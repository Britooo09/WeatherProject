// Custom headers
#include "lib/curlFunctions.hpp"
#include "lib/globals.hpp"

// 3rd party headers
#include "lib/json.hpp"
#include <curl/curl.h>

// Standard headers
#include <iostream>
#include <fstream>

using std::cerr;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;
using json = nlohmann::json;

// Functions definition
size_t curlCallback(void* contents, size_t unitsize, size_t qty, void* userp)
{
	size_t realsize = unitsize * qty;			// realsize stores full processed data size
	auto* buffer = static_cast<string*>(userp);	// *buffer stores string casted *userp
	auto* data = static_cast<char*>(contents);	// *data stores char casted *contents
	buffer->append(data, realsize);				// Add the amount of characters of data, indicated by realsize. Stored in api_response

	return realsize;
}

void curlStart(string url)
{
	// cURL variables declaration
	CURL* curl;
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
