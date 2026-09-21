# Catálogo de Jugadores de Voleibol

Este programa funciona como un registro de los jugadores que integran un equipo de Voleibol, en el cuál se lleva un control de cada atleta y se puede desplegar un catálogo ordenado por su alcance de remate:
* ID
* Nombre
* Posición
* Bloqueo
* Remate
* Ataques
* Errores

## SICT0302: Toma Decisiones
#### Selección de Estructura de Datos
Utilizo un vector para almacenar los objetos de tipo Jugador. Esta estructura es la más adecuada porque permite acceso directo a cualquier posición en tiempo O(1), lo cual es necesario para dividir la lista a la mitad en la Búsqueda Binaria y en el MergeSort.

#### Algoritmo de Ordenamiento Seleccionado: MergeSort
Para definir la alineación titular, el cuerpo técnico necesita evaluar el alcance de remate de los jugadores. Seleccioné MergeSort porque mantiene una velocidad constante de O(n log n) en el mejor, promedio y peor de los casos, evitando volverse lento como otros algoritmos.

## SICT0301: Evalúa los componentes
#### Complejidad del Ordenamiento:
El algoritmo MergeSort tiene una complejidad de O(n log n) en todos los casos, ya que divide sucesivamente el vector a la mitad y realiza un intercalado lineal.

#### Complejidad de la Estructura de Datos:
El vector tiene una complejidad de O(1) para consultar elementos por índice y O(1) promedio para insertar al final con push_back.

#### Complejidad de los demás Componentes y Complejidad Final:
* Búsqueda Binaria: O(log n), divide el espacio de búsqueda a la mitad.
* Búsqueda Secuencial: O(n), recorre la lista completa para filtrar por posición.
* Función Iterativa (promedio bloqueo): O(n), recorre los elementos con un ciclo for.
* Lectura y Escritura de archivos: O(n), procesa los datos de inicio a fin.
* Complejidad Final del Programa: O(n log n), determinada por el algoritmo de ordenamiento que es la operación de mayor costo computacional.

## SICT0303: Implementa acciones científicas
* Consulta: Permite consultar el roster completo, buscar por ID con Búsqueda Binaria y filtrar por posición.
* Lectura de archivos: La función cargar_desde_txt lee los registros almacenados en el archivo txt.
* Escritura de archivos: La función guardar_en_txt guarda el roster en el archivo txt para conservar la información.

## SEG0701: Cultura digital
Utilizo un programa computacional para facilitar el proceso de llevar un registro de atletas y apoyar la toma de decisiones tácticas en un equipo de voleibol.
