#pragma once
#include <string>

size_t curlCallback(void* contents, size_t unitsize, size_t qty, void* userp);
void curlStart(std::string url);
