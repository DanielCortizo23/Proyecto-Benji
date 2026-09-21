# Sistema de Roster y Rendimiento para Equipos de Voleibol

Este programa funciona como un sistema de gestión y análisis para el cuerpo técnico de un equipo de voleibol. Permite registrar las métricas físicas y de rendimiento de los jugadores, consultar el roster y generar clasificaciones de acuerdo con su alcance de salto en la red:
* ID
* Nombre
* Posición en cancha
* Alcance de bloqueo (cm)
* Alcance de remate (cm)
* Efectividad neta de ataque

## SICT0302: Toma Decisiones

#### Selección de Estructura de Datos
Utilicé un vector dinámico porque los jugadores están indexados y se requiere acceso directo por posición en memoria contigua en tiempo O(1) para que la Búsqueda Binaria y el Merge Sort puedan dividir el arreglo a la mitad eficientemente.

#### Algoritmo de Ordenamiento Seleccionado: MergeSort
El cuerpo técnico requiere evaluar a los jugadores según su alcance de remate para definir la alineación titular. Seleccioné el algoritmo de ordenamiento **Merge Sort** porque garantiza una complejidad de O(n \log n) en el mejor, promedio y peor de los casos, a diferencia de Bubble Sort O(n^2) o QuickSort (que puede degradarse a O(n^2) si el pivote elegido no es favorable).

#### Algoritmos de Búsqueda Seleccionados
1. **Búsqueda Binaria ($O(\log n)$):** Utilizada para localizar a un jugador por su ID único dividiendo el arreglo a la mitad recursivamente.
2. **Búsqueda Secuencial ($O(n)$):** Utilizada para recorrer el roster y filtrar a todos los jugadores que pertenezcan a una misma posición (por ejemplo, centrales).

## SICT0301: Evalúa los componentes

#### Análisis de Complejidad:
* **Función Directa (`calcular_efectividad`):** Complejidad de $O(1)$ en tiempo y espacio, ya que solo realiza una resta aritmética simple (`ataques - errores`) sin bucles.
* **Función Iterativa (`promedio_altura_bloqueo`):** Complejidad de $O(n)$, debido a que recorre los $n$ elementos del vector una sola vez mediante un ciclo `for` para sumar los valores de bloqueo.
* **Función Recursiva (`busqueda_binaria_rec`):** Complejidad de $O(\log n)$, ya que en cada paso divide el rango de búsqueda a la mitad.
* **Algoritmo de Ordenamiento (`Merge Sort`):** Complejidad de $O(n \log n)$ tanto en el mejor como en el peor de los casos, dividiendo el vector en mitades recursivamente y realizando un intercalado lineal de $O(n)$.
* **Búsqueda Secuencial (`filtrar_por_posicion`):** Complejidad de $O(n)$, pues examina linealmente cada jugador para comprobar si coincide con la posición solicitada.

## SICT0303: Implementa acciones científicas
Utilizo dos clases modulares: `Jugador.h` y `Equipo.h`, junto con un vector que almacena objetos de tipo `Jugador`. El programa permite registrar a los atletas, procesar sus estadísticas y aplicar algoritmos de ordenamiento y búsqueda para la toma de decisiones deportivas.

## SEG0701: Cultura digital
Utilizo un programa computacional para digitalizar el seguimiento deportivo, facilitando el análisis objetivo del rendimiento atlético y la toma de decisiones tácticas en un equipo de voleibol.
