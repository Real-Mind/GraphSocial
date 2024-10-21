#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

using namespace std;

// Класс для представления графа
class Graph {
public:
    // Структура для хранения списка смежности
    unordered_map<string, vector<string>> adjList;

    // Метод для добавления ребра между двумя вершинами
    void addEdge(const string& person1, const string& person2) {
        adjList[person1].push_back(person2);
        adjList[person2].push_back(person1); // Неориентированный граф
    }

    // Метод для поиска всех пар с расстоянием не более 3
    set<pair<string, string>> findPairs() {
        set<pair<string, string>> result;

        for (const auto& person : adjList) {
            const string& start = person.first;
            // BFS
            queue<pair<string, int>> q; // Пара: человек и расстояние
            unordered_map<string, int> visited;
            q.push({start, 0});
            visited[start] = 0;

            while (!q.empty()) {
                auto current = q.front();
                q.pop();
                string currentPerson = current.first;
                int currentDistance = current.second;

                // Если расстояние больше 3, пропускаем
                if (currentDistance < 3) {
                    for (const auto& neighbor : adjList[currentPerson]) {
                        if (visited.find(neighbor) == visited.end() || visited[neighbor] > currentDistance + 1) {
                            visited[neighbor] = currentDistance + 1;
                            q.push({neighbor, currentDistance + 1});
                        }
                    }
                }
            }

            // Добавляем пары в результат
            for (const auto& entry : visited) {
                const string& target = entry.first;
                int distance = entry.second;

                // Добавляем в результат, если расстояние не превышает 3
                if (distance <= 3 && target != start) {
                    result.insert({start, target});
                }
            }
        }

        return result;
    }
};

int main() {
    Graph g;

    // Добавляем ребра (друзья)
    g.addEdge("Олег", "Иван");
    g.addEdge("Иван", "Петр");
    g.addEdge("Петр", "Саша");
    g.addEdge("Саша", "Женя");
    g.addEdge("Олег", "Анна");
    g.addEdge("Анна", "Женя");

    // Найти и вывести все пары с расстоянием не более 3
    auto pairs = g.findPairs();
    
    cout << "Пары друзей через три рукопожатия:" << endl;
    for (const auto& pair : pairs) {
        cout << pair.first << " и " << pair.second << endl;
    }

    return 0;
}
