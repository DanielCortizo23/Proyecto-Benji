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
    public:
        string value;
        NodoTitular* previous;
        NodoTitular* next;

        // Constructor, Complejidad Temporal: O(1)
        NodoTitular(string val) {
            value = val;
            previous = 0;
            next = 0;
        }
};

// Nodo para el Arbol Binario de Busqueda (BST) indexado por ID 
class NodoBST {
    public:
        Jugador value;
        NodoBST* left;
        NodoBST* right;

        // Constructor, Complejidad Temporal: O(1)
        NodoBST(Jugador val) : value(val), left(0), right(0) {}

        // Insertar en el BST, Promedio: O(log n), Peor caso: O(n)
        void add(Jugador val) {
            if (val.get_id() < value.get_id()) {
                if (left != 0) {
                    left->add(val);
                } else {
                    left = new NodoBST(val);
                }
            } else if (val.get_id() > value.get_id()) {
                if (right != 0) {
                    right->add(val);
                } else {
                    right = new NodoBST(val);
                }
            }
        }

        // Buscar por ID en el BST, Promedio: O(log n), Peor caso: O(n)
        NodoBST* find(int id_buscado) {
            if (id_buscado == value.get_id()) {
                return this;
            } else if (id_buscado < value.get_id()) {
                if (left != 0) {
                    return left->find(id_buscado);
                }
            } else {
                if (right != 0) {
                    return right->find(id_buscado);
                }
            }
            return 0;
        }

        // Obtener predecesor (mayor del subarbol izquierdo), Promedio: O(log n), Peor caso: O(n)
        NodoBST* predecesor() {
            NodoBST *le = left;

            if (left->right == 0) {
                left = left->left;
                le->left = 0;
                return le;
            }

            NodoBST *parent = left;
            NodoBST *child = left->right;
            while (child->right != 0) {
                parent = child;
                child = child->right;
            }
            parent->right = child->left;
            child->left = 0;
            return child;
        }

        // Eliminar nodo por ID, Promedio: O(log n), Peor caso: O(n)
        void remove(int id_borrar) {
            NodoBST *succ, *old;

            if (id_borrar < value.get_id()) {
                if (left != 0) {
                    if (left->value.get_id() == id_borrar) {
                        old = left;
                        if (old->left != 0 && old->right != 0) {
                            succ = old->predecesor();
                            succ->left = old->left;
                            succ->right = old->right;
                            left = succ;
                        } else if (old->left != 0) {
                            left = old->left;
                        } else {
                            left = old->right;
                        }
                        delete old;
                    } else {
                        left->remove(id_borrar);
                    }
                }
            } else if (id_borrar > value.get_id()) {
                if (right != 0) {
                    if (right->value.get_id() == id_borrar) {
                        old = right;
                        if (old->left != 0 && old->right != 0) {
                            succ = old->predecesor();
                            succ->left = old->left;
                            succ->right = old->right;
                            right = succ;
                        } else if (old->left != 0) {
                            right = old->left;
                        } else {
                            right = old->right;
                        }
                        delete old;
                    } else {
                        right->remove(id_borrar);
                    }
                }
            }
        }

        // Liberar memoria de los hijos, Complejidad Temporal: O(n)
        void removeChilds() {
            if (left != 0) {
                left->removeChilds();
                delete left;
                left = 0;
            }
            if (right != 0) {
                right->removeChilds();
                delete right;
                right = 0;
            }
        }

        // Recorrido Inorder (despliega jugadores ordenados por ID) -> Complejidad Temporal: O(n)
        void inorder() {
            if (left != 0) {
                left->inorder();
            }
            value.mostrar_resumen();
            if (right != 0) {
                right->inorder();
            }
        }

        // Guardar recorrido Inorder en archivo txt -> Complejidad Temporal: O(n)
        void guardar_inorder(ofstream &archivo) {
            if (left != 0) {
                left->guardar_inorder(archivo);
            }
            archivo << value.get_id() << " "
                    << value.get_nombre() << " "
                    << value.get_posicion() << " "
                    << value.get_bloqueo() << " "
                    << value.get_remate() << " "
                    << value.get_ataques() << " "
                    << value.get_errores() << "\n";
            if (right != 0) {
                right->guardar_inorder(archivo);
            }
        }
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

