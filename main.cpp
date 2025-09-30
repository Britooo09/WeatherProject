// Custom headers
#include "lib/apiFunctions.hpp"
#include "lib/curlFunctions.hpp"
#include "lib/initialConfigRead.hpp"
#include "lib/globals.hpp"
#include "lib/menuSystem.hpp"

// Standard headers
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	initialConfigRead();
	intro();
	if (curlError)
	{
		// Behavior if program fails
		system("pause");
		return 1;
	}
	else
	{
		// Behavior if program succeeds
		system("pause");
		return 0;
	}
}

/*
Se necesita:
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

Procedimiento general planeado:
Lista de opciones:
- Consulta rápida
	- Búsqueda por nombre
	- Búsqueda por nombre + código
	- Búsqueda por id
- Búsqueda avanzada
	- Geocoding API
		- Se pide el nombre de la ubicación que se desea consultar
		- Se muestra una lista de opciones sencilla con los datos resultantes de la búsqueda
		- Se permite seleccionar una ubicación para consultar el clima (como en la consulta rápida)
- Ver datos
	- Geocoding API
		- Se pide el nombre de la ubicación que se desea consultar
		- Se muestra una lista de opciones sencilla con los datos resultantes de la búsqueda
		- Se despliega toda la información técnica de la ubicación (los resultados de la misma API)
- Repetir última consulta
Al ver el clima o el pronóstico de una ubicación, permitir pasar a la otra opción dinámicamente
Agregar weather/forecast a la lista de opciones
GUARDAR LA ID COMO "ÚLTIMA CONSULTA", LPM SOY UN GENIO

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
*/
