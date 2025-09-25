// Custom headers
#include "lib/curlFunctions.hpp"
#include "lib/initialConfigRead.hpp"
#include "lib/menuSystem.hpp"

// 3rd-party headers
#include "lib/curl/curl.h"
#include "lib/json.hpp"

// Standard headers
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;
using json = nlohmann::json;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    initialConfigRead();
    intro();
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
    */

    /*
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
    Al ver el clima o el pronóstico de una ubicación, permitir pasar a la otra opción dinámicamente
    Agregar weather/forecast a la lista de opciones
    GUARDAR LA ID COMO "ÚLTIMA CONSULTA", LPM SOY UN GENIO
    */
