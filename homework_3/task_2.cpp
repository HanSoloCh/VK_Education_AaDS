/*
 Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то
 вершинами. Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность
 O(V+E).
*/

#include <iostream>
#include <queue>
#include <vector>

class ListGraph {
   public:
    explicit ListGraph(int size) : adjacencyLists(size){};
    ~ListGraph() = default;

    void AddEdge(int from, int to) {
        adjacencyLists[from].push_back(to);
        adjacencyLists[to].push_back(from);
    }

    int VerticesCount() const { return adjacencyLists.size(); }

    std::vector<int> GetNextVertices(int vertex) const { return adjacencyLists[vertex]; }

    std::vector<int> GetPrevVertices(int vertex) const {
        std::vector<int> prevVertices;

        for (int from = 0; from < adjacencyLists.size(); from++) {
            for (int to : adjacencyLists[from]) {
                if (to == vertex) {
                    prevVertices.push_back(from);
                }
            }
        }
        return prevVertices;
    }

    int ShortWaysCount(int from, int to) const;

   private:
    std::vector<std::vector<int>> adjacencyLists;
};

int ListGraph::ShortWaysCount(int from, int to) const {
    if (from == to) return 0;

    std::vector<int> distance(VerticesCount());
    std::vector<int> way_counter(VerticesCount());

    way_counter[from] = 1;
    std::queue<int> qu;
    qu.push(from);

    while (!qu.empty()) {
        int cur_vertex = qu.front();
        qu.pop();
        for (auto next_vertex : GetNextVertices(cur_vertex)) {
            if (distance[next_vertex] == 0 || distance[cur_vertex] + 1 < distance[next_vertex]) {
                if (distance[next_vertex] == 0) qu.push(next_vertex);

                distance[next_vertex] = distance[cur_vertex] + 1;
                way_counter[next_vertex] = way_counter[cur_vertex];
            } else if (distance[cur_vertex] + 1 == distance[next_vertex])
                way_counter[next_vertex] += way_counter[cur_vertex];
        }
    }
    return way_counter[to];
}

int main() {
    int v = 0, n = 0;
    std::cin >> v >> n;
    ListGraph new_graph(v);
    int from = 0, to = 0;

    for (size_t i = 0; i < n; ++i) {
        std::cin >> from >> to;
        new_graph.AddEdge(from, to);
    }
    std::cin >> from >> to;

    std::cout << new_graph.ShortWaysCount(from, to);

    return 0;
}