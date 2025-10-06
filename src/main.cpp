// Custom headers
#include "../lib/apiFunctions.hpp"
#include "../lib/curlFunctions.hpp"
#include "../lib/otherFunctions.hpp"
#include "../lib/globals.hpp"
#include "../lib/menuSystem.hpp"

// Standard headers
#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	initialConfigRead();
	intro();
	return curlOK ? 0 : 1;
}
