#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <string>
using namespace std;

// Clase que modela a un jugador de voleibol y sus estadisticas
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

        int calcular_efectividad();
        void mostrar_info_completa();
        void mostrar_resumen();
};

// Desarrollo de los metodos

// Constructor por omision, Complejidad Temporal: O(1)
Jugador::Jugador() {
    id = 0;
    nombre = "";
    posicion = "";
    bloqueo = 0;
    remate = 0;
    ataques = 0;
    errores = 0;
}

// Constructor con parametros, Complejidad Temporal: O(1)
Jugador::Jugador(int code, string name, string pos, int block, int spike, int pts, int err) {
    id = code;
    nombre = name;
    posicion = pos;
    bloqueo = block;
    remate = spike;
    ataques = pts;
    errores = err;
}

// Getter de ID, Complejidad Temporal: O(1)
int Jugador::get_id() {
    return id;
}

// Getter de nombre, Complejidad Temporal: O(1)
string Jugador::get_nombre() {
    return nombre;
}

// Getter de posicion, Complejidad Temporal: O(1)
string Jugador::get_posicion() {
    return posicion;
}

// Getter de alcance de bloqueo, Complejidad Temporal: O(1)
int Jugador::get_bloqueo() {
    return bloqueo;
}

// Getter de alcance de remate, Complejidad Temporal: O(1)
int Jugador::get_remate() {
    return remate;
}

// Getter de ataques efectivos, Complejidad Temporal: O(1)
int Jugador::get_ataques() {
    return ataques;
}

// Getter de errores cometidos, Complejidad Temporal: O(1)
int Jugador::get_errores() {
    return errores;
}

// Setter de ID, Complejidad Temporal: O(1)
void Jugador::set_id(int code) {
    id = code;
}

// Setter de nombre, Complejidad Temporal: O(1)
void Jugador::set_nombre(string name) {
    nombre = name;
}

// Setter de posicion, Complejidad Temporal: O(1)
void Jugador::set_posicion(string pos) {
    posicion = pos;
}

// Setter de alcance de bloqueo, Complejidad Temporal: O(1)
void Jugador::set_bloqueo(int block) {
    bloqueo = block;
}

// Setter de alcance de remate, Complejidad Temporal: O(1)
void Jugador::set_remate(int spike) {
    remate = spike;
}

// Setter de ataques efectivos, Complejidad Temporal: O(1)
void Jugador::set_ataques(int pts) {
    ataques = pts;
}

// Setter de errores cometidos, Complejidad Temporal: O(1)
void Jugador::set_errores(int err) {
    errores = err;
}

// Calcula los puntos netos de ataque (operacion directa), Complejidad Temporal: O(1)
int Jugador::calcular_efectividad() {
    return ataques - errores;
}

// Despliega todos los atributos y la efectividad del jugador, Complejidad Temporal: O(1)
void Jugador::mostrar_info_completa() {
    cout << "\nID: " << id << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Posicion: " << posicion << endl;
    cout << "Alcance Bloqueo: " << bloqueo << " cm" << endl;
    cout << "Alcance Remate: " << remate << " cm" << endl;
    cout << "Efectividad Ataque: " << calcular_efectividad() << " pts netos" << endl;
}

// Despliega un resumen breve del jugador, Complejidad Temporal: O(1)
void Jugador::mostrar_resumen() {
    cout << "\n" << nombre << " (" << posicion << ") - Remate: " << remate 
         << " cm | Bloqueo: " << bloqueo << " cm" << endl;
}

#endif
