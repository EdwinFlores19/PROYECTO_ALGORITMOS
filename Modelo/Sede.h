#pragma once
#include <iostream>
using namespace std;

class Nodo {
public:

	typedef struct Sede {
		Sede* sgt;
		string nom;
		Sede(string nombre) : nom(nombre) {}
		Sede() {}
	}Sede;
public:
	typedef struct Arista {
		Sede* destino;
		int  peso;
		Sede* inicio;
		Arista* sgt;
		Arista(Sede* dest, int p, Sede* ini) : destino(dest), peso(p), inicio(ini), sgt(NULL) {}
	}Arista;
}; 
