#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../Controlador/ControladorSede.h"
using namespace std;
class CargaDatos
{
public:
	void cargarSedes(ControladorSede &controlador)
	{
		ifstream archivo("Sedes.txt");
		if (!archivo)
		{
			cout << "\n\tNo se pudo abrir el archivo." << endl;
			return;
		}

		string linea;
		while (getline(archivo, linea))
		{
			if (linea.find("Sede:") != string::npos)
			{
				string nombreSede = linea.substr(linea.find(":") + 2);
				controlador.addSede(nombreSede);
			}
		}
		archivo.close();
		// cout << "\n\tDatos cargados exitosamente desde Sedes.txt" << endl;
	}
	void cargarAristas(ControladorSede &controlador)
	{
		ifstream archivo("Caminos.txt");
		if (!archivo)
		{
			cout << "\n\tNo se pudo abrir el archivo." << endl;
			return;
		}
		string linea;

		while (getline(archivo, linea))
		{
			if (linea.find(""))
			{
			}
		}

		archivo.close();
	}
	void trim(string &str)
	{
		// Eliminar espacios al inicio
		size_t inicio = str.find_first_not_of(" ");
		if (inicio != string::npos)
		{
			str = str.substr(inicio);
		}
		else
		{
			str.clear();
			return;
		}

		// Eliminar espacios al final
		size_t fin = str.find_last_not_of(" ");
		if (fin != string::npos)
		{
			str = str.substr(0, fin + 1);
		}
		else
		{
			str.clear();
		}
	}
};