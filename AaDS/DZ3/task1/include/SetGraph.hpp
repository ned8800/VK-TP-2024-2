#ifndef GRAPH_SRC_SETGRAPH_H_
#define GRAPH_SRC_SETGRAPH_H_

#include "IGraph.hpp"
#include <unordered_set>
#include <vector>

class SetGraph : public IGraph {
public:
    explicit SetGraph(int _verticesCount);

    explicit SetGraph(const IGraph &graph);

    ~SetGraph() override = default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::unordered_set<int>> setGraph;
    int verticesCount;
};

#endif //GRAPH_SRC_SETGRAPH_H_