        // Puntero raiz del Arbol Binario de Busqueda (BST)
        NodoBST *root_bst;

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

        void registrar_jugador(Jugador);

        void cargar_desde_txt(string);
        void guardar_en_txt(string);
        void guardar_reporte_txt(string);

        void ordenar_por_remate();
        int buscar_por_id(int);
        void mostrar_jugador_en(int);
        void filtrar_por_posicion(string);
        double promedio_altura_bloqueo();

        void mostrar_roster();
        void mostrar_resumen_jugadores();

        // Metodos de la Lista Doblemente Ligada (Titulares)
        bool titulares_empty() const;
        void limpiar_titulares();
        void insertar_titular(string);
        int buscar_titular(string) const;
        void eliminar_titular_en(int);
        string titulares_forward() const;
        string titulares_backward() const;

        void agregar_titular_por_id(int);
        void quitar_titular(string);
        void mostrar_titulares();

        // Metodos del Arbol Binario de Busqueda (BST por ID)
        bool bst_empty() const;
        void limpiar_bst();
        void insertar_bst(Jugador);
        bool existe_id_bst(int);
        void buscar_en_bst(int);
        void eliminar_de_bst(int);
        void mostrar_ordenados_por_id_bst();
};

// Constructor por omision O(1)
Equipo::Equipo() {
    nombre = "";
    categoria = "";
    head = 0;
    tail = 0;
    size_titulares = 0;
    root_bst = 0;
}

// Constructor con parametros O(1)
Equipo::Equipo(string name, string cat) {
    nombre = name;
    categoria = cat;
    head = 0;
    tail = 0;
    size_titulares = 0;
    root_bst = 0;
}

// Destructor (libera lista doblemente ligada y BST) O(n)
Equipo::~Equipo() {
    limpiar_titulares();
    limpiar_bst();
}

// Getter de nombre O(1)
string Equipo::get_nombre() {
    return nombre;
}

// Getter de categoria O(1)
string Equipo::get_categoria() {
    return categoria;
}

// Setter de nombre O(1)
void Equipo::set_nombre(string name) {
    nombre = name;
}

// Setter de categoria O(1)
void Equipo::set_categoria(string cat) {
    categoria = cat;
}

// Registrar jugador en vector O(1) amortizado y en BST O(log n) promedio / O(n) peor caso
void Equipo::registrar_jugador(Jugador nuevo) {
    roster.push_back(nuevo);
    insertar_bst(nuevo);
}

// Cargar jugadores desde archivo txt hacia el vector y el BST
// Complejidad Temporal: O(n log n) promedio al insertar n nodos en el BST, O(n^2) peor caso
void Equipo::cargar_desde_txt(string ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "\nAviso: No se encontro el archivo " << ruta << endl;
        return;
    }

    roster.clear();
    limpiar_bst();
    int id, block, spike, pts, err;
    string name, pos;

    while (archivo >> id >> name >> pos >> block >> spike >> pts >> err) {
        Jugador nuevo(id, name, pos, block, spike, pts, err);
        roster.push_back(nuevo);
        insertar_bst(nuevo);
    }
    archivo.close();
    cout << "\nDatos cargados con exito desde " << ruta << " (" << roster.size() << " jugadores)." << endl;
}

// Guardar el vector roster en archivo txt, Complejidad Temporal: O(n)
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
    cout << "\nDatos del roster guardados correctamente en " << ruta << endl;
}

