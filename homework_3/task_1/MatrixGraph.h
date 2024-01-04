#ifndef HOMEWORK_3_MATRIXGRAPH_H
#define HOMEWORK_3_MATRIXGRAPH_H

#include <vector>

#include "IGraph.h"

struct MatrixGraph : public IGraph {
   public:
    explicit MatrixGraph(int size);
    ~MatrixGraph();

    explicit MatrixGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

   private:
    std::vector<std::vector<int>> adjacency_matrix;
};

#endif
