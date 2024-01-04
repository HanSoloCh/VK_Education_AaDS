#include "SetGraph.h"

#include "vector"

SetGraph::SetGraph(const IGraph &graph)
    : verticesCount(graph.VerticesCount()), in(verticesCount), out(verticesCount) {
    std::vector<int> vertices;

    for (int i = 0; i < verticesCount; ++i) {
        vertices = graph.GetNextVertices(i);
        for (int j : vertices) {
            in[j].insert(i);
            out[i].insert(j);
        }
        vertices.clear();
    }
}

void SetGraph::AddEdge(int from, int to) {
    in[to].insert(from);
    out[from].insert(to);
}

int SetGraph::VerticesCount() const { return verticesCount; }

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> vertices;
    for (int i : in[vertex]) vertices.push_back(i);

    return vertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> vertices;
    for (int i : out[vertex]) vertices.push_back(i);

    return vertices;
}