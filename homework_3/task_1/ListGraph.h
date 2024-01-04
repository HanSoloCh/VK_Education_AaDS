#ifndef HOMEWORK_3_LISTGRAPH_H
#define HOMEWORK_3_LISTGRAPH_H

#include <vector>

#include "IGraph.h"

struct ListGraph : public IGraph {
   public:
    explicit ListGraph(int size);
    ~ListGraph();

    explicit ListGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

   private:
    std::vector<std::vector<int>> adjacencyLists;
};

#endif