// Guardar datos de la Lista Doblemente Ligada y del BST (inorder) en un archivo de reporte
// Complejidad Temporal: O(n)
void Equipo::guardar_reporte_txt(string ruta) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "\nError al crear el archivo de reporte " << ruta << endl;
        return;
    }

    archivo << "REPORTE DEL EQUIPO: " << nombre << " (" << categoria << ")\n";
    archivo << "----------------------\n";
    archivo << "ALINEACION TITULAR (Lista Doblemente Ligada):\n";
    if (titulares_empty()) {
        archivo << "Sin titulares asignados.\n";
    } else {
        archivo << "Rotacion Forward:  " << titulares_forward() << "\n";
        archivo << "Rotacion Backward: " << titulares_backward() << "\n";
    }

    archivo << "\nCATALOGO ORDENADO POR ID (Recorrido Inorder del BST):\n";
    archivo << "ID Nombre Posicion Bloqueo Remate Ataques Errores\n";
    if (!bst_empty()) {
        root_bst->guardar_inorder(archivo);
    } else {
        archivo << "El arbol de jugadores esta vacio.\n";
    }

    archivo.close();
    cout << "\nReporte de estructuras guardado correctamente en " << ruta << endl;
}

// Calcular promedio de altura de bloqueo, Complejidad Temporal: O(n)
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

// MERGE SORT (Ordenar por remate de mayor a menor)
// Complejidad Temporal: O(n log n) en mejor, promedio y peor caso
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


// MERGE SORT AUXILIAR (Ordenar por ID de menor a mayor)
// Complejidad Temporal: O(n log n) en todos los casos
// Complejidad Espacial: O(n)

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
// Complejidad Temporal de busqueda_binaria_rec: O(log n)
// Complejidad Espacial: O(log n) por la pila de recursion

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

// Ordena por ID O(n log n) y luego ejecuta busqueda binaria O(log n), Total: O(n log n)
int Equipo::buscar_por_id(int id_buscado) {
    if (!roster.empty()) {
        merge_sort_id(0, roster.size() - 1);
    }
    return busqueda_binaria_rec(0, roster.size() - 1, id_buscado);
}

// Mostrar informacion de un jugador por indice del vector O(1)
void Equipo::mostrar_jugador_en(int pos) {
    if (pos >= 0 && pos < (int)roster.size()) {
        roster[pos].mostrar_info_completa();
    }
}

// Busqueda secuencial por posicion, Complejidad Temporal: O(n)
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

// Desplegar todos los jugadores con info completa, Complejidad Temporal: O(n)
void Equipo::mostrar_roster() {
    cout << "\nEquipo: " << nombre << " (" << categoria << ")" << endl;
    cout << "-------------------" << endl;
    if (roster.size() == 0) {
        cout << "El roster esta vacio." << endl;
    } else {
        for (size_t i = 0; i < roster.size(); i++) {
            roster[i].mostrar_info_completa();
        }
    }
}

