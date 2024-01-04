#ifndef M3_CSETGRAPH_H
#define M3_CSETGRAPH_H

#include <iostream>
#include <set>
#include <vector>

#include "IGraph.h"

class SetGraph : public IGraph {
   public:
    explicit SetGraph(int size) : verticesCount(size), in(size), out(size) {}
    explicit SetGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

   private:
    int verticesCount;
    std::vector<std::set<int>> in;
    std::vector<std::set<int>> out;
};

#endif