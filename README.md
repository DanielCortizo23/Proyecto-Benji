# Catálogo de Jugadores de Voleibol

Este programa funciona como un registro interactivo de los jugadores que integran un equipo de Voleibol, en el cuál se lleva un control de cada atleta, se puede desplegar un catálogo ordenado por alcance de remate o por ID, gestionar la alineación titular y exportar reportes a archivos de texto:
- ID
- Nombre
- Posición
- Bloqueo
- Remate
- Ataques
- Errores

## SICT0302: Toma Decisiones
#### Selección de Estructuras de Datos
Utilizo un vector para almacenar el catálogo general de objetos de tipo Jugador. Esta estructura es adecuada porque permite acceso directo a cualquier posición en tiempo O(1), lo cual es necesario para dividir y mezclar los elementos durante el MergeSort, así como recorrer el plantel para filtros y estadísticas.

Utilizo una Lista Doblemente Ligada para guardar la alineación titular, porque permite insertar jugadores al final en tiempo O(1) usando el puntero tail, eliminar elementos dinámicamente y recorrer la rotación de titulares hacia adelante y hacia atrás con los punteros next y previous.

Utilizo un Árbol Binario de Búsqueda (BST) indexado por el ID del jugador como estructura no lineal. Esta estructura permite buscar jugadores rápidamente por su ID y validar si un ID ya está registrado en tiempo O(log n) promedio sin tener que volver a ordenar el vector, además de desplegar y guardar el catálogo ordenado por ID mediante el recorrido inorder.

#### Algoritmo de Ordenamiento Seleccionado: MergeSort
Para definir la alineación titular, el cuerpo técnico necesita evaluar el alcance de remate de los jugadores. Seleccioné MergeSort porque mantiene una velocidad constante de O(n log n) en el mejor, promedio y peor de los casos, evitando volverse lento como otros algoritmos cuadráticos.

## SICT0301: Evalúa los componentes
#### Complejidad del Ordenamiento:
El algoritmo MergeSort (ordenar_por_remate, merge_sort y mezclar) tiene una complejidad temporal de O(n log n) en el mejor, promedio y peor caso, y una complejidad espacial de O(n), ya que divide sucesivamente el vector a la mitad y realiza un intercalado lineal usando un vector temporal.

#### Complejidad de las Estructuras de Datos:
- Vector (roster):
  - Acceso por índice: O(1).
  - Inserción al final (push_back): O(1) amortizado y O(n) en el peor caso cuando redimensiona memoria.
  - Recorridos completos (mostrar_roster, mostrar_resumen_jugadores): O(n).

- Lista Doblemente Ligada (Titulares):
  - Verificar si está vacía (titulares_empty): O(1).
  - Inserción al final usando el puntero tail (insertar_titular): O(1).
  - Búsqueda de un titular (buscar_titular): O(1) mejor caso, O(n) promedio y peor caso.
  - Eliminación por índice (eliminar_titular_en): O(1) en los extremos head o tail, O(n) en posiciones intermedias.
  - Recorridos de rotación normal e inverso (titulares_forward, titulares_backward) y liberar memoria (limpiar_titulares): O(n).

- Árbol Binario de Búsqueda (BST por ID):
  - Verificar si está vacío (bst_empty): O(1).
  - Inserción (insertar_bst / add): O(log n) en caso promedio y O(n) en el peor caso si los IDs entran ordenados.
  - Búsqueda y validación de ID duplicado (buscar_en_bst / existe_id_bst / find): O(1) mejor caso (en la raíz), O(log n) promedio y O(n) peor caso.
  - Eliminación de nodo (eliminar_de_bst / remove / predecesor): O(log n) promedio y O(n) peor caso.
  - Recorrido ordenado por ID (mostrar_ordenados_por_id_bst / inorder), guardado inorder (guardar_inorder) y liberar memoria (limpiar_bst / removeChilds): O(n).

#### Complejidad de los demás Componentes y Complejidad Final:
- Métodos de la clase Jugador (constructores, getters, setters, calcular_efectividad, mostrar_info_completa y mostrar_resumen): O(1).
- Constructores, getters y setters de Equipo (Equipo, get_nombre, get_categoria, set_nombre, set_categoria): O(1).
- Destructor (~Equipo): O(n), ya que llama a limpiar_titulares O(n) y limpiar_bst O(n).
- Registrar jugador (registrar_jugador): O(log n) promedio y O(n) peor caso, al insertar en el vector O(1) amortizado y en el BST O(log n) promedio.
- Búsqueda Secuencial (filtrar_por_posicion): O(n), recorre el vector completo para filtrar por posición.
- Función Iterativa (promedio_altura_bloqueo): O(n), recorre los elementos con un ciclo for para sumar y promediar.
- Gestión de titulares desde menú (agregar_titular_por_id, quitar_titular, mostrar_titulares): O(n), ya que busca en el BST O(log n) promedio y valida duplicados, busca o recorre la lista de titulares en O(n).
- Lectura de archivo (cargar_desde_txt): O(n log n) promedio y O(n^2) en el peor caso teórico, porque lee los n registros del archivo txt y los inserta uno por uno en el vector y en el BST.
- Escritura de archivos (guardar_en_txt y guardar_reporte_txt): O(n), recorre los n jugadores del vector, la lista doblemente ligada y el BST en inorder para escribirlos en los archivos txt.
- Validaciones de entrada en main (leer_entero, leer_posicion_valida, leer_nombre_valido): O(1) por intento para números y posiciones, y O(k) para el nombre donde k es su cantidad de caracteres.
- Menú interactivo en main: O(m * n log n) en caso promedio, donde m es la cantidad de operaciones que realice el usuario antes de salir.
- Complejidad Final del Programa: O(n log n) en caso promedio por operación principal, determinada por el ordenamiento MergeSort y la carga inicial de los n registros al BST (siendo O(n^2) únicamente en el peor caso teórico de cargar datos estrictamente ordenados en el BST).

## SICT0303: Implementa acciones científicas
- Consulta: Permite consultar el roster completo en el vector, buscar por ID en el Árbol BST, listar jugadores ordenados por ID con el recorrido inorder del BST, filtrar por posición y administrar la lista doblemente ligada de titulares.
- Lectura de archivos: La función cargar_desde_txt lee los 40 registros de prueba almacenados en jugadores.txt al iniciar el programa y pobla tanto el vector como el BST.
- Escritura de archivos: La función guardar_en_txt guarda el roster actualizado en jugadores.txt cuando se registra un nuevo jugador, y la función guardar_reporte_txt exporta a reporte_equipo.txt el estado actual de la Lista Doblemente Ligada de titulares y el recorrido inorder del Árbol BST.

## SEG0701: Cultura digital
Utilizo un programa computacional interactivo con validaciones de entrada para facilitar el registro estadístico de atletas y apoyar la toma de decisiones tácticas en un equipo de voleibol. Las validaciones evitan errores comunes del usuario como ingresar letras en campos numéricos, registrar IDs repetidos, escribir posiciones inexistentes o introducir alcances de remate menores al de bloqueo, haciendo la herramienta útil y confiable para un entorno deportivo real.
