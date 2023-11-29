/*
Miguel Angel Tena Garcia
A01709653
Evidencia 3
Main.cpp

Cambios:
- Busqueda de canciones por titulo
- Simulacion de reproduccion 
- Clonacion de la lista seleccionada para usarla en la reproduccion
- Manejo separa de la cola de reproduccion
- Busqueda por titulo
- Carga y Guardado de listas segun su manipulacion
- Mensajes durante la reproduccion


*/

#include "song.h"
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  DoublyLinkedList library;
  library.loadSongsFromFile();
  std::cout << "\nHola!, bienvenido a tu lista de reproduccion, aqui podras "
               "administrar la musica que mas te gusta!, porfavor dinos que "
               "quieres hacer en esta playlist:\n";

  // Menu principal
  bool continueRunning = true;
  while (continueRunning) {
    std::cout << "\nSeleccione una opción:\n";
    std::cout << "1. Mostrar canciones\n";
    std::cout << "2. Añadir nueva canción\n";
    std::cout << "3. Eliminar una canción por título\n";
    std::cout << "4. Ordenar canciones por likes\n";
    std::cout << "5. Buscar canciones por titulo\n";
    std::cout << "6. Reproducir playlist (sim)\n";
    std::cout << "7. Salir\n";

    int choice;
    std::cin >> choice;

    switch (choice) {

    // Mostrar canciones
    case 1:
      library.displaySongs();
      break;

    // Añadir canciones
    case 2: {
      std::string title, artist;
      int likes;

      std::cin.ignore(); // Limpia el buffer

      std::cout << "Introduce el título de la canción: ";
      std::getline(std::cin, title);

      std::cout << "Introduce el nombre del artista: ";
      std::getline(std::cin, artist);

      std::cout << "Introduce el número de likes: ";
      std::cin >> likes;

      Song newSong(title, artist, likes);
      library.addSong(newSong);
      std::cout << "Canción añadida exitosamente.\n";
      break;
    }

    // Eliminar cancion por titulo
    case 3: {
      std::cin.ignore(); // Limpia el buffer
      std::string title;
      std::cout << "Introduce el título de la canción a eliminar: ";
      std::getline(std::cin, title);
      library.removeSongByTitle(title);
      std::cout << "Canción eliminada (si existía).\n";
      break;
    }

      // Ordenar canciones por likes

    case 4: {
      library.sortSongs();
      std::cout << "Canciones ordenadas por likes.\n";
      break;
    }

    case 7: {
      library.saveSongsToFile();
      continueRunning = false;
      break;
    }

    case 5: {
      std::string searchTitle;
      std::cin.ignore();
      std::cout << "Introduce el título de la canción a buscar: ";
      std::getline(std::cin, searchTitle);
      library.searchSongByTitle(searchTitle);
      break;
    }

    case 6: {
      library.playAndClearQueue();
      break;
    }

    default:
      std::cout << "Opción no válida. Intente de nuevo.\n";
    }
  }
  return 0;
}
