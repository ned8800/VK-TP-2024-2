#include <stdexcept>
#include "SetGraph.hpp"

SetGraph::SetGraph(int _verticesCount) : setGraph(_verticesCount), verticesCount(_verticesCount) {}

SetGraph::SetGraph(const IGraph &graph) : setGraph(graph.VerticesCount()), verticesCount(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        auto nextVertices = graph.GetNextVertices(i);
        for (const auto &vertex: nextVertices) {
            setGraph[i].insert(vertex);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    if ((from >= 0) && (to >= 0) && (from < verticesCount) && (to < verticesCount)) {
        setGraph[from].insert(to);
    }    
}

int SetGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    if ((vertex >= 0) && (vertex < verticesCount)) {
        std::vector<int> nextVertices;
        for (const auto &v: setGraph[vertex]) {
            nextVertices.push_back(v);
        }
        return nextVertices;
    }
    else {
        std::vector<int> emptyVertices{};
        return emptyVertices;
    }
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    if ((vertex >= 0) && (vertex < verticesCount)) {
        std::vector<int> prevVertices;
        for (int u = 0; u < setGraph.size(); ++u) {
            for (const auto &v: setGraph[u]) {
                if (v == vertex) {
                    prevVertices.push_back(u);
                }
            }
        }
        return prevVertices;
    }
    else {
        std::vector<int> emptyVertices{};
        return emptyVertices;
    }
}

