#include "ListGraph.h"

#include <vector>

ListGraph::ListGraph(int size) : adjacencyLists(size) {}

ListGraph::ListGraph(const IGraph &graph) : adjacencyLists(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); i++) {
        adjacencyLists[i] = graph.GetNextVertices(i);
    }
}

ListGraph::~ListGraph() = default;

void ListGraph::AddEdge(int from, int to) { adjacencyLists[from].push_back(to); }

int ListGraph::VerticesCount() const { return static_cast<int>(adjacencyLists.size()); }

std::vector<int> ListGraph::GetNextVertices(int vertex) const { return adjacencyLists[vertex]; }

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
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
