#include <cassert>
#include <functional>
#include <iostream>
#include <queue>

#include "ArcGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, std::function<void(int)> &func) {
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while (!qu.empty()) {
        int currentVertex = qu.front();
        qu.pop();

        func(currentVertex);

        for (int nextVertex : graph.GetNextVertices(currentVertex)) {
            if (!visited[nextVertex]) {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void BFS(const IGraph &graph, std::function<void(int)> func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i]) BFS(graph, i, visited, func);
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, std::function<void(int)> &func) {
    visited[vertex] = true;
    func(vertex);

    for (int nextVertex : graph.GetNextVertices(vertex)) {
        if (!visited[nextVertex]) DFS(graph, nextVertex, visited, func);
    }
}

void DFS(const IGraph &graph, std::function<void(int)> func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i]) DFS(graph, i, visited, func);
    }
}

int main() {
    ListGraph listGraph(9);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 5);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(1, 6);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 6);
    listGraph.AddEdge(5, 4);
    listGraph.AddEdge(5, 6);
    listGraph.AddEdge(6, 4);
    listGraph.AddEdge(7, 8);

    MatrixGraph matrixGraph(listGraph);
    assert(matrixGraph.VerticesCount() == listGraph.VerticesCount());
    SetGraph setGraph(listGraph);
    assert(setGraph.VerticesCount() == listGraph.VerticesCount());
    ArcGraph arcGraph(listGraph);
    assert(arcGraph.VerticesCount() == listGraph.VerticesCount());

    SetGraph setGraph1(matrixGraph);
    assert(setGraph1.VerticesCount() == matrixGraph.VerticesCount());
    ArcGraph arcGraph1(matrixGraph);
    assert(arcGraph.VerticesCount() == matrixGraph.VerticesCount());

    MatrixGraph matrixGraph1(setGraph1);
    assert(setGraph1.VerticesCount() == matrixGraph1.VerticesCount());
    ArcGraph arcGraph2(setGraph1);
    assert(setGraph1.VerticesCount() == arcGraph2.VerticesCount());

    MatrixGraph matrixGraph2(arcGraph2);
    assert(matrixGraph2.VerticesCount() == arcGraph2.VerticesCount());
    SetGraph setGraph2(arcGraph2);
    assert(setGraph2.VerticesCount() == arcGraph2.VerticesCount());

    std::cout << "BFS:" << std::endl;

    std::cout << "List graph: ";
    BFS(listGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "Matrix graph: ";
    BFS(matrixGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "Set graph: ";
    BFS(setGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "Arc graph: ";
    BFS(arcGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "DFS:" << std::endl;

    std::cout << "List graph: ";
    DFS(listGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "Matrix graph: ";
    DFS(matrixGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "Set graph: ";
    DFS(setGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "Arc graph: ";
    DFS(arcGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    return 0;
}