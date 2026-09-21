#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <string>
using namespace std;

class Jugador {
    private:
        int id;
        string nombre;
        string posicion;
        int bloqueo;  // Alcance en cm
        int remate;   // Alcance en cm
        int ataques;  // Ataques efectivos
        int errores;  // Errores cometidos

    public:
        Jugador();
        Jugador(int, string, string, int, int, int, int);

        int get_id();
        string get_nombre();
        string get_posicion();
        int get_bloqueo();
        int get_remate();
        int get_ataques();
        int get_errores();

        void set_id(int);
        void set_nombre(string);
        void set_posicion(string);
        void set_bloqueo(int);
        void set_remate(int);
        void set_ataques(int);
        void set_errores(int);

        // Funcion Directa: O(1)
        int calcular_efectividad();

        void mostrar_info_completa();
        void mostrar_resumen();
};

Jugador::Jugador() {
    id = 0;
    nombre = "";
    posicion = "";
    bloqueo = 0;
    remate = 0;
    ataques = 0;
    errores = 0;
}

Jugador::Jugador(int code, string name, string pos, int block, int spike, int pts, int err) {
    id = code;
    nombre = name;
    posicion = pos;
    bloqueo = block;
    remate = spike;
    ataques = pts;
    errores = err;
}

int Jugador::get_id() {
    return id;
}

string Jugador::get_nombre() {
    return nombre;
}

string Jugador::get_posicion() {
    return posicion;
}

int Jugador::get_bloqueo() {
    return bloqueo;
}

int Jugador::get_remate() {
    return remate;
}

int Jugador::get_ataques() {
    return ataques;
}

int Jugador::get_errores() {
    return errores;
}

void Jugador::set_id(int code) {
    id = code;
}

void Jugador::set_nombre(string name) {
    nombre = name;
}

void Jugador::set_posicion(string pos) {
    posicion = pos;
}

void Jugador::set_bloqueo(int block) {
    bloqueo = block;
}

void Jugador::set_remate(int spike) {
    remate = spike;
}

void Jugador::set_ataques(int pts) {
    ataques = pts;
}

void Jugador::set_errores(int err) {
    errores = err;
}

// Funcion Directa: O(1)
int Jugador::calcular_efectividad() {
    return ataques - errores;
}

void Jugador::mostrar_info_completa() {
    cout << "\nID: " << id << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Posicion: " << posicion << endl;
    cout << "Alcance Bloqueo: " << bloqueo << " cm" << endl;
    cout << "Alcance Remate: " << remate << " cm" << endl;
    cout << "Efectividad Ataque: " << calcular_efectividad() << " pts netos" << endl;
}

void Jugador::mostrar_resumen() {
    cout << "\n" << nombre << " (" << posicion << ") - Remate: " << remate 
         << " cm | Bloqueo: " << bloqueo << " cm" << endl;
}

#endif