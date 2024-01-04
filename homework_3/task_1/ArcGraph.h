#ifndef HOMEWORK_3_ARCGRAPH_H
#define HOMEWORK_3_ARCGRAPH_H

#include <vector>

#include "IGraph.h"

struct ArcGraph : public IGraph {
   public:
    explicit ArcGraph(int size);
    ~ArcGraph();

    explicit ArcGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

   private:
    int vertex_count;
    std::vector<std::pair<int, int>> pair_arr;
};

#endif
