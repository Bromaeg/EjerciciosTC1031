# Proyecto: Lista de reproduccion (Music Organizer)
Este programa esta diseñado para gestionar una lista de reproduccion de musica, cada cancion posee un titulo, artista y numero de likes, estas canciones estan almacenadas en una estructura de lista doblemente ligada, y las principales funcionalidades para este avance es el añadir y eliminar canciones de la lista, mostrar todas las canciones de la lista, ordenar canciones basado en el numero likes asi como el guardar y cargar las canciones desde un archivo txt donde se almacenaran las playlist.

## Descripción del avance 1
En este avance, desarrolle el merge sort que utilizo para ordenar la lista de ambas formas, tambien se carga el archivo songs.txt donde se almacena la lista y finalmente despliega en consola la lista original, despues ordenadas en likes y artistas en ese orden.

## Descripción del avance 2
En este avance, solo cambie la estructura de los datos, el usuario debe de ingresar los datos de sus canciones favoritas, para despues poder ordenarlos por numero de likes, por lo que aqui utilizo una lista doblemente ligada, junto con un merge sort, finalmente agregue tanto la lectura como escritura en el archivo txt.

## Descripción del avance 3
En este avance, realicé mejoras significativas en la gestión de la lista de reproducción. Implementé la función playAndClearQueue, que simula la reproducción de canciones y, para proteger la lista original, introduje un sistema de clonación con cloneToQueue. También agregué la búsqueda de canciones por título con searchSongByTitle, mejorando la interactividad del usuario, ademas de que en esta se guardan las playlist con las estructuras con las que estes trabajando. Estas adiciones han hecho que el programa sea más dinámico y amigable, manteniendo la eficiencia en la gestión y reproducción de las listas de música, considero que la aplicacion puede usarse facilmente para generar un reproductor de archivos de musica muy facilmente lo que nos indica su clara aplicacion en el mundo real.

### Cambios sobre el tercer avance

1. Simulación de Reproducción de Canciones (playAndClearQueue): Se añadió una nueva funcionalidad para simular la reproducción de canciones. Esta función recorre la lista, muestra cada canción como si se estuviera reproduciendo y luego la elimina de la lista temporal.
   
2. Clonación de la Lista de Reproducción (cloneToQueue): Para evitar modificar la lista original durante la reproducción, se implementó un sistema para clonar la lista de reproducción actual en una lista temporal. Esto permite simular la reproducción sin alterar la lista principal.
   
3. Búsqueda por Título (searchSongByTitle): Se introdujo una función para buscar canciones específicas por su título, mejorando la interacción y la experiencia del usuario con el programa.
   
4. Creacion de playlist's con nombre personalizado, donde se guarda con las estructuras que se van generando en el mismo archivo si estas modificando o en el nuevo si la playlist es nueva.

## Instrucciones para compilar el avance de proyecto
Ejecuta el siguiente comando en la terminal:

`g++ song.h main.cpp -o songs` 

## Instrucciones para ejecutar el avance de proyecto
Ejecuta el siguiente comando en la terminal:

`./songs` 

## Descripción de las entradas del proyecto
La entrada del proyecto es que el usuario tenga alguna lista formateada en txt, ingresando el nombre podria reproducirla o empezar a modificarla, si el no hay archivos con ese nombre, se crea una nueva playlist con el nombre, y puedes empezar a añadir canciones, una vez que ya tienes canciones puedes darle en reproducir y empezara la simulacion de reproduccion.

## Descripción de las salidas del avance de proyecto
La salida del programa, me arroja un txt con la informacion actualizada de la playlist, formateado con cada una de las canciones, ademas cuando se esta reproduciendo te lanza en consola que cancion se esta reproduciendo. 

## Desarrollo de competencias

### SICT0301: Evalúa los componentes
#### Hace un análisis de complejidad correcto y completo para todos los demás componentes del programa y determina la complejidad final del programa.

