#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Jugador.h"

using namespace std;

// Nodo para la Lista Doblemente Ligada
class NodoTitular {
    private:
        string value;
        NodoTitular* previous;
        NodoTitular* next;

        NodoTitular(string val) : value(val), previous(0), next(0) {}

        friend class Equipo;
};

class Equipo {
    private:
        string nombre;
        string categoria;
        vector<Jugador> roster;

        // Punteros de la Lista Doblemente Ligada de titulares
        NodoTitular *head;
        NodoTitular *tail;
        int size_titulares;

        void mezclar(int, int, int);
        void merge_sort(int, int);
        void mezclar_id(int, int, int);
        void merge_sort_id(int, int);
        int busqueda_binaria_rec(int, int, int);

    public:
        Equipo();
        Equipo(string, string);
        ~Equipo();

        string get_nombre();
        string get_categoria();

        void set_nombre(string);
        void set_categoria(string);

        void registrar_jugador(const Jugador&);
        
        void cargar_desde_txt(string);
        void guardar_en_txt(string);

        void ordenar_por_remate();             
        int buscar_por_id(int);                
        void filtrar_por_posicion(string);     
        double promedio_altura_bloqueo();      

        void mostrar_roster();
        void mostrar_resumen_jugadores();

        // Metodos de la Lista Doblemente Ligada 
        bool titulares_empty() const;
        void limpiar_titulares();
        void insertar_titular(string);
        int buscar_titular(string) const;
        void eliminar_titular_en(int);
        string titulares_forward() const;
        string titulares_backward() const;

        // Funciones conectadas al menu
        void agregar_titular_por_id(int);
        void quitar_titular(string);
        void mostrar_titulares();
};

Equipo::Equipo() {
    nombre = "";
    categoria = "";
    head = 0;
    tail = 0;
    size_titulares = 0;
}

Equipo::Equipo(string name, string cat) {
    nombre = name;
    categoria = cat;
    head = 0;
    tail = 0;
    size_titulares = 0;
}

