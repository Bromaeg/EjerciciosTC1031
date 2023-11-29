/*
Miguel Angel Tena Garcia
A01709653
Evidencia 3
Song.h

*/

#ifndef SONG_H
#define SONG_H

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

// SONG
class Song {
private:
  std::string title;
  std::string artist;
  int likes;

public:
  // Constructor de la clase Song
  Song(std::string t, std::string a, int l) : title(t), artist(a), likes(l) {}

  // Getters para los atributos de la clase
  std::string getTitle() const { return title; }
  std::string getArtist() const { return artist; }
  int getLikes() const { return likes; }

  // Método para mostrar la información de la canción
  void display() const {
    std::cout << "Título: \"" << title << "\" - Artista: \"" << artist
              << "\" (Likes: " << likes << ")\n";
  }
};

// DoublyLinkedList

class DoublyLinkedList {

private:
  // Definición del nodo de la lista doblemente ligada
  struct Node {
    Song data;
    Node *prev;
    Node *next;

    // Constructor del nodo
    Node(const Song &s) : data(s), prev(nullptr), next(nullptr) {}
  };

  Node *head;
  Node *tail;
  Node *queueHead;
  std::string playlistName;

  // Obtiene el nodo medio de la lista
  Node *getMiddle(Node *start, Node *last) {
    if (!start)
      return nullptr;

    Node *slow = start;
    Node *fast = start->next;

    // Algoritmo del corredor rapido y lento para obtener el nodo medio
    while (fast != last) {
      fast = fast->next;
      if (fast != last) {
        slow = slow->next;
        fast = fast->next;
      }
    }
    return slow;
  }

  // Fusiona dos listas ordenadas en una sola lista ordenada
  Node *merge(Node *left, Node *right) {
    if (!left)
      return right;
    if (!right)
      return left;

    // Compara los 'likes' de las canciones para determinar el orden
    if (left->data.getLikes() >= right->data.getLikes()) {
      left->next = merge(left->next, right);
      left->next->prev = left;
      left->prev = nullptr;
      return left;
    } else {
      right->next = merge(left, right->next);
      right->next->prev = right;
      right->prev = nullptr;
      return right;
    }
  }

  // Implementacion recursiva del algoritmo MergeSort
  Node *mergeSort(Node *node) {
    if (!node || !node->next)
      return node;

    Node *middle = getMiddle(node, nullptr);
    Node *middleNext = middle->next;

    middle->next = nullptr;

    Node *left = mergeSort(node);
    Node *right = mergeSort(middleNext);

    return merge(left, right);
  }

