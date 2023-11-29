#include <string>
#include <unordered_map>

// Clase para representar una lista doblemente enlazada.
class DoublyLinkedList {
private:

    // Nodo interno para la lista doblemente enlazada.
    struct Node {
        char value; 
        Node* prev; // Puntero al nodo anterior.
        Node* next; // Puntero al nodo siguiente.
        Node(char val) : value(val), prev(nullptr), next(nullptr) {}
    };

    Node* head; 
    Node* tail; 
    std::unordered_map<char, Node*> charMap;

public:
    DoublyLinkedList() {
        head = new Node(0);
        tail = new Node(0);
        head->next = tail;
        tail->prev = head;
    }

    // Destructor que libera la memoria de los nodos.
    ~DoublyLinkedList() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr; // Libera el nodo actual.
            curr = next; // Avanza al siguiente nodo.
        }
    }

    // Añade un carácter al final de la lista y elimina los nodos anteriores si es necesario.
    void addCharToEnd(char c) {
        if (charMap.find(c) != charMap.end()) {
            removeNodesUpTo(charMap[c]); // Elimina nodos si el carácter ya existe.
        }
        Node* newNode = new Node(c);
        newNode->prev = tail->prev; 
        newNode->next = tail;
        tail->prev->next = newNode; // Enlaza el último nodo con el nuevo.
        tail->prev = newNode; // Enlaza la cola ficticia con el nuevo nodo.
        charMap[c] = newNode;
    }

    // Elimina nodos de la lista hasta el nodo dado.
    void removeNodesUpTo(Node* node) {
        Node* curr = head->next;
        while (curr != node) {
            Node* next = curr->next;
            charMap.erase(curr->value);
            delete curr; 
            curr = next; // Avanza al siguiente nodo.
        }
        // Elimina el nodo que causó la duplicidad y ajusta la lista.
        if (node != nullptr) {
            head->next = node->next;
            if (node->next != nullptr) {
                node->next->prev = head;
            }
            charMap.erase(node->value);
            delete node; // Libera el nodo duplicado.
        }
    }

    // Devuelve el número de nodos únicos en la lista.
    int size() const {
        return charMap.size();
    }
};

// Clase para resolver el problema de la subcadena más larga sin caracteres repetidos.
class Solution {
public:

    // Función que calcula la longitud de la subcadena más larga sin caracteres repetidos.
    int lengthOfLongestSubstring(std::string s) {
        DoublyLinkedList dll; 
        int maxLength = 0; 

        // Itera sobre cada carácter de la cadena.
        for (char c : s) {
            dll.addCharToEnd(c); 
            maxLength = std::max(maxLength, dll.size()); 
        }

        return maxLength; // Devuelve la longitud de la subcadena más larga sin repetición.
    }
};