// Desplegar resumen de todos los jugadores, Complejidad Temporal: O(n)
void Equipo::mostrar_resumen_jugadores() {
    cout << "\nEquipo: " << nombre << " (" << categoria << ")" << endl;
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


// Verificar si esta vacia O(1)
bool Equipo::titulares_empty() const {
    return (head == 0);
}

// Limpiar/Vaciar lista O(n)
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

// Insertar al final usando el puntero tail  O(1)
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

// Buscar elemento en la lista O(n)
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

// Eliminar elemento por indice  O(1) en extremos, O(n) en posicion intermedia
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

// Recorrido Forward (Normal)  O(n)
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

// Recorrido Backward (Inverso) O(n)
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

// Agregar titular buscando primero en el BST O(log n) promedio y revisando duplicados O(n), Total: O(n)
void Equipo::agregar_titular_por_id(int id_buscado) {
    if (bst_empty()) {
        cout << "\nNo hay jugadores cargados en el sistema." << endl;
        return;
    }

    NodoBST *encontrado = root_bst->find(id_buscado);
    if (encontrado == 0) {
        cout << "\nNo existe ningun jugador con el ID " << id_buscado << "." << endl;
        return;
    }

    string nombre_jug = encontrado->value.get_nombre();
    if (buscar_titular(nombre_jug) != -1) {
        cout << "\nEl jugador " << nombre_jug << " ya esta en la lista de titulares." << endl;
        return;
    }

    insertar_titular(nombre_jug);
    cout << "\nJugador " << nombre_jug << " agregado a la lista de titulares." << endl;
}

// Quitar titular por nombre, Buscar O(n) y Eliminar O(n), Total: O(n)
void Equipo::quitar_titular(string nombre_jug) {
    int index = buscar_titular(nombre_jug);
    if (index == -1) {
        cout << "\nEl jugador " << nombre_jug << " no se encuentra en la lista de titulares." << endl;
    } else {
        eliminar_titular_en(index);
        cout << "\nJugador " << nombre_jug << " eliminado de la lista de titulares." << endl;
    }
}

// Mostrar lista de titulares en ambos sentidos O(n)
void Equipo::mostrar_titulares() {
    cout << "\n--- ALINEACION TITULAR (Lista Doblemente Ligada) ---" << endl;
    if (titulares_empty()) {
        cout << "La lista de titulares esta vacia." << endl;
    } else {
        cout << "Orden de rotacion (Forward):  " << titulares_forward() << endl;
        cout << "Orden inverso (Backward):     " << titulares_backward() << endl;
    }
}


// IMPLEMENTACION DEL ARBOL BINARIO DE BUSQUEDA (BST por ID)


// Verificar si el BST esta vacio O(1)
bool Equipo::bst_empty() const {
    return (root_bst == 0);
}

// Liberar toda la memoria del BST O(n)
void Equipo::limpiar_bst() {
    if (root_bst != 0) {
        root_bst->removeChilds();
        delete root_bst;
        root_bst = 0;
    }
}

// Insertar jugador en el BST, Promedio: O(log n), Peor caso: O(n)
void Equipo::insertar_bst(Jugador nuevo) {
    if (root_bst != 0) {
        if (root_bst->find(nuevo.get_id()) == 0) {
            root_bst->add(nuevo);
        }
    } else {
        root_bst = new NodoBST(nuevo);
    }
}

// Validar si un ID ya existe en el BST, Promedio: O(log n), Peor caso: O(n)
bool Equipo::existe_id_bst(int id_buscado) {
    if (root_bst != 0) {
        return (root_bst->find(id_buscado) != 0);
    }
    return false;
}

// Buscar y mostrar jugador directamente desde el BST, Promedio: O(log n), Peor caso: O(n)
void Equipo::buscar_en_bst(int id_buscado) {
    if (bst_empty()) {
        cout << "\nEl arbol de jugadores esta vacio." << endl;
        return;
    }

    NodoBST *encontrado = root_bst->find(id_buscado);
    if (encontrado != 0) {
        cout << "\n--- Jugador encontrado en el BST ---" << endl;
        encontrado->value.mostrar_info_completa();
    } else {
        cout << "\nNo se encontro ningun jugador con el ID " << id_buscado << " en el BST." << endl;
    }
}

// Eliminar jugador del BST por ID, Promedio: O(log n), Peor caso: O(n)
void Equipo::eliminar_de_bst(int id_borrar) {
    if (bst_empty()) {
        cout << "\nEl arbol esta vacio." << endl;
        return;
    }

    if (root_bst->find(id_borrar) == 0) {
        cout << "\nNo existe un jugador con el ID " << id_borrar << " en el BST." << endl;
        return;
    }

    if (id_borrar == root_bst->value.get_id()) {
        NodoBST *old = root_bst;
        if (old->left != 0 && old->right != 0) {
            NodoBST *succ = old->predecesor();
            succ->left = old->left;
            succ->right = old->right;
            root_bst = succ;
        } else if (old->left != 0) {
            root_bst = old->left;
        } else {
            root_bst = old->right;
        }
        delete old;
    } else {
        root_bst->remove(id_borrar);
    }
    cout << "\nJugador con ID " << id_borrar << " eliminado del BST." << endl;
}

// Mostrar jugadores ordenados de menor a mayor ID usando Inorder O(n)
void Equipo::mostrar_ordenados_por_id_bst() {
    cout << "\n--- CATALOGO ORDENADO POR ID (BST Inorder) ---" << endl;
    if (bst_empty()) {
        cout << "El arbol de jugadores esta vacio." << endl;
    } else {
        root_bst->inorder();
    }
}

#endif
