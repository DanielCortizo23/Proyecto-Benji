#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Jugador.h"
using namespace std;

class Equipo {
    private:
        string nombre;
        string categoria;
        vector<Jugador> roster;

        // Metodos auxiliares de ordenamiento y busqueda recursiva
        void mezclar(int, int, int);
        void merge_sort(int, int);
        int busqueda_binaria_rec(int, int, int);

    public:
        Equipo();
        Equipo(string, string);

        string get_nombre();
        string get_categoria();

        void set_nombre(string);
        void set_categoria(string);

        void registrar_jugador(const Jugador&);
        void cargar_desde_txt(string);

        // Algoritmos de la rubrica
        void ordenar_por_remate();             // Merge Sort O(n log n)
        int buscar_por_id(int);                // Busqueda Binaria O(log n)
        void filtrar_por_posicion(string);     // Busqueda Secuencial O(n)
        double promedio_altura_bloqueo();      // Funcion Iterativa O(n)

        void mostrar_roster();
        void mostrar_resumen_jugadores();
};

Equipo::Equipo() {
    nombre = "";
    categoria = "";
}

Equipo::Equipo(string name, string cat) {
    nombre = name;
    categoria = cat;
}

string Equipo::get_nombre() {
    return nombre;
}

string Equipo::get_categoria() {
    return categoria;
}

void Equipo::set_nombre(string name) {
    nombre = name;
}

void Equipo::set_categoria(string cat) {
    categoria = cat;
}

void Equipo::registrar_jugador(const Jugador& nuevo) {
    roster.push_back(nuevo);
}

// Lectura de archivo txt
void Equipo::cargar_desde_txt(string ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "\nAviso: No se encontro el archivo " << ruta << ", usando registro manual." << endl;
        return;
    }

    int id, block, spike, pts, err;
    string name, pos;

    while (archivo >> id >> name >> pos >> block >> spike >> pts >> err) {
        roster.push_back(Jugador(id, name, pos, block, spike, pts, err));
    }
    archivo.close();
}

// Funcion Iterativa: O(n)
double Equipo::promedio_altura_bloqueo() {
    if (roster.size() == 0) {
        return 0.0;
    }

    double suma = 0.0;
    for (size_t i = 0; i < roster.size(); i++) {
        suma = suma + roster[i].get_bloqueo();
    }
    return suma / roster.size();
}

// Merge Sort: mezcla O(n)
void Equipo::mezclar(int inicio, int medio, int fin) {
    int i = inicio;
    int j = medio + 1;
    vector<Jugador> temp;

    // Ordenar de mayor a menor por alcance de remate
    while (i <= medio && j <= fin) {
        if (roster[i].get_remate() >= roster[j].get_remate()) {
            temp.push_back(roster[i]);
            i++;
        } else {
            temp.push_back(roster[j]);
            j++;
        }
    }

    while (i <= medio) {
        temp.push_back(roster[i]);
        i++;
    }

    while (j <= fin) {
        temp.push_back(roster[j]);
        j++;
    }

    for (size_t k = 0; k < temp.size(); k++) {
        roster[inicio + k] = temp[k];
    }
}

// Merge Sort recursivo: O(n log n)
void Equipo::merge_sort(int inicio, int fin) {
    if (inicio < fin) {
        int medio = (inicio + fin) / 2;
        merge_sort(inicio, medio);
        merge_sort(medio + 1, fin);
        mezclar(inicio, medio, fin);
    }
}

void Equipo::ordenar_por_remate() {
    if (!roster.empty()) {
        merge_sort(0, roster.size() - 1);
    }
}

// Busqueda Binaria recursiva: O(log n)
int Equipo::busqueda_binaria_rec(int inicio, int fin, int id_buscado) {
    if (inicio > fin) {
        return -1; // No encontrado
    }

    int medio = (inicio + fin) / 2;

    if (roster[medio].get_id() == id_buscado) {
        return medio;
    }

    if (id_buscado < roster[medio].get_id()) {
        return busqueda_binaria_rec(inicio, medio - 1, id_buscado);
    } else {
        return busqueda_binaria_rec(medio + 1, fin, id_buscado);
    }
}

int Equipo::buscar_por_id(int id_buscado) {
    // Ordenamos por ID de forma sencilla para garantizar la condicion de busqueda binaria
    for (size_t i = 0; i < roster.size(); i++) {
        for (size_t j = 0; j + 1 < roster.size(); j++) {
            if (roster[j].get_id() > roster[j + 1].get_id()) {
                swap(roster[j], roster[j + 1]);
            }
        }
    }
    return busqueda_binaria_rec(0, roster.size() - 1, id_buscado);
}

// Busqueda Secuencial: O(n)
void Equipo::filtrar_por_posicion(string pos_buscada) {
    cout << "\nJugadores en la posicion: " << pos_buscada << endl;
    int encontrados = 0;
    for (size_t i = 0; i < roster.size(); i++) {
        if (roster[i].get_posicion() == pos_buscada) {
            roster[i].mostrar_resumen();
            encontrados++;
        }
    }
    if (encontrados == 0) {
        cout << "No se encontraron jugadores en esa posicion." << endl;
    }
}

void Equipo::mostrar_roster() {
    cout << "\nEquipo: " << nombre << " (" << categoria << ")" << endl;
    if (roster.size() == 0) {
        cout << "El roster esta vacio." << endl;
    } else {
        for (size_t i = 0; i < roster.size(); i++) {
            roster[i].mostrar_info_completa();
        }
    }
}

void Equipo::mostrar_resumen_jugadores() {
    cout << "\nEquipo: " << nombre << " (" << categoria << ")" << endl;
    if (roster.size() == 0) {
        cout << "El roster esta vacio." << endl;
    } else {
        for (size_t i = 0; i < roster.size(); i++) {
            roster[i].mostrar_resumen();
        }
    }
}

#endif