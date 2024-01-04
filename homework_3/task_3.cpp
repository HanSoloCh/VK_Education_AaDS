/*
Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога, которая
возвращается в этот же город.

Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
N ≤ 10000, M ≤ 250000.
Длина каждой дороги ≤ 10000.
 */

#include <iostream>
#include <queue>
#include <set>
#include <vector>

class ListGraph {
   public:
    explicit ListGraph(int size) : adjacencyLists(size){};
    ~ListGraph() = default;

    void AddEdge(int from, int to, int length) {
        adjacencyLists[from].emplace_back(to, length);
        adjacencyLists[to].emplace_back(from, length);
    };

    [[nodiscard]] int VerticesCount() const { return static_cast<int>(adjacencyLists.size()); };

    [[nodiscard]] std::vector<std::pair<int, int>> GetNextVertices(int vertex) const { return adjacencyLists[vertex]; };

    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const {
        std::vector<int> prevVertices;

        for (int from = 0; from < adjacencyLists.size(); ++from) {
            for (std::pair<int, int> to : adjacencyLists[from]) {
                if (to.first == vertex) {
                    prevVertices.push_back(from);
                }
            }
        }
        return prevVertices;
    }

    int ShortestWay(int from, int to) const;

   private:
    std::vector<std::vector<std::pair<int, int>>> adjacencyLists;
};

int ListGraph::ShortestWay(int from, int to) const {
    std::vector<int> distance(VerticesCount(), -1);
    distance[from] = 0;
    // Хранятся (Расстояние, вершина)
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> priority_queue;
    priority_queue.emplace(distance[from], from);
    while (!priority_queue.empty()) {
        std::pair<int, int> cur = priority_queue.top();
        int cur_num = cur.second, cur_len = cur.first;
        priority_queue.pop();
        if (distance[cur_num] != -1 && distance[cur_num] < cur_len) continue;

        // Дает нам (вершину, расстояние)
        for (std::pair<int, int> next_vert : GetNextVertices(cur.second)) {
            if (distance[next_vert.first] == -1) {
                distance[next_vert.first] = distance[cur_num] + next_vert.second;
                priority_queue.emplace(distance[next_vert.first], next_vert.first);
            } else if (distance[next_vert.first] > distance[cur_num] + next_vert.second) {
                distance[next_vert.first] = distance[cur_num] + next_vert.second;
                priority_queue.emplace(distance[next_vert.first], next_vert.first);
            }
        }
    }
    return distance[to];
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    ListGraph graph(n);
    int from = 0, to = 0;
    for (size_t i = 0; i < m; ++i) {
        int length = 0;
        std::cin >> from >> to >> length;
        graph.AddEdge(from, to, length);
    }
    std::cin >> from >> to;
    std::cout << graph.ShortestWay(from, to);
    return 0;
}
