#include "ArcGraph.h"

#include <vector>

ArcGraph::ArcGraph(int size) : vertex_count(size) {}

ArcGraph::ArcGraph(const IGraph &graph) : vertex_count(graph.VerticesCount()) {
    for (int from = 0; from < graph.VerticesCount(); ++from) {
        for (auto to : graph.GetNextVertices(from)) {
            pair_arr.emplace_back(from, to);
        }
    }
}

ArcGraph::~ArcGraph() = default;

void ArcGraph::AddEdge(int from, int to) { pair_arr.emplace_back(from, to); }

int ArcGraph::VerticesCount() const { return vertex_count; }

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> next_vertices;
    for (auto &pair : pair_arr) {
        if (pair.first == vertex) next_vertices.push_back(pair.second);
    }
    return next_vertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev_vertices;

    for (auto pair : pair_arr) {
        if (pair.second == vertex) prev_vertices.push_back(pair.first);
    }
    return prev_vertices;
}
