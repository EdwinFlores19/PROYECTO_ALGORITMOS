#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
//#include "Sede.h"
using namespace std;

class ControladorSede {
public:
    struct Sede;
    struct Arista;

    struct Sede {
        string nom;
        Sede* sgt;
        Arista* primeraArista;
        bool visitado;
        int distancia;
        Sede* anterior;

        Sede(const string& nombre) : nom(nombre), sgt(nullptr), primeraArista(nullptr), visitado(false), distancia(numeric_limits<int>::max()), anterior(nullptr) {}
    };

    struct Arista {
        Sede* destino;
        int peso;
        Arista* sgt;

        Arista(Sede* dest, int p) : destino(dest), peso(p), sgt(nullptr) {}
    };

    Sede* head;
    priority_queue<pair<int, Sede*>, vector<pair<int, Sede*>>, greater<pair<int, Sede*>>> colaPrioridad;

public:
    ControladorSede() : head(nullptr) {}

    void addSede(const string& nombre) {
    	bool esNumero = true;
        for (char c : nombre) {
            if (!isdigit(c)) {
                esNumero = false;
                break;
            }
        }

        if (esNumero) {
            cout << "\n\tEl nombre de la sede no puede ser un numero." << endl;
            string nuevoNombre;
            do {
                cout << "\tIngrese un nuevo nombre para la sede: ";
                cin >> nuevoNombre;
                esNumero = true;
                for (char c : nuevoNombre) {
                    if (!isdigit(c)) {
                        esNumero = false;
                        break;
                    }
                }
            } while (esNumero);
            addSede(nuevoNombre);
            return;
        }

        Sede* sedeExistente = buscarNodo(nombre);
        if (sedeExistente != nullptr) {
            cout << "\n\tYa existe una sede con el nombre ingresado: " << nombre << endl;
            string nuevoNombre;
            do {
                cout << "\tIngrese un nuevo nombre para la sede: ";
                cin >> nuevoNombre;
                sedeExistente = buscarNodo(nuevoNombre);
                if (sedeExistente != nullptr) {
                    cout << "\n\tYa existe una sede con el nombre ingresado: " << nuevoNombre << endl;
                }
            } while (sedeExistente != nullptr);
            addSede(nuevoNombre);
            return;
        }

        Sede* nuevaSede = new Sede(nombre);
        nuevaSede->sgt = head;
        head = nuevaSede;
    }

    void guardarSedes() {		//Esto solo guarda las Sedes
        ofstream archivo("Sedes.txt");

        Sede* sedeActual = head;
        while (sedeActual != nullptr) {
            archivo << "Sede: " << sedeActual->nom << endl;
            sedeActual = sedeActual->sgt;
        }

        archivo.close();
        cout << "\n\tDatos guardados exitosamente en Sedes.txt" << endl;
    }
    void guardarCaminos() {
        ofstream archivo("Caminos.txt");

        Sede* sedeActual = head;
        while (sedeActual != nullptr) {
            Arista* inicio = sedeActual->primeraArista;
            while(inicio != nullptr){
                archivo << "Sede Inicio: " << sedeActual->nom << ", Sede Destino: "<< inicio->destino->nom <<", Distancia: " << inicio->peso << endl;
                inicio = inicio->sgt;
            }
            sedeActual = sedeActual->sgt;
        }
        archivo.close();
        cout << "\n\tDatos guardados exitosamente en Caminos.txt" << endl;
    }

    void addArista(Sede* ini, Sede* dest, int peso) {
        if (ini != nullptr && dest != nullptr) {
            Arista* nuevaArista = new Arista(dest, peso);
            nuevaArista->sgt = ini->primeraArista;
            ini->primeraArista = nuevaArista;
			nuevaArista = new Arista(ini, peso);
            nuevaArista->sgt = dest->primeraArista;
            dest->primeraArista = nuevaArista;
            cout << "\n\tSe agrego exitosamente!!" << endl;
        }
    }

    void imprimirGrafo() {
        Sede* sedeActual = head;
        while (sedeActual != nullptr) {
            Arista* aristaActual = sedeActual->primeraArista;
            while (aristaActual != nullptr) {
                cout << "\tLa sede: " << sedeActual->nom << " está conectada con la sede: " << aristaActual->destino->nom << " con un peso de " << aristaActual->peso << endl;
                aristaActual = aristaActual->sgt;
            }
            sedeActual = sedeActual->sgt;
        }
    }
    void imprimirSede(){
    	Sede* s = head;
    	while(s != nullptr){
    		cout<<"\nLa sede: "<<s->nom;
    		s=s->sgt;
		}
	}

    Sede* buscarNodo(const string& nombre) {
        Sede* sedeActual = head;
        while (sedeActual != nullptr) {
            if (sedeActual->nom == nombre) {
                return sedeActual;
            }
            sedeActual = sedeActual->sgt;
        }
        return nullptr;
    }

    vector<Sede*> encontrarCaminoMasCorto(const string& nombreInicio, const string& nombreDestino) {
        Sede* nodoInicio = buscarNodo(nombreInicio);
        Sede* nodoDestino = buscarNodo(nombreDestino);

        if (nodoInicio == nullptr || nodoDestino == nullptr)

        {
            cout << "\n\tLas sedes ingresadas no existen!!" << endl;
            return {};
        }

        reiniciarNodos();

        nodoInicio->distancia = 0;
        colaPrioridad.push(make_pair(0, nodoInicio));

        while (!colaPrioridad.empty()) {
            Sede* nodoActual = colaPrioridad.top().second;
            colaPrioridad.pop();

            if (nodoActual->visitado) {
                continue;
            }

            nodoActual->visitado = true;

            if (nodoActual == nodoDestino) {
                break;
            }

            Arista* aristaActual = nodoActual->primeraArista;
            while (aristaActual != nullptr) {
                Sede* nodoDestino = aristaActual->destino;
                int pesoArista = aristaActual->peso;
                int distanciaAcumulada = nodoActual->distancia + pesoArista;

                if (distanciaAcumulada < nodoDestino->distancia) {
                    nodoDestino->distancia = distanciaAcumulada;
                    nodoDestino->anterior = nodoActual;
                    colaPrioridad.push(make_pair(distanciaAcumulada, nodoDestino));
                }

                aristaActual = aristaActual->sgt;
            }
        }

        vector<Sede*> caminoMasCorto;
        Sede* nodoActual = nodoDestino;
        while (nodoActual != nullptr) {
            caminoMasCorto.insert(caminoMasCorto.begin(), nodoActual);
            nodoActual = nodoActual->anterior;
        }

        while (!colaPrioridad.empty()) {
            colaPrioridad.pop();
        }

        return caminoMasCorto;
    }

private:
    void reiniciarNodos() {
        Sede* sedeActual = head;
        while (sedeActual != nullptr) {
            sedeActual->visitado = false;
            sedeActual->distancia = numeric_limits<int>::max();
            sedeActual->anterior = nullptr;
            sedeActual = sedeActual->sgt;
        }
    }
};
