#ifndef CURLFUNCTIONS_H
#define CURLFUNCTIONS_H

#include <string>

// Global variables declaration
int mode = 0;        // 0. City Name; 1. City Name + Country Code; 2. ID
std::string url;
std::string fileName = "testFiles/testFile.txt";
bool curlError = false;

// Functions declaration
size_t curlCallback(void *contents, size_t unitsize, size_t qty, void *userp);
void urlConstruction();
void curlStart();
void resultsDisplay();

#endif
