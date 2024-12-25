#include "ArcGraph.hpp"
#include <algorithm>
#include <stdexcept>

ArcGraph::ArcGraph(int _verticesCount) : edges(), verticesCount(_verticesCount) {}

ArcGraph::ArcGraph(const IGraph &graph) : edges(), verticesCount(graph.VerticesCount()) {
    for (int u = 0; u < graph.VerticesCount(); ++u) {
        std::vector<int> nextVertices = graph.GetNextVertices(u);
        for (const int &v: nextVertices) {
            edges.emplace_back(u, v);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    if ((from >= 0) && (to >= 0) && (from < verticesCount) && (to < verticesCount)) {
        edges.emplace_back(from, to);
    }
}

int ArcGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    if ((vertex >= 0) && (vertex < verticesCount)) {
        std::vector<int> nextVertices;
        for (const auto &edge: edges) {
            if (edge.first == vertex) {
                nextVertices.push_back(edge.second);
            }
        }
        return nextVertices;
    }
    else {
        std::vector<int> emptyVertices{};
        return emptyVertices;
    }

}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    if ((vertex >= 0) && (vertex < verticesCount)) {
        std::vector<int> prevVertices;
        for (const auto &edge: edges) {
            if (edge.second == vertex) {
                prevVertices.push_back(edge.first);
            }
        }
        return prevVertices;
    }
    else {
        std::vector<int> emptyVertices{};
        return emptyVertices;
    }
}

