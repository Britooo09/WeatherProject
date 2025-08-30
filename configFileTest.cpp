#include "lib/json.hpp"
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;
using json = nlohmann::json;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    ifstream f("config.json");
    json j;

    if (f.is_open())
    {
        j = json::parse(f);
        cout<<"esto es lo que hay en el archivo .json: "<<j<<"\n";
        cout<<"y esto es el valor de \"opt\": "<<j["opt"]<<"\n\n";
        int a = j["opt"];
        cout<<"esto es lo que se guardó en la variable a: "<<a<<"\n\n";
        j["opt"] = a + 1;
        cout<<"esto es lo que hay en el objeto j después de la asignar el nuevo valor: "<<j<<"\n";
        cout<<"y esto es el nuevo valor de \"opt\": "<<j["opt"]<<"\n";
        cout<<"el archivo .json no debería haber cambiado todavía.\n\n";
        f.close();

        ofstream f2("config.json");
        f2 << j;
        f2.close();

        fstream f3("config.json");
        json j2 = json::parse(f3);

        cout<<"el archivo .json ahora sí debería haber cambiado. Este es su contenido: "<<j2<<"\n\n";

        f3.close();
        // cout << "Se pudo abrir el archivo. Esta es la cantidad de veces que has abierto el programa: " << j["opt"] << ".\n\n";
    }

    else
    {
        cout << "No se pudo abrir el archivo. Significa que es la primera vez que abres el programa.\n\n";
        ofstream f("config.json");
        j["opt"] = 1;
        f << j;
    }

    system("pause");
    return 0;
}