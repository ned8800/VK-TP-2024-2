#ifndef GRAPH_IGRAPH_H_
#define GRAPH_IGRAPH_H_

#include <vector>

struct IGraph {
    public:
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif //GRAPH_IGRAPH_H_

