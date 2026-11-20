#include <iostream>
#include <string>
#include <vector>
#include "Equipo.h"

using namespace std;

// Validacion de entrada para numeros enteros dentro de un rango, O(1) por intento
int leer_entero(string mensaje, int min_val, int max_val) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            if (valor >= min_val && valor <= max_val) {
                return valor;
            } else {
                cout << "Error: El valor debe estar entre " << min_val << " y " << max_val << "." << endl;
            }
        } else {
            cout << "Error: Debes ingresar un numero entero valido." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

// Validacion de entrada para posicion de voleibol O(1) por intento
string leer_posicion_valida() {
    string pos;
    while (true) {
        cout << "Ingresa Posicion (Central, Libero, Colocador, Opuesto, Banda): ";
        cin >> pos;
        if (pos == "Central" || pos == "Libero" || pos == "Colocador" || pos == "Opuesto" || pos == "Banda") {
            return pos;
        } else {
            cout << "Error: Posicion no valida. Respeta mayuscula inicial (ej. Central)." << endl;
        }
    }
}

// Validacion de nombre (evita que sea solo numeros) O(k) donde k es longitud del nombre
string leer_nombre_valido() {
    string name;
    while (true) {
        cout << "Ingresa Nombre (usa guion bajo sin espacios, ej. Juan_Perez): ";
        cin >> name;
        bool tiene_letra = false;
        for (size_t i = 0; i < name.size(); i++) {
            if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z')) {
                tiene_letra = true;
            }
        }
        if (tiene_letra) {
            return name;
        } else {
            cout << "Error: El nombre debe contener letras." << endl;
        }
    }
}

int main() {
    Equipo miEquipo("Borregos Voleibol", "Universitaria");

    // Carga inicial desde archivo txt hacia el vector y el BST
    miEquipo.cargar_desde_txt("jugadores.txt");

    int opcion = 0;

    while (opcion != 12) {
        cout << "\n" << endl;
        cout << "            SISTEMA DE GESTION DE VOLEIBOL" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "1.  Mostrar roster completo (Vector)" << endl;
        cout << "2.  Ordenar por alcance de remate (Merge Sort)" << endl;
        cout << "3.  Buscar jugador por ID (Arbol BST)" << endl;
        cout << "4.  Mostrar jugadores ordenados por ID (BST Inorder)" << endl;
        cout << "5.  Filtrar por posicion (Busqueda Secuencial)" << endl;
        cout << "6.  Ver promedio de altura de bloqueo" << endl;
        cout << "7.  Agregar jugador a titulares por ID (Lista Doblemente Ligada)" << endl;
        cout << "8.  Quitar jugador de titulares por nombre" << endl;
        cout << "9.  Mostrar titulares en orden normal e inverso" << endl;
        cout << "10. Registrar nuevo jugador y guardar en txt" << endl;
        cout << "11. Exportar reporte de Titulares y BST a archivo txt" << endl;
        cout << "12. Salir" << endl;

        opcion = leer_entero("Elige una opcion (1-12): ", 1, 12);

        if (opcion == 1) {
            miEquipo.mostrar_roster();
        }
        else if (opcion == 2) {
            miEquipo.ordenar_por_remate();
            cout << "\n--- Roster ordenado por alcance de remate (Mayor a Menor) ---" << endl;
            miEquipo.mostrar_resumen_jugadores();
        }
        else if (opcion == 3) {
            int id_bst = leer_entero("Ingresa el ID del jugador a consultar en el BST (1-9999): ", 1, 9999);
            miEquipo.buscar_en_bst(id_bst);
        }
        else if (opcion == 4) {
            miEquipo.mostrar_ordenados_por_id_bst();
        }
        else if (opcion == 5) {
            string pos = leer_posicion_valida();
            miEquipo.filtrar_por_posicion(pos);
        }
        else if (opcion == 6) {
            cout << "\nPromedio de altura de bloqueo del equipo: "
                 << miEquipo.promedio_altura_bloqueo() << " cm" << endl;
        }
        else if (opcion == 7) {
            int id_titular = leer_entero("Ingresa el ID del jugador para agregar a titulares (1-9999): ", 1, 9999);
            miEquipo.agregar_titular_por_id(id_titular);
        }
        else if (opcion == 8) {
            string nombre_quitar = leer_nombre_valido();
            miEquipo.quitar_titular(nombre_quitar);
        }
        else if (opcion == 9) {
            miEquipo.mostrar_titulares();
        }
        else if (opcion == 10) {
            cout << "\n--- REGISTRO DE NUEVO JUGADOR ---" << endl;
            int id = leer_entero("Ingresa ID (1-9999): ", 1, 9999);
            while (miEquipo.existe_id_bst(id)) {
                cout << "Error: El ID " << id << " ya esta registrado. Intenta con otro." << endl;
                id = leer_entero("Ingresa ID (1-9999): ", 1, 9999);
            }

            string name = leer_nombre_valido();
            string pos = leer_posicion_valida();
            int block = leer_entero("Ingresa alcance de bloqueo en cm (180-400): ", 180, 400);
            int spike = leer_entero("Ingresa alcance de remate en cm (debe ser >= bloqueo, max 420): ", block, 420);
            int pts = leer_entero("Ingresa puntos de ataque (0-5000): ", 0, 5000);
            int err = leer_entero("Ingresa errores cometidos (0-2000): ", 0, 2000);

            miEquipo.registrar_jugador(Jugador(id, name, pos, block, spike, pts, err));
            miEquipo.guardar_en_txt("jugadores.txt");
        }
        else if (opcion == 11) {
            miEquipo.guardar_reporte_txt("reporte_equipo.txt");
        }
        else if (opcion == 12) {
            cout << "\nSaliendo del programa... Hasta luego!" << endl;
        }
    }

    return 0;
}
