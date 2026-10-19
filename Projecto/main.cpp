#include <iostream>
#include <string>
#include <vector>
#include "Equipo.h"

using namespace std;

int main() {
    Equipo miEquipo("Borregos Voleibol", "Universitaria");

    miEquipo.cargar_desde_txt("jugadores.txt");

    int opcion = 0;

    while (opcion != 9) {
        cout << "\n" << endl;
        cout << "          SISTEMA DE VOLEIBOL" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "1. Mostrar roster completo" << endl;
        cout << "2. Ordenar por alcance de remate " << endl;
        cout << "3. Buscar jugador por ID " << endl;
        cout << "4. Filtrar por posicion (Central, Libero, Colocador, Opuesto, Banda)" << endl;
        cout << "5. Ver promedio de altura de bloqueo" << endl;
        cout << "6. Agregar jugador a titulares por ID " << endl;
        cout << "7. Quitar jugador de titulares por nombre" << endl;
        cout << "8. Mostrar titulares en orden normal e inverso" << endl;
        cout << "9. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            miEquipo.mostrar_roster();
        }
        else if (opcion == 2) {
            miEquipo.ordenar_por_remate();
            cout << "\n--- Roster ordenado por remate ---" << endl;
            miEquipo.mostrar_resumen_jugadores();
        }
        else if (opcion == 3) {
            int id_buscado;
            cout << "Ingresa el ID del jugador a buscar (1 al 20): ";
            cin >> id_buscado;
            int pos = miEquipo.buscar_por_id(id_buscado);
            if (pos != -1) {
                cout << "\nJugador con ID " << id_buscado << " encontrado en el sistema!" << endl;
            } else {
                cout << "\nJugador no encontrado." << endl;
            }
        }
        else if (opcion == 4) {
            string pos;
            cout << "Ingresa la posicion (Central, Libero, Colocador, Opuesto, Banda): ";
            cin >> pos;
            miEquipo.filtrar_por_posicion(pos);
        }
        else if (opcion == 5) {
            cout << "\nPromedio de altura de bloqueo: " 
                 << miEquipo.promedio_altura_bloqueo() << " cm" << endl;
        }
        else if (opcion == 6) {
            int id_titular;
            cout << "Ingresa el ID del jugador para meter a titulares (1 al 20): ";
            cin >> id_titular;
            miEquipo.agregar_titular_por_id(id_titular);
        }
        else if (opcion == 7) {
            string nombre_quitar;
            cout << "Ingresa el nombre exacto del jugador a quitar (ej. Wilfredo_Leon): ";
            cin >> nombre_quitar;
            miEquipo.quitar_titular(nombre_quitar);
        }
        else if (opcion == 8) {
            miEquipo.mostrar_titulares();
        }
        else if (opcion == 9) {
            cout << "\nSaliendo del programa... Hasta luego!" << endl;
        }
        else {
            cout << "\nOpcion no valida. Intenta de nuevo." << endl;
        }
    }

    return 0;
}
