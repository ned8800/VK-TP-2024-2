#ifndef GRAPH_LISTGRAPH_H_
#define GRAPH_LISTGRAPH_H_

#include "IGraph.hpp"
#include <vector>

struct ListGraph : public IGraph {
public:
    ListGraph(int size);

    explicit ListGraph(const IGraph &graph);

    ~ListGraph() override = default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> listGraph;
    int verticesCount;
};

#endif //GRAPH_LISTGRAPH_H_

