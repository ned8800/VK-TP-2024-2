#ifndef GRAPH_SRC_ARCGRAPH_H_
#define GRAPH_SRC_ARCGRAPH_H_

#include "IGraph.hpp"
#include <vector>

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(int _verticesCount);

    explicit ArcGraph(const IGraph &graph);
    
    ~ArcGraph() override = default;

    void AddEdge(int from, int to) override;
    
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> edges;
    int verticesCount;
};

#endif //GRAPH_SRC_ARCGRAPH_H_

