// Miguel Angel Tena Garcia
// A01709653
// Búsqueda de los K Elementos Más Frecuentes Usando Min Heap y Mapeo de Frecuencias

#include <vector>
#include <unordered_map>
#include <queue>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Paso 1: Contar la frecuencia de cada elemento
        unordered_map<int, int> frequencyMap;
        for (int num : nums) {
            frequencyMap[num]++;
        }

        // Paso 2: Usar un min heap para almacenar los elementos por frecuencia
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

        for (auto pair : frequencyMap) {
            minHeap.push({pair.second, pair.first});
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }

        // Paso 3: Construir el resultado
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        return result;
    }
};
