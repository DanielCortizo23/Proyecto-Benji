#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Jugador.h"
using namespace std;

// Clase Equipo
class Equipo {
    private:
        string nombre;
        string categoria;
        vector<Jugador> roster;

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
        
        // Archivos de texto 
        void cargar_desde_txt(string);
        void guardar_en_txt(string);

        void ordenar_por_remate();             // Merge Sort O(n log n)
        int buscar_por_id(int);                // Busqueda Binaria O(log n)
        void filtrar_por_posicion(string);     // Busqueda Secuencial O(n)
        double promedio_altura_bloqueo();      // Funcion Iterativa O(n)

        void mostrar_roster();
        void mostrar_resumen_jugadores();
};

// Desarrollo de los métodos
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

// Lectura de archivos
void Equipo::cargar_desde_txt(string ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "\nAviso: No se encontro el archivo " << ruta << endl;
        return;
    }

    roster.clear();
    int id, block, spike, pts, err;
    string name, pos;

    while (archivo >> id >> name >> pos >> block >> spike >> pts >> err) {
        roster.push_back(Jugador(id, name, pos, block, spike, pts, err));
    }
    archivo.close();
    cout << "\nDatos cargados con exito desde " << ruta << " (" << roster.size() << " jugadores)." << endl;
}

// Escritura de archivos
void Equipo::guardar_en_txt(string ruta) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "\nError al abrir archivo para guardar." << endl;
        return;
    }

    for (size_t i = 0; i < roster.size(); i++) {
        archivo << roster[i].get_id() << " "
                << roster[i].get_nombre() << " "
                << roster[i].get_posicion() << " "
                << roster[i].get_bloqueo() << " "
                << roster[i].get_remate() << " "
                << roster[i].get_ataques() << " "
                << roster[i].get_errores() << "\n";
    }
    archivo.close();
    cout << "\nDatos guardados correctamente en " << ruta << endl;
}

// Función Iterativa
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

// Merge Sort
void Equipo::mezclar(int inicio, int medio, int fin) {
    int i = inicio;
    int j = medio + 1;
    vector<Jugador> temp;

    // Ordenar de mayor a menor según alcance de remate
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

// Merge Sort recursivo O(n log n)
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

// Búsqueda Binaria recursiva O(log n)
int Equipo::busqueda_binaria_rec(int inicio, int fin, int id_buscado) {
    if (inicio > fin) {
        return -1;
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
    // Ordenamos por ID para asegurar la precondición de búsqueda binaria
    for (size_t i = 0; i < roster.size(); i++) {
        for (size_t j = 0; j + 1 < roster.size(); j++) {
            if (roster[j].get_id() > roster[j + 1].get_id()) {
                swap(roster[j], roster[j + 1]);
            }
        }
    }
    return busqueda_binaria_rec(0, roster.size() - 1, id_buscado);
}

// Búsqueda Secuencial O(n)
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
