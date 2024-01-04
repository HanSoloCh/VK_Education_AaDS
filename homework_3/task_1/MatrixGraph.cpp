#include "MatrixGraph.h"

#include <vector>

MatrixGraph::MatrixGraph(int size) : adjacency_matrix(size, std::vector<int>(size)) {}

MatrixGraph::MatrixGraph(const IGraph &graph)
    : adjacency_matrix(graph.VerticesCount(), std::vector<int>(graph.VerticesCount())) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        std::vector<int> from_i_to = graph.GetNextVertices(i);
        for (int vertex : from_i_to) adjacency_matrix[i][vertex] = 1;
    }
}

MatrixGraph::~MatrixGraph() = default;

void MatrixGraph::AddEdge(int from, int to) { adjacency_matrix[from][to] = 1; }

int MatrixGraph::VerticesCount() const { return static_cast<int>(adjacency_matrix.size()); }

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> next_vertices;
    for (int to = 0; to < adjacency_matrix[vertex].size(); ++to) {
        if (adjacency_matrix[vertex][to]) next_vertices.push_back(to);
    }
    return next_vertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev_vertices;

    for (int from = 0; from < adjacency_matrix.size(); ++from) {
        if (adjacency_matrix[from][vertex]) prev_vertices.push_back(from);
    }
    return prev_vertices;
}