Dentro de este avance, emplee el algoritmo del MergeSort para ordenar las canciones en funcion del numero de likes, pero, gracias a su versatilidad, podriamos adaptarlo facilmente para ordenar por otros criterios, ya sea alfabeticamente por titulo o por artista.
Analizando a fondo la complejidad de nuestro proyecto y buscando una eficiencia óptima, optamos por Merge Sort, que presenta una complejidad temporal de (O(n log n)).

T(n) = 2T(n/2) + O(n)
T(n) = O(n log n)

por lo que para el los metodos queda asi:

MergeSort para Ordenar la Lista = O(n log n)

Búsqueda de Canciones por Título (searchSongByTitle) = O(n)
- La búsqueda lineal recorre cada nodo de la lista hasta encontrar la canción deseada o hasta que se acabe la lista

Inserción de una Nueva Canción (addSong) = O(1)
- La inserción al final de una lista doblemente ligada es una operación de tiempo constante, ya que se tiene un puntero directo al último nodo (tail).

Eliminación de una Canción por Título (removeSongByTitle) = O(n)
- Requiere recorrer potencialmente toda la lista para encontrar la canción a eliminar, similar a la búsqueda por título.

Carga de Canciones desde un Archivo (loadSongsFromFile) = O(n)
- Ambas operaciones recorren cada canción de la lista (para cargar o guardar), lo que resulta en una complejidad lineal respecto al número de canciones.

Reproducción y Limpieza de la Cola (playAndClearQueue) = O(n)
- Aunque incluye un retraso temporal (sleep), en términos de complejidad algorítmica, se recorre toda la lista (o su clon), lo que implica una complejidad lineal.

Guardado de la playlist en un archivo nuevo.
- Guarda la playlist con la que estas trabajando, ya sea actualizandola o creando una nueva seria O(1)

Mejor Caso: O(1)
Caso Promedio: O(n/2)
Peor Caso: O(n log n)

#### Implementa mecanismos para consultar información de las estructras correctos.

En mi programa, implementé un mecanismo eficiente para consultar información en la lista doblemente ligada, que representa una biblioteca de música. Cada nodo en la lista contiene una instancia de la clase Song, que incluye métodos 'getters' para acceder a sus atributos (título, artista, likes). Para consultar información específica, desarrollé la función searchSongByTitle, que permite a los usuarios buscar canciones por título. Esta función recorre la lista y utiliza los getters de Song para encontrar y mostrar la canción deseada. Además, la capacidad de ordenar las canciones por popularidad (likes) y mostrarlas en consola proporciona una forma clara y directa de consultar el estado actual de la lista. Estas implementaciones demuestran un entendimiento profundo de cómo gestionar y acceder a la información almacenada en estructuras de datos complejas.

#### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.

Desde el inicio del proyecto, he implementado mecanismos de lectura de archivos para cargar los datos de las canciones desde un archivo songs.txt a la estructura de la lista doblemente ligada. En los avances posteriores, mejoré este mecanismo para permitir que los usuarios ingresen sus propias canciones, que luego se añaden a la lista. La función loadSongsFromFile se encarga de leer los datos del archivo, analizar cada línea y convertir la información en instancias de Song, que se añaden a la lista. Este proceso asegura que la lista refleje fielmente el contenido del archivo songs.txt. Al final de cada sesión del programa, la lista actualizada se guarda de nuevo en el archivo, manteniendo la persistencia de los datos. Esta implementación muestra mi habilidad para manejar la lectura de archivos y cargar datos de manera efectiva en estructuras de datos en un entorno de programación real.

#### Implementa mecanismos de escritura de archivos para guardar los datos  de las estructuras de manera correcta

En esta nueva y ultima iteracion de mi proyecto, al momento de iniciar el programa si no se quiere editar una playlist, se crea una nueva y ahi empiezas a añadir las canciones que quieres reproducir, cuando terminas de añadir las canciones, al salir, presionar la opcion 7 del menu, se guarda la estructura de la playlist en un archivo .txt con el nombre de la playlist.