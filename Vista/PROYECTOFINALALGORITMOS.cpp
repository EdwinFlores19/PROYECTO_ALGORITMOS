#pragma once
#include <iostream>
#include "../Controlador/ControladorSede.h"
#include "../Controlador/ControladorCarga.h"
// #include "Sede.h"
using namespace std;

int main()
{
    ControladorSede controlS;
    CargaDatos cargar;
    cargar.cargarSedes(controlS);
    // cargar.cargarAristas(controlS);

    string inicio, destino;
    vector<ControladorSede::Sede *> caminoMasCorto;
    char opt;
    string sede, sd1, sd2;

    do
    {
        system("cls");
        cout << "\n\tMENU" << endl;
        cout << "\ta) Ingresar nueva sede" << endl;
        cout << "\tb) Agregar Camino" << endl;
        cout << "\tc) Imprimir los caminos" << endl;
        cout << "\td) Encontrar camino mas corto" << endl;
        cout << "\te) Grafo por defecto " << endl;
        cout << "\tf) Guardar datos" << endl;
        cout << "\tg) Salir" << endl;
        cout << "\tIngresar opcion: ";
        cin >> opt;

        switch (opt)
        {
        case 'a':
            cout << "\n\tIngrese una nueva Sede: ";
            cin >> sede;
            controlS.addSede(sede);
            cout << "\n\tSe ha agregado exitosamente!!!!" << endl;
            system("pause");
            break;

        case 'b':
            int tmp;
            cout << "\n\tIngrese la sede inicial: ";
            cin >> sd1;
            cout << "\tIngrese la sede destino: ";
            cin >> sd2;
            cout << "\tIngrese el tiempo que toma: ";
            cin >> tmp;
            controlS.addArista(controlS.buscarNodo(sd1), controlS.buscarNodo(sd2), tmp);
            system("pause");
            break;

        case 'c':
            cout << "\n\tGrafo: ";
            // controlS.imprimirGrafo();
            controlS.imprimirSede();
            system("pause");
            break;

        case 'd':
            cout << "\n\tIngrese la sede de inicio: ";
            cin >> inicio;
            cout << "\tIngrese la sede de destino: ";
            cin >> destino;

            caminoMasCorto = controlS.encontrarCaminoMasCorto(inicio, destino);

            if (!caminoMasCorto.empty())
            {
                cout << "\n\tEl camino más corto desde " << inicio << " hasta " << destino << " es:" << endl;
                for (ControladorSede::Sede *sede : caminoMasCorto)
                {
                    cout << "\t" << sede->nom << endl;
                }
            }
            else
            {
                cout << "\n\tNo se encontró un camino válido desde " << inicio << " hasta " << destino << endl;
            }

            system("pause");
            break;

        case 'e':
            controlS.addSede("A");
            controlS.addSede("B");
            controlS.addSede("C");
            controlS.addSede("D");
            controlS.addSede("E");
            controlS.addArista(controlS.buscarNodo("A"), controlS.buscarNodo("B"), 5);
            controlS.addArista(controlS.buscarNodo("B"), controlS.buscarNodo("C"), 10);
            controlS.addArista(controlS.buscarNodo("C"), controlS.buscarNodo("D"), 20);
            controlS.addArista(controlS.buscarNodo("A"), controlS.buscarNodo("D"), 40);
            controlS.addArista(controlS.buscarNodo("A"), controlS.buscarNodo("E"), 20);
            controlS.addArista(controlS.buscarNodo("E"), controlS.buscarNodo("D"), 30);
            system("pause");
            break;
        case 'f':
            controlS.guardarSedes();
            controlS.guardarCaminos();
            system("pause");
            break;
        case 'g':
            break;
        default:
            cout << opt << " No existe esa opción. Vuelva a ingresar un número." << endl;
        }
    } while (opt != 'g');

    return 0;
}
