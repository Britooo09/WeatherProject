#include "../lib/curlFunctions.hpp"
#include "../lib/globals.hpp"
#include <curl/curl.h>
#include <iostream>
#include <fstream>

size_t curlCallback(void* contents, size_t unitsize, size_t qty, void* userp)
{
	size_t realsize = unitsize * qty;					// realsize stores full processed data size
	auto* buffer = static_cast<std::string*>(userp);	// *buffer stores string casted *userp
	auto* data = static_cast<char*>(contents);			// *data stores char casted *contents
	buffer->append(data, realsize);						// Add the amount of characters of data, indicated by realsize. Stored in api_response

	return realsize;
}

void curlStart(std::string url)
{
	// cURL variables declaration
	CURL* curl;
	CURLcode res;
	std::string api_response;

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
			std::ofstream fileWrite(fileName);
			if (fileWrite.is_open())
			{
				fileWrite << api_response;
				fileWrite.close();
			}
			curlOK = true;
		}

		else
		{
			std::cerr << "\ncURL failed.\n";
			std::cerr << "Error: " << curl_easy_strerror(res) << "\n";
			std::cerr << "Returning to main menu...\n\n";
			curlOK = false;
			system("pause");
		}
	}
	curl_easy_cleanup(curl);
}