  // Añadir a la cola
  void addToQueue(const Song &song) {
    Node *newNode = new Node(song);
    if (!queueHead) {
      queueHead = newNode;
      return;
    }
    Node *temp = queueHead;
    while (temp->next) {
      temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
  }

  // Método para limpiar la cola
  void clearQueue() {
    while (queueHead != nullptr) {
      Node *temp = queueHead;
      queueHead = queueHead->next;
      delete temp;
    }
  }

public:
  // Constructor de la lista doblemente ligada con canciones prefab.
  DoublyLinkedList() : head(nullptr), tail(nullptr), queueHead(nullptr) {}

  // Método para clonar la lista actual a la cola de reproduccion
  void cloneToQueue() {
    Node *current = head;
    while (current) {
      addToQueue(current->data);
      current = current->next;
    }
  }

  // Buscar cancion por nombre
  void searchSongByTitle(const std::string &title) const {
    Node *current = head;
    while (current != nullptr) {
      if (current->data.getTitle() == title) {
        current->data.display();
        return;
      }
      current = current->next;
    }
    std::cout << "Canción no encontrada.\n";
  }

  // Añade una cancion al final de la lista
  void addSong(const Song &song) {
    Node *newNode = new Node(song);
    if (!head) {
      head = tail = newNode;
      return;
    }
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }

  // Elimina una cancion por su título
  void removeSongByTitle(const std::string &title) {
    Node *temp = head;

    while (temp != nullptr) {
      if (temp->data.getTitle() == title) {
        if (temp->prev)
          temp->prev->next = temp->next;
        if (temp->next)
          temp->next->prev = temp->prev;

        if (temp == head)
          head = head->next;
        if (temp == tail)
          tail = tail->prev;

        delete temp;
        return;
      }
      temp = temp->next;
    }
  }

  // Ordena las canciones por 'likes' utilizando MergeSort
  void sortSongs() {
    head = mergeSort(head);
    tail = head;
    while (tail && tail->next) {
      tail = tail->next;
    }
  }

  // Muestra todas las canciones en la lista
  void displaySongs() const {
    Node *current = head;
    while (current) {
      current->data.display();
      current = current->next;
    }
  }

  // Cargar las canciones de una playlist segun el nombre de la playlist
  void loadSongsFromFile() {
    std::cout << "Ingrese el nombre de la playlist (sin espacios, use '-') a "
                 "cargar, si no existe, ingrese el nombre de una nueva: ";
    std::cin >> playlistName;
    std::string filename = playlistName + ".txt";

    std::ifstream file(filename);
    if (!file.is_open()) {
      std::cout << "Playlist no encontrada, creando una nueva: " << filename
                << "\n";
      std::ofstream newFile(filename);
      newFile.close();
      return;
    }

    std::string line;
    while (getline(file, line)) {
      std::istringstream ss(line);
      std::string title, artist, likesStr;

      // Asumiendo que el formato de la línea es: "title","artist",likes
      if (getline(ss, title, ',') && getline(ss, artist, ',') &&
          getline(ss, likesStr)) {
        // Limpiar las comillas de title y artist
        title = title.substr(1, title.length() - 2);
        artist = artist.substr(1, artist.length() - 2);

        try {
          // Asumiendo que likes está seguido de la palabra " Likes"
          size_t pos = likesStr.find(" ");
          if (pos != std::string::npos) {
            likesStr = likesStr.substr(0, pos);
          }
          int likes = std::stoi(likesStr);

          // Añadir la cancion a la lista
          addSong(Song(title, artist, likes));
        } catch (const std::invalid_argument &) {
          std::cerr << "Error al procesar la línea: " << line << "\n";
        }
      } else {
        std::cerr << "Formato incorrecto en la línea: " << line << "\n";
      }
    }
    file.close();
  }

  // Guardar cambios en el archivo
  void saveSongsToFile() const {
    std::string filename = playlistName + ".txt";
    std::ofstream file(filename);
    if (!file.is_open()) {
      std::cerr << "Error al crear el archivo " << filename << "\n";
      return;
    }

    Node *current = head;
    while (current) {
      file << "\"" << current->data.getTitle() << "\",\""
           << current->data.getArtist() << "\"," << current->data.getLikes()
           << "\n";
      current = current->next;
    }
    file.close();
  }

  void playAndClearQueue() {
    // Clona la lista principal en la cola de reproduccion
    cloneToQueue();

    // Ahora usa la cola de reproduccion (queueHead) para la reproduccion
    Node *current = queueHead;
    while (current) {
      // Muestra la información de la canción actual
      std::cout << "\n Cambiando cancion... \n";
      std::cout << "\n Se está reproduciendo: \n";
      current->data.display();

      // Espera 2 segundos como simulacion de la reproduccion de la cancion
      // Se puede añadir la funcion para reproducir algun archivo y hacerlo funcional
      std::this_thread::sleep_for(std::chrono::seconds(2));

      // Avanza a la siguiente cancion y elimina la actual de la cola
      Node *toDelete = current;
      current = current->next;
      delete toDelete;
    }

    // Limpia la cola de reproduccion
    queueHead = nullptr;

    std::cout << "Fin de la reproducción.\n";
  }

  // Método para limpiar la lista actual
  void clearList() {
    while (head != nullptr) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
    head = tail = nullptr;
  }
};

#endif // SONG_H
