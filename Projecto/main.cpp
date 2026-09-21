#include <iostream>
#include <string>
#include <vector>
#include "Equipo.h"

using namespace std;

int main() {
    Equipo miEquipo("Borregos Voleibol", "Universitaria");

    // Registro inicial de jugadores
    miEquipo.registrar_jugador(Jugador(101, "Wilfredo_Leon", "Receptor", 345, 370, 45, 8));
    miEquipo.registrar_jugador(Jugador(102, "Lucas_Saatkamp", "Central", 340, 355, 30, 3));
    miEquipo.registrar_jugador(Jugador(103, "Yuji_Nishida", "Opuesto", 330, 350, 50, 12));
    miEquipo.registrar_jugador(Jugador(104, "Simone_Giannelli", "Colocador", 320, 335, 10, 2));
    miEquipo.registrar_jugador(Jugador(105, "Robertlandy_Simon", "Central", 355, 384, 38, 4));

  
    miEquipo.guardar_en_txt("jugadores.txt");


    miEquipo.cargar_desde_txt("jugadores.txt");

    cout << "\n" << endl;
    cout << "ROSTER SIN ORDENAR" << endl;
    cout << "" << endl;
    miEquipo.mostrar_roster();

    //  Merge Sort O(n log n)
    miEquipo.ordenar_por_remate();

    cout << "\n\n" << endl;
    cout << "ROSTER ORDENADO POR ALCANCE DE REMATE" << endl;
    cout << "" << endl;
    miEquipo.mostrar_resumen_jugadores();

    // Búsqueda Binaria O(log n)
    cout << "\n\n" << endl;
    cout << "BUSQUEDA POR ID" << endl;
    cout << "" << endl;
    int id_a_buscar = 103;
    int posicion = miEquipo.buscar_por_id(id_a_buscar);
    if (posicion != -1) {
        cout << "Jugador con ID " << id_a_buscar << " encontrado exitosamente en el sistema." << endl;
    } else {
        cout << "Jugador no encontrado." << endl;
    }

    // Búsqueda Secuencial O(n)
    cout << "\n\n" << endl;
    cout << "BUSQUEDA POR POSICION" << endl;
    cout << "" << endl;
    miEquipo.filtrar_por_posicion("Central");

    // Función Iterativa O(n)
    cout << "\n" << endl;
    cout << "METRICA DEL EQUIPO" << endl;
    cout << "" << endl;
    cout << "Promedio de altura de bloqueo: " 
         << miEquipo.promedio_altura_bloqueo() << " cm" << endl;

    return 0;
}