Equipo::~Equipo() {
    limpiar_titulares();
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


// MERGE SORT (Ordenar por remate)
// Complejidad Temporal: O(n log n)
// Complejidad Espacial: O(n)

void Equipo::mezclar(int inicio, int medio, int fin) {
    int i = inicio;
    int j = medio + 1;
    vector<Jugador> temp;

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

void Equipo::mezclar_id(int inicio, int medio, int fin) {
    int i = inicio;
    int j = medio + 1;
    vector<Jugador> temp;

    while (i <= medio && j <= fin) {
        if (roster[i].get_id() <= roster[j].get_id()) {
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

void Equipo::merge_sort_id(int inicio, int fin) {
    if (inicio < fin) {
        int medio = (inicio + fin) / 2;
        merge_sort_id(inicio, medio);
        merge_sort_id(medio + 1, fin);
        mezclar_id(inicio, medio, fin);
    }
}
 
// BUSQUEDA BINARIA RECURSIVA POR ID
// Complejidad Temporal: O(log n)
// Complejidad Espacial: O(log n) por la pila de recursión

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
    if (!roster.empty()) {
        merge_sort_id(0, roster.size() - 1);
    }
    return busqueda_binaria_rec(0, roster.size() - 1, id_buscado);
}

void Equipo::filtrar_por_posicion(string pos_buscada) {
    cout << "\n--- Jugadores en la posicion: " << pos_buscada << " ---" << endl;
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
    cout << "\n" << endl;
    cout << "Equipo: " << nombre << " (" << categoria << ")" << endl;
    cout << "-------------------" << endl;
    if (roster.size() == 0) {
        cout << "El roster esta vacio." << endl;
    } else {
        for (size_t i = 0; i < roster.size(); i++) {
            roster[i].mostrar_info_completa();
        }
    }
}

void Equipo::mostrar_resumen_jugadores() {
    cout << "\n" << endl;
    cout << "Equipo: " << nombre << " (" << categoria << ")" << endl;
    cout << "----------------" << endl;
    if (roster.size() == 0) {
        cout << "El roster esta vacio." << endl;
    } else {
        for (size_t i = 0; i < roster.size(); i++) {
            roster[i].mostrar_resumen();
        }
    }
}

 
// IMPLEMENTACION DE LA LISTA DOBLEMENTE LIGADA (Titulares)


// Verificar si está vacía -> O(1)
bool Equipo::titulares_empty() const {
    return (head == 0);
}

// Limpiar/Vaciar lista -> O(n)
void Equipo::limpiar_titulares() {
    NodoTitular *p = head;
    NodoTitular *q;

    while (p != 0) {
        q = p->next;
        delete p;
        p = q;
    }

    head = 0;
    tail = 0;
    size_titulares = 0;
}

// Insertar al final usando el puntero tail -> O(1)
void Equipo::insertar_titular(string val) {
    NodoTitular *newLink = new NodoTitular(val);

    if (titulares_empty()) {
        head = newLink;
        tail = newLink;
    } else {
        tail->next = newLink;
        newLink->previous = tail;
        tail = newLink;
    }
    size_titulares++;
}

// Buscar elemento en la lista -> O(n)
int Equipo::buscar_titular(string val) const {
    NodoTitular *p = head;
    int index = 0;

    while (p != 0) {
        if (p->value == val) {
            return index;
        }
        p = p->next;
        index++;
    }
    return -1;
}

// Eliminar elemento por índice -> O(n)
void Equipo::eliminar_titular_en(int index) {
    if (index < 0 || index >= size_titulares) {
        return;
    }
    NodoTitular *p;

    if (index == 0) {
        p = head;
        if (head == tail) {
            head = 0;
            tail = 0;
        } else {
            head = head->next;
            head->previous = 0;
        }
        delete p;
    } else if (index == size_titulares - 1) {
        p = tail;
        tail = tail->previous;
        tail->next = 0;
        delete p;
    } else {
        p = head;
        int pos = 0;
        while (pos != index) {
            p = p->next;
            pos++;
        }
        p->previous->next = p->next;
        p->next->previous = p->previous;
        delete p;
    }

    size_titulares--;
}

// Recorrido Forward (Normal) -> O(n)
string Equipo::titulares_forward() const {
    stringstream aux;
    NodoTitular *p = head;

    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->next != 0) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

// Recorrido Backward (Inverso) -> O(n)
string Equipo::titulares_backward() const {
    stringstream aux;
    NodoTitular *p = tail;

    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->previous != 0) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}

void Equipo::agregar_titular_por_id(int id_buscado) {
    int pos = buscar_por_id(id_buscado);
    if (pos == -1) {
        cout << "\nNo existe ningun jugador con el ID " << id_buscado << "." << endl;
        return;
    }

    string nombre_jug = roster[pos].get_nombre();
    if (buscar_titular(nombre_jug) != -1) {
        cout << "\nEl jugador " << nombre_jug << " ya esta en la lista de titulares." << endl;
        return;
    }

    insertar_titular(nombre_jug);
    cout << "\nJugador " << nombre_jug << " agregado a la lista de titulares." << endl;
}

void Equipo::quitar_titular(string nombre_jug) {
    int index = buscar_titular(nombre_jug);
    if (index == -1) {
        cout << "\nEl jugador " << nombre_jug << " no se encuentra en la lista de titulares." << endl;
    } else {
        eliminar_titular_en(index);
        cout << "\nJugador " << nombre_jug << " eliminado de la lista de titulares." << endl;
    }
}

void Equipo::mostrar_titulares() {
    cout << "\n--- ALINEACION TITULAR (Lista Doblemente Ligada) ---" << endl;
    if (titulares_empty()) {
        cout << "La lista de titulares esta vacia." << endl;
    } else {
        cout << "Orden de rotacion (Forward):  " << titulares_forward() << endl;
        cout << "Orden inverso (Backward):     " << titulares_backward() << endl;
    }
}

#endif
